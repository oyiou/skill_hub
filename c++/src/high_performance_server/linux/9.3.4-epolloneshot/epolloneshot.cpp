//
// Created by leever on 2023/3/14.
//
#include "high_performance_server.h"

#define MAX_EVENT_NUMBER 1024
#define BUFFER_SIZE 1024

struct fds {
    int epoll_fd;
    int sock_fd;
};

int set_non_blocking(int fd) {
    int old_option = fcntl(fd, F_GETFL);
    int new_option = old_option | O_NONBLOCK;
    fcntl(fd, F_SETFL, new_option);
    return old_option;
}
// 将 fd 上的 EPOLLIN 和 EPOLLET 事件注册到 epollfd 指示的 epoll 内核事件表中，参数 oneshot 指定是否注册 fd 上的 EPOLLONESHOT 事件
void add_fd (int epoll_fd, int fd, bool one_shot) {
    epoll_event event;
    event.data.fd = fd;
    event.events = EPOLLIN | EPOLLET;
    if (one_shot) {
        event.events |= EPOLLONESHOT;
    }
    epoll_ctl(epoll_fd, EPOLL_CTL_ADD, fd, &event);
    set_non_blocking(fd);
}
// 重置 fd 上的事件。这样操作之后，尽管 fd 上的 EPOLLONESHOT 事件被注册，但是操作系统仍然会触发 fd 上的 EPOLLIN 事件，且只触发一次
void reset_one_shot (int epoll_fd, int fd) {
    epoll_event event;
    event.data.fd = fd;
    event.events = EPOLLIN | EPOLLET | EPOLLONESHOT;
    epoll_ctl(epoll_fd, EPOLL_CTL_MOD, fd, &event);
}
// 工作线程
void *worker (void *arg) {
    int sock_fd = ((fds*)arg)->sock_fd;
    int epoll_fd = ((fds*)arg)->epoll_fd;
    printf("start new thread to receive data on fd: %d\n", sock_fd);
    char buf[BUFFER_SIZE];
    memset(buf, '\0', BUFFER_SIZE);
    // 循环读取 sock_fd 上的数据，直到遇到 EAGAIN 错误
    while (1) {
        int ret = recv(sock_fd, buf, BUFFER_SIZE - 1, 0);
        if (ret == 0) {
            close(sock_fd);
            printf("foreiner closed the connection\n");
            break;
        } else if (ret < 0) {
            if (errno == EAGAIN) {
                reset_one_shot(epoll_fd, sock_fd);
                printf("read later\n");
                break;
            }
        } else {
            printf("get content: %s\n", buf);
            // 休眠 5s，模拟数据处理过程
            sleep(5);
        }
    }
    printf("end thread receiving data in fd: %d\n", sock_fd);
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

    int listen_fd = listen(PF_INET, SOCK_STREAM, 0);
    assert(listen_fd >= 0);

    ret = bind(listen_fd, (struct sockaddr*)&address, sizeof(address));
    assert(ret != -1);

    ret = listen(listen_fd, 5);
    assert(ret != -1);

    epoll_event events[MAX_EVENT_NUMBER];
    int epoll_fd = epoll_create(5);
    assert(epoll_fd != -1);
    // 注意，监听 socket listen_fd 上是不能注册 EPOLLONESHOT 事件的，否则应用程序只能处理一个客户连接，因为后续的客户连接将不再触发 listen_fd 上的 EPOLLIN 事件
    add_fd(epoll_fd, listen_fd, false);

    while (1) {
        ret = epoll_wait(epoll_fd, events, MAX_EVENT_NUMBER, -1);
        if (ret < 0) {
            printf("epoll failure\n");
            break;
        }
        for (int i = 0; i < ret; ++i) {
            int sock_fd = events[i].data.fd;
            if (sock_fd == listen_fd) {
                struct sockaddr_in client_address;
                socklen_t client_addr_length = sizeof(client_address);
                int conn_fd = accept(listen_fd, (struct sockaddr*)&client_address, &client_addr_length);
                // 对每个非监听文件描述符都注册 EPOLLONESHOT 事件
                add_fd(epoll_fd, conn_fd, true);
            } else if (events[i].events & EPOLLIN) {
                pthread_t thread;
                fds fds_for_new_worker;
                fds_for_new_worker.epoll_fd = epoll_fd;
                fds_for_new_worker.sock_fd = sock_fd;
                // 新启动一个工作线程为 sock_fd 服务
                pthread_create(&thread, NULL,  worker, (void *)&fds_for_new_worker);
            } else {
                printf("something else happened\n");
            }
        }
    }
    close(listen_fd);
    return 0;
}