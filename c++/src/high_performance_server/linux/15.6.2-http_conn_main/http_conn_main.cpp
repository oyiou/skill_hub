//
// Created by leever on 2023/3/25.
//
#include "locker.h"
#include "threadpool.h"
#include "http_conn.h"

#define MAX_FD 65536
#define MAX_EVENT_NUMBER 10000

extern int add_fd(int epoll_fd, int fd, bool one_shot);
extern int remove_fd(int epoll_fd, int fd);

void add_sig(int sig, void (handler)(int), bool restart = true) {
    struct sigaction sa;
    memset(&sa, '\0', sizeof(sa));
    sa.sa_handler = handler;
    if (restart) {
        sa.sa_flags |= SA_REQUEST;
    }
    sigfillset(&sa.sa_mask);
    assert(sigaction(sig, &sa, NULL) != -1);
}

void show_error(int conn_fd, const char *info) {
    printf("%s", info);
    send(conn_fd, info, strlen(info), 0);
    close(conn_fd);
}

int main(int argc, char *argv[]) {
    if (argc <= 2) {
        printf("usage: %s ip_address port_number\n", basename(argv[0]));
        return 1;
    }
    const char *ip = argv[1];
    int port = atoi(argv[2]);

    // 忽略 SIGPIPE 信号
    add_sig(SIGPIPE, SIG_IGN);

    // 创建线程池
    threadpool<http_conn> *pool = NULL;
    try {
        pool = new threadpool<http_conn>;
    } catch (...) {
        return 1;
    }

    // 预先为每个可能的客户连接分配一个 http_conn 对象
    http_conn *users = new http_conn[MAX_FD];
    assert(users);
    int user_count = 0;

    int listen_fd = socket(PF_INET, SOCK_STREAM, 0);
    assert(listen_fd >= 0);
    struct linger tmp = {1, 0};
    setsockopt(listen_fd, SOL_SOCKET, SO_LINGER, &tmp, sizeof(tmp));

    int ret = 0;
    struct sockaddr_in address;
    bzero(&address, sizeof(address));
    address.sin_family = AF_INET;
    inet_pton(AF_INET, ip, &address.sin_addr);
    address.sin_port = htons(port);

    ret = bind(listen_fd, (struct sockaddr*)&address, sizeof(address));
    assert(ret >= 0);

    ret = listen(listen_fd, 5);
    assert(ret >= 0);

    epoll_event events[MAX_EVENT_NUMBER];
    int epoll_fd = epoll_create(5);
    assert(epoll_fd != -1);
    add_fd(epoll_fd, listen_fd, false);
    http_conn::m_epoll_fd = epoll_fd;

    while (true) {
        int number = epoll_wait(epoll_fd, events, MAX_EVENT_NUMBER, -1);
        if ((number < 0) && (errno != EINTR)) {
            printf("epoll failure\n");
            break;
        }

        for (int i = 0; i < number; i++) {
            int sock_fd = events[i].data.fd;
            if (sock_fd == listen_fd) {
                struct sockaddr_in client_address;
                socklen_t client_addr_length = sizeof(client_address);
                int conn_fd = accept(listen_fd, (struct sockaddr*)&client_address, &client_addr_length);
                if (conn_fd < 0) {
                    printf("errno is: %d\n", errno);
                    continue;
                }
                if (http_conn::m_user_count >= MAX_FD) {
                    show_error(conn_fd, "Internal server busy");
                    continue;
                }
                // 初始化客户连接
                users[conn_fd].init(conn_fd, client_address);
            } else if (events[i].events & (EPOLLRDHUP | EPOLLHUP | EPOLLERR)) {
                // 如果有异常，直接关闭客户连接
                users[sock_fd].close_conn();
            } else if (events[i].events & EPOLLIN) {
                // 根据读的结果，决定是将任务添加到线程池，还是关闭连接
                if (users[sock_fd].read()) {
                    pool->append(users + sock_fd);
                } else {
                    users[sock_fd].close_conn();
                }
            } else if (events[i].events & EPOLLOUT) {
                // 根据写的结果，决定是否关闭连接
                if (!users[sock_fd].write()) {
                    users[sock_fd].close_conn();
                }
            } else {

            }
        }
    }

    close(epoll_fd);
    close(listen_fd);
    delete [] users;
    delete pool;
    return 0;
}