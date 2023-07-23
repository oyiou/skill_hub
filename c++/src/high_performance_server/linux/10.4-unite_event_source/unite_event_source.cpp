//
// Created by leever on 2023/3/15.
//
#include "high_performance_server.h"

#define MAX_EVENT_NUMBER 1024
static int pipe_fd[2];

int set_non_blocking (int fd) {
    int old_option = fcntl(fd, F_GETFL);
    int new_option = old_option | O_NONBLOCK;
    fcntl(fd, F_SETFL, new_option);
    return old_option;
}

void add_fd (int epoll_fd, int fd) {
    epoll_event event;
    event.data.fd = fd;
    event.events = EPOLLIN | EPOLLET;
    epoll_ctl(epoll_fd, EPOLL_CTL_ADD, fd, &event);
    set_non_blocking(fd);
}
// 信号处理函数
void sig_handler (int sig) {
    // 保留原理的 errno，在函数最后恢复，以保证函数的可重入性
    int save_errno = errno;
    int msg = sig;
    send(pipe_fd[1], (char *)&msg, 1, 0);   // 将信号值写入管道，以通知主循环
    errno = save_errno;
}
// 设置信号的处理函数
void add_sig (int sig) {
    struct sigaction sa;
    memset(&sa, '\0', sizeof(sa));
    sa.sa_handler = sig_handler;
    sa.sa_flags |= SA_RESTART;
    sigfillset(&sa.sa_mask);
    assert(sigaction(sig, &sa, NULL) != -1);
}

int main(int argc, char *argv[]) {
    if (argc <= 2) {
        printf("usage: %s ip_address port_number\n", basename(argv[0]));
        return 1;
    }
    const char *ip = argv[1];
    int port = atoi(argv[2]);

    int ret = 0;
    struct sockaddr_in address;
    bzero(&address, sizeof(address));
    address.sin_family = AF_INET;
    inet_pton(AF_INET, ip, &address.sin_addr);
    address.sin_port = htons(port);

    int listen_fd = socket(PF_INET, SOCK_STREAM, 0);
    assert(listen_fd >= 0);

    ret = bind(listen_fd, (struct sockaddr*)&address, sizeof(address));
    if (ret == -1) {
        printf("errno is %d\n", errno);
        return 1;
    }
    ret = listen(listen_fd, 5);
    assert(ret != -1);

    epoll_event events[MAX_EVENT_NUMBER];
    int epoll_fd = epoll_create(5);
    assert(epoll_fd != -1);
    add_fd(epoll_fd, listen_fd);

    // 使用 socketpair 创建管道，注册 pipe_fd[0] 上的可读事件
    ret = socketpair(PF_UNIX, SOCK_STREAM, 0, pipe_fd);
    assert(ret != -1);
    set_non_blocking(pipe_fd[1]);
    add_fd(epoll_fd, pipe_fd[0]);

    // 设置一些信号的处理函数
    add_sig(SIGHUP);
    add_sig(SIGCHLD);
    add_sig(SIGTERM);
    add_sig(SIGINT);
    bool stop_server = false;

    while (!stop_server) {
        int number = epoll_wait(epoll_fd, events, MAX_EVENT_NUMBER, -1);
        if ((number < 0) && (errno != EINTR)) {
            printf("epoll failure\n");
            break;
        }

        for (int i = 0; i < number; i++) {
            int sock_fd = events[i].data.fd;
            // 如果就绪的文件描述符是 listen_fd，则处理新的连接
            if (sock_fd == listen_fd) {
                struct sockaddr_in client_address;
                socklen_t client_addr_length = sizeof(client_address);
                int conn_fd = accept(listen_fd, (struct sockaddr*)&client_address, &client_addr_length);
                add_fd(epoll_fd,conn_fd);
            } else if ((sock_fd == pipe_fd[0]) && (events[i].events & EPOLLIN)) {   // 如果就绪的文件描述符是 pipe_fd[0]，则处理信号
                int sig;
                char signals[1024];
                ret = recv(pipe_fd[0], signals, sizeof(signals), 0);
                if (ret == -1) {
                    continue;
                } else if (ret == 0) {
                    continue;
                } else {
                    // 因为每个信号值占 1 字节，所以按字节来逐个接收信号。以 SIGTERM 为例，来说明如何安全地终止服务器主循环
                    for (int j = 0; j < ret; ++j) {
                        switch (signals[i]) {
                            case SIGCHLD:
                            case SIGHUP: {
                                continue;
                            }
                            case SIGTERM:
                            case SIGINT: {
                                stop_server = true;
                            }
                        }
                    }
                }
            } else {

            }
        }
    }
    printf("close fds\n");
    close(listen_fd);
    close(pipe_fd[1]);
    close(pipe_fd[0]);
    return 0;
}