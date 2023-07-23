//
// Created by leever on 2023/3/15.
//
#include "high_performance_server.h"

#define MAX_EVENT_NUMBER 1024
#define TCP_BUFFER_SIZE 512
#define UDP_BUFFER_SIZE 1024

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

    // 创建 TCP socket，并将其绑定到端口 port 上
    int listen_fd = socket(PF_INET, SOCK_STREAM, 0);
    assert(listen_fd >= 0);

    ret = bind(listen_fd, (struct sockaddr*)&address, sizeof(address));
    assert(ret != -1);

    ret = listen(listen_fd, 5);
    assert(ret != -1);

    // 创建 UDP socket，并将其绑定到端口 port 上
    bzero(&address, sizeof(address));
    address.sin_family = AF_INET;
    inet_pton(AF_INET, ip, &address.sin_addr);
    address.sin_port = htons(port);
    int udp_fd = socket(PF_INET, SOCK_DGRAM, 0);
    assert(udp_fd >= 0);

    ret = bind(udp_fd, (struct sockaddr*)&address, sizeof(address));
    assert(ret != -1);

    epoll_event events[MAX_EVENT_NUMBER];
    int epoll_fd = epoll_create(5);
    assert(epoll_fd != -1);
    // 注册 TCP socket 和 TDP socket 上的可读事件
    add_fd(epoll_fd, listen_fd);
    add_fd(epoll_fd, udp_fd);

    while (1) {
        int number = epoll_wait(epoll_fd, events, MAX_EVENT_NUMBER, -1);
        if (number < 0) {
            printf("epoll failure\n");
            break;
        }

        for (int i = 0; i < number; i++) {
            int sock_fd = events[i].data.fd;
            if (sock_fd == listen_fd) {
                struct sockaddr_in client_address;
                socklen_t  client_addr_length = sizeof(client_address);
                int conn_fd = accept(listen_fd, (struct sockaddr*)&client_address, &client_addr_length);
                add_fd(epoll_fd, conn_fd);
            } else if (sock_fd == udp_fd) {
                char buf[UDP_BUFFER_SIZE];
                memset(buf, '\0', UDP_BUFFER_SIZE);
                struct sockaddr_in client_address;
                socklen_t client_addr_length = sizeof(client_address);

                ret = recvfrom(udp_fd, buf, UDP_BUFFER_SIZE - 1, 0, (struct sockaddr*)&client_address, &client_addr_length);

                if (ret > 0) {
                    sendto(udp_fd, buf, UDP_BUFFER_SIZE - 1, 0, (struct sockaddr*)&client_address, client_addr_length);
                }
            } else if (events[i].events & EPOLLIN) {
                char buf[TCP_BUFFER_SIZE];
                while (1) {
                    memset(buf, '\0', TCP_BUFFER_SIZE);
                    ret = recv(sock_fd, buf, TCP_BUFFER_SIZE - 1, 0);
                    if (ret < 0) {
                        if ((errno == EAGAIN) || (errno == EWOULDBLOCK)) {
                            break;
                        }
                        close(sock_fd);
                        break;
                    } else if (ret == 0) {
                        close(sock_fd);
                    } else {
                        send(sock_fd, buf, ret, 0);
                    }
                }
            } else {
                printf("something else happened\n");
            }
        }
    }
    close(listen_fd);
    return 0;
}