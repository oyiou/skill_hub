//
// Created by leever on 2023/3/14.
//
#include "high_performance_server.h"

#define MAX_EVENT_NUMBER 1024
#define BUFFER_SIZE 10

// 将文件描述符设置成非阻塞的
int set_non_blocking(int fd) {
    int old_option = fcntl(fd, F_GETFL);
    int new_option = old_option | O_NONBLOCK;
    fcntl(fd, F_SETFL, new_option);
    return old_option
}
// 将文件描述符 fd 上的 EPOLLIN 注册到 epollfd 指示的 epoll 内核事件表中，参数 enable_et 指定是否对 fd 启用 ET 模式
void add_fd(int epoll_fd, int fd, bool enable_et) {
    epoll_event event;
    event.data.fd = fd;
    event.events = EPOLLIN;
    if (enable_et) {
        event.events |= EPOLLET;
    }
    epoll_ctl(epoll_fd, EPOLL_CTL_ADD, fd, &event);
    set_non_blocking(fd);
}
// LT 模式工作流程
void lt (epoll_event *events, int number, int epoll_fd, int listen_fd) {
    char buf[BUFFER_SIZE];
    for (int i = 0; i < number; i++) {
        int sock_fd = events[i].data.fd;
        if (sock_fd == listen_fd) {
            struct sockaddr_in client_address;
            socklen_t client_addr_length = sizeof(client_address);
            int conn_fd = accept(listen_fd, (struct sockaddr*)&client_address, &client_addr_length);
            add_fd(epoll_fd, conn_fd, false);   // 对 conn_fd 禁用 ET 模式
        } else if (events[i].events & EPOLLIN) {
            // 只要 socket 读缓存中还有为读出的数据，这段代码就被触发
            printf("event trigger once\n");
            memset(buf, '\0', BUFFER_SIZE);
            int ret = recv(sock_fd, buf, BUFFER_SIZE - 1, 0);
            if (ret <= 0) {
                close(sock_fd);
                continue;
            }
            printf("get %d bytes of content: %s\n", ret, buf);
        } else {
            printf("something else happened\n");
        }
    }
}
// ET 模式的工作流程
void et (epoll_event *events, int number, int epoll_fd, int listen_fd) {
    char buf[BUFFER_SIZE];
    for (int i = 0; i < number; i++) {
        int sock_fd = events[i].data.fd;
        if (sock_fd == listen_fd) {
            struct sockaddr_in client_address;
            socklen_t client_addr_length = sizeof(client_address);
            int conn_fd = accept(listen_fd, (struct sockaddr*)&client_address, &client_addr_length);
            add_fd(epoll_fd, conn_fd, true);    // 对 conn_fd 开启 ET 模式
        } else if (events[i].events & EPOLLIN) {
            // 这段代码不会被重复触发，所以循环读取数据，以确保把 socket 读缓存中的所有数据读出
            printf("event trigger once\n");
            while (1) {
                memset(buf, '\0', BUFFER_SIZE);
                int ret = recv(sock_fd, buf, BUFFER_SIZE - 1, 0);
                if (ret < 0) {
                    // 对于非阻塞 IO，下面的条件成立表示数据已经全部读取完毕。此后，epoll 就能再次触发 sock_fd 上的 EPOLLIN 事件，以驱动下一次读操作
                    if ((errno == EAGAIN) || (errno == EWOULDBLOCK)) {
                        printf("read later\n");
                        break;
                    }
                    close(sock_fd);
                    break;
                } else if (ret == 0) {
                    close(sock_fd);
                } else {
                    printf("get %d bytes of content: %s\n", ret, buf);
                }
            }
        } else {
            printf("something else happened\n");
        }
    }
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
    assert(ret != -1);

    ret = listen(listen_fd, 5);
    assert(ret != -1);

    epoll_event events[MAX_EVENT_NUMBER];
    int epoll_fd = epoll_create(5);
    assert(epoll_fd != -1);
    add_fd(epoll_fd, listen_fd, true);

    while (1) {
        ret = epoll_wait(epoll_fd, events, MAX_EVENT_NUMBER, -1);
        if (ret < 0) {
            printf("epoll failure\n");
            break;
        }
        lt(events, ret, epoll_fd, listen_fd);   // 使用 LT 模式
//        et(events, ret ,epoll_fd, listen_fd);   // 使用 ET 模式
    }
    close(listen_fd);
    return 0;
}