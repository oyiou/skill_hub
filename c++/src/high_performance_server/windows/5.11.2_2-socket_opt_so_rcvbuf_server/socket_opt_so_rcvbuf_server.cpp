//
// Created by leever on 2023/3/9.
//
#include "high_performance_server.h"

#define BUFFER_SIZE 1024

int main(int argc, char *argv[]) {
    if (argc <= 2) {
        printf("usage: %s ip_address port_number recv_buffer_size\n", basename(argv[0]));
        return 1;
    }

    WSA_INIT

    const char *ip = argv[1];
    char *endptr;
    int port = (int)strtol(argv[2], &endptr, 0);

    struct sockaddr_in address;
    memset(&address, 0, sizeof(address));
    address.sin_family = AF_INET;
    inet_pton(AF_INET, ip, &address.sin_addr);
    address.sin_port = htons(port);

    SOCKET sock = socket(PF_INET, SOCK_STREAM, 0);
    assert(sock != INVALID_SOCKET);

    char recvbuf = *argv[3];
    int len = sizeof(recvbuf);
    // 先设置 TCP 发送缓冲区的大小，然后立即读取之
    setsockopt(sock, SOL_SOCKET, SO_RCVBUF, &recvbuf, sizeof(recvbuf));
    getsockopt(sock, SOL_SOCKET, SO_RCVBUF, &recvbuf, (socklen_t*)&len);
    printf("the tcp receive buffer size after setting is %d\n", recvbuf);

    int ret = bind(sock, (struct sockaddr*)&address, sizeof(address));
    assert(ret != SOCKET_ERROR);

    ret = listen(sock, 5);
    assert(ret != SOCKET_ERROR);

    struct sockaddr_in client;
    socklen_t  client_addrlength = sizeof(client);
    SOCKET connfd = accept(sock, (struct sockaddr*)&client, &client_addrlength);
    if (connfd == INVALID_SOCKET) {
        printf("WSAGetLastError() is: %d\n", WSAGetLastError());
    } else {
        char buffer[BUFFER_SIZE];
        memset(buffer, '\0', BUFFER_SIZE);
        while (recv(connfd, buffer, BUFFER_SIZE-1, 0) > 0) {}
        closesocket(connfd);
    }
    closesocket(sock);
    WSA_RELEASE
    return 0;
}