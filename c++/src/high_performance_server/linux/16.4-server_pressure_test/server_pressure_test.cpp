//
// Created by leever on 2023/3/25.
//
#include "high_performance_server.h"

// 每个客户连接不停地向服务器发送这个请求
static const char *request = "GET http://localhost/index.html HTTP/1.1\r\nConnection: keep-alive\r\n\r\nxxxxxxxxxxxxxxxxxxxxxxx";

int set_non_blocking(int fd) {
    int old_option = fcntl(fd, F_GETFL);
    int new_option = old_option | O_NONBLOCK;
    fcntl(fd, F_SETFL, new_option);
    return old_option;
}

void add_fd(int epoll_fd, int fd) {
    epoll_event event;
    event.data.fd = fd;
    event.events = EPOLLOUT | EPOLLET | EPOLLERR;
    epoll_ctl(epoll_fd, EPOLL_CTL_ADD, fd, &event);
    set_non_blocking(fd);
}

// 向服务器写入 len 字节的数据
bool write_n_bytes(int sock_fd, const char *buffer, int len) {
    int bytes_write = 0;
    printf("write out %d bytes to socket %d\n", len, sock_fd);
    while (1) {
        bytes_write = send(sock_fd, buffer, len, 0);
        if (bytes_write == -1) {
            return false;
        } else if (bytes_write == 0) {
            return false;
        }

        len -= bytes_write;
        buffer == buffer + bytes_write;
        if (len <= 0) {
            return true;
        }
    }
}

// 从服务器读取数据
bool read_once(int sock_fd, char *buffer, int len) {
    int bytes_read = 0;
    memset(buffer, '\0', len);
    bytes_read = recv(sock_fd, buffer, len, 0);
    if (bytes_read == -1) {
        return false;
    } else if (bytes_read == 0) {
        return false;
    }
    printf("read in %d bytes from socket %d with content: %s\n", bytes_read, sock_fd, buffer);

    return true;
}

// 向服务器发起 num 个 TCP 连接，可以通过改变 num 来调整测试压力
void start_conn(int epoll_fd, int num, const char *ip, int port) {
    int ret = 0;
    struct sockaddr_in address;
    bzero(&address, sizeof(address));
    address.sin_family = AF_INET;
    inet_pton(AF_INET, ip, &address.sin_addr);
    address.sin_port = htons(port);

    for (int i = 0; i < num; ++i) {
        sleep(1);
        int sock_fd = socket(PF_INET, SOCK_STREAM, 0);
        printf("create 1 sock\n");
        if (sock_fd < 0) {
            continue;
        }

        if (connect(sock_fd, (struct sockaddr*)&address, sizeof(address)) == 0) {
            printf("build connection %d\n", i);
            add_fd(epoll_fd, sock_fd);
        }
    }
}

void close_conn(int epoll_fd, int sock_fd) {
    epoll_ctl(epoll_fd, EPOLL_CTL_DEL, sock_fd, 0);
    close(sock_fd);
}

int main(int argc, char *argv[]) {
    assert(argc == 4);
    int epoll_fd = epoll_create(100);
    start_conn(epoll_fd, atoi(argv[3]), argv[1], atoi(argv[2]));
    epoll_event events[10000];
    char buffer[2048];
    while (1) {
        int fds = epoll_wait(epoll_fd, events, 10000, 2000);
        for (int i = 0; i < fds; ++i) {
            int sock_fd = events[i].data.fd;
            if (events[i].events & EPOLLIN) {
                if (!read_once(sock_fd, buffer, 2048)) {
                    close_conn(epoll_fd, sock_fd);
                }
                struct epoll_event event;
                event.events = EPOLLOUT | EPOLLET | EPOLLERR;
                event.data.fd = sock_fd;
                epoll_ctl(epoll_fd, EPOLL_CTL_MOD, sock_fd, &event);
            } else if (events[i].events & EPOLLOUT) {
                if (!write_n_bytes(sock_fd, request, strlen(request))) {
                    close_conn(epoll_fd, sock_fd);
                }
                struct epoll_event event;
                event.events = EPOLLIN | EPOLLET | EPOLLERR;
                event.data.fd = sock_fd;
                epoll_ctl(epoll_fd, EPOLL_CTL_MOD, sock_fd, &event);
            } else if (events[i].events & EPOLLERR) {
                close_conn(epoll_fd, sock_fd);
            }
        }
    }
}