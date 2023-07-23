//
// Created by leever on 2023/3/20.
//
#include "high_performance_server.h"

// 超时连接函数
int timeout_connect (const char *ip, int port, int time) {
    int ret = 0;
    struct sockaddr_in address;
    bzero(&address, sizeof(address));
    address.sin_family = AF_INET;
    inet_pton(AF_INET, ip, &address.sin_addr);
    address.sin_port = htons(port);

    int  sock_fd = socket(PF_INET, SOCK_STREAM, 0);
    assert(sock_fd >= 0);
    // 通过选项 SO_RCVTIMEO 和 SO_SNDTIMEO 所设置的超时时间的类型是 timeval，这和 select 系统调用的超时参数类型相同
    struct timeval timeout;
    timeout.tv_sec = time;
    timeout.tv_usec = 0;
    socklen_t len = sizeof(timeout);
    ret = setsockopt(sock_fd, SOL_SOCKET, SO_SNDTIMEO, &timeout, len);
    assert(ret != -1);

    ret = connect(sock_fd, (struct sockaddr*)&address, sizeof(address));
    if (ret == -1) {
        // 超时对应的错误号是 EINPROGRESS
        if (errno == EINPROGRESS) {
            printf("connecting timeout, process timeout logic \n");
            return -1;
        }
        printf("error occur when connecting to server\n");
        return -1;
    }
    return sock_fd;
}

int main (int argc, char *argv[]) {
    if (argc <= 2) {
        printf("usage: %s ip_address port_number\n", basename(argv[0]));
        return 1;
    }
    const char *ip = argv[1];
    int port = atoi(argv[2]);

    int sock_fd = timeout_connect(ip, port, 10);
    if (sock_fd < 0) {
        return 1;
    }
    return 0;
}