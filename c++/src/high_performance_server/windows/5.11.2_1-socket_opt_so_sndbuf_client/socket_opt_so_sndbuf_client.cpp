//
// Created by leever on 2023/3/9.
//
#include "high_performance_server.h"

#define BUFFER_SIZE 512

int main(int argc, char *argv[]) {
    if (argc <= 2) {
        printf("usage: %s ip_address port_number send_buffer_size\n", basename(argv[0]));
        return 1;
    }

    WSA_INIT

    const char *ip = argv[1];
    char *endptr;
    int port = (int)strtol(argv[2], &endptr, 0);

    struct sockaddr_in server_address;
    memset(&server_address, 0, sizeof(server_address));
    server_address.sin_family = AF_INET;
    inet_pton(AF_INET, ip, &server_address.sin_addr);
    server_address.sin_port = htons(port);

    SOCKET sock = socket(PF_INET, SOCK_STREAM, 0);
    assert(sock != INVALID_SOCKET);

    char sendbuf = *argv[3];
    int len = sizeof(sendbuf);
    // 先设置 TCP 发送缓冲区的大小，然后立即读取之
    setsockopt(sock, SOL_SOCKET, SO_SNDBUF, &sendbuf, sizeof(sendbuf));
    getsockopt(sock, SOL_SOCKET, SO_SNDBUF, &sendbuf, (socklen_t*)&len);
    printf("the tcp send buffer size after setting is %d\n", sendbuf);

    if (connect(sock, (struct sockaddr*)&server_address, sizeof(server_address)) != 1) {
        char buffer[BUFFER_SIZE];
        memset(buffer, 'a', BUFFER_SIZE);
        send(sock, buffer, BUFFER_SIZE, 0);
    }
    closesocket(sock);
    WSA_RELEASE
    return 0;
}