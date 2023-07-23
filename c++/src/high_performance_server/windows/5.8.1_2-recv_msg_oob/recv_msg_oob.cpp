//
// Created by leever on 3/7/23.
//
#include "high_performance_server.h"

#define BUF_SIZE 1024

int main(int argc, char *argv[]) {
    if (argc <= 2) {
        printf("usage: %s ip_address port_number\n", basename(argv[0]));
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

    int ret = bind(sock, (struct sockaddr*)&address, sizeof(address));
    assert(ret != SOCKET_ERROR);

    ret = listen(sock, 5);
    assert(ret != SOCKET_ERROR);

    struct  sockaddr_in client;
    socklen_t  client_addrlength = sizeof(client);
    SOCKET connfd = accept(sock, (struct sockaddr*)&client, &client_addrlength);
    if (connfd == INVALID_SOCKET) {
        printf("WSAGetLastError() is: %d\n", WSAGetLastError());
    } else {
        char buffer[BUF_SIZE];
        ssize_t bytes;

        memset(buffer, '\0', BUF_SIZE);
        bytes = recv(connfd, buffer, BUF_SIZE-1, 0);
        printf("got %zd bytes of normal data '%s'\n", bytes, buffer);

        memset(buffer, '\0', BUF_SIZE);
        bytes = recv(connfd, buffer, BUF_SIZE-1, MSG_OOB);
        printf("got %zd bytes of oob data '%s'\n", bytes, buffer);

        memset(buffer, '\0', BUF_SIZE);
        bytes = recv(connfd, buffer, BUF_SIZE-1, 0);
        printf("got %zd bytes of normal data '%s'\n", bytes, buffer);

        closesocket(connfd);
    }
    closesocket(sock);
    WSA_RELEASE
    return 0;
}