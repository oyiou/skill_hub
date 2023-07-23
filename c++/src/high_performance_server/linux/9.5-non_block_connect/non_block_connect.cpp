//
// Created by leever on 2023/3/14.
//
#include "high_performance_server.h"

#define BUFFER_SIZE 1023

int set_non_blocking (int fd) {
    int old_option = fcntl(fd, F_GETFL);
    int new_option = old_option | O_NONBLOCK;
    fcntl(fd, F_SETFL, new_option);
    return old_option;
}
// 超时连接函数，参数分别是服务器 IP 地址、端口号和超时事件（毫秒）。函数成功时返回已经处于连接状态的 socket，失败则返回 -1
int unblock_connect (const char *ip, int port, int time) {
    int ret = 0;
    struct sockaddr_in address;
    bzero(&address, sizeof(address));
    address.sin_family = AF_INET;
    inet_pton(AF_INET, ip, &address.sin_addr);
    address.sin_port = htons(port);

    int sock_fd = socket(PF_INET, SOCK_STREAM, 0);
    int fd_opt = set_non_blocking(sock_fd);
    ret = connect(sock_fd, (struct sockaddr*)&address, sizeof(address));
    if (ret == 0) {
        // 如果连接成功，则恢复 sock_fd 的属性，并立即返回之
        printf("connect with server immediately\n");
        fcntl(sock_fd, F_SETFL, fd_opt);
        return sock_fd;
    } else if (errno != EINPROGRESS) {
        // 如果连接没有立即建立，那么只有当 errno 是 EINPROGRESS 时才表示连接还在进行，否则出错返回
        printf("unblock connect not support\n");
        return -1;
    }
    fd_set read_fds;
    fd_set write_fds;
    struct timeval timeout;

    FD_ZERO(&read_fds);
    FD_SET(sock_fd, &write_fds);

    timeout.tv_sec = time;
    timeout.tv_usec = 0;

    ret = select(sock_fd + 1, NULL, &write_fds, NULL, &timeout);
    if (ret <= 0) {
        // select 超时或者出错，立即返回
        printf("connection time out\n");
        close(sock_fd);
        return -1;
    }

    if (!FD_ISSET(sock_fd, &write_fds)) {
        printf("no events on sockfd found\n");
        close(sock_fd);
        return -1;
    }

    int error = 0;
    socklen_t length = sizeof(error);
    // 调用 getsockopt 来获取并清除 sockfd 上的错误
    if (getsockopt(sock_fd, SOL_SOCKET, SO_ERROR, &error, &length) < 0) {
        printf("get socket option failed\n");
        close(sock_fd);
        return -1;
    }
    // 错误号不为 0 表示连接出错
    if (error != 0) {
        printf("connection failed after select with the error: %d\n", error);
        close(sock_fd);
        return -1;
    }
    // 连接成功
    printf("connection ready after select with the socket: %d\n", sock_fd);
    fcntl(sock_fd, F_SETFL, fd_opt);
    return sock_fd;
}

int main(int argc, char *argv[]) {
    if (argc <= 2) {
        printf("usage: %s ip_address port_number\n", basename(argv[0]));
        return 1;
    }
    const char *ip = argv[1];
    int port = atoi(argv[2]);

    int sock_fd = unblock_connect(ip, port, 10);
    if (sock_fd < 0) {
        return 1;
    }
    close(sock_fd);
    return 0;
}