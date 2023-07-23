//
// Created by leever on 3/7/23.
//
#include "high_performance_server.h"

int main(int argc, char *argv[])
{
    if (argc <= 2) {
        printf("usage: %s ip_address port_number\n", basename(argv[0]));
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

    SOCKET sockfd = socket(PF_INET, SOCK_STREAM, 0);
    assert(sockfd != INVALID_SOCKET);
    SOCKET  conncheck = connect(sockfd, (struct sockaddr*)&server_address, sizeof(server_address));
    if (conncheck == SOCKET_ERROR) {
        printf("connection failed\n");
    } else {
        const char *oob_data = "abc";
        const char *normal_data = "123";
        int oob_data_len, normal_data_len;
        oob_data_len = (int)strlen(oob_data);
        normal_data_len = (int)strlen(normal_data);
        send(sockfd, normal_data, normal_data_len, 0);
        send(sockfd, oob_data, oob_data_len, MSG_OOB);
        send(sockfd, normal_data, normal_data_len, 0);
    }

    closesocket(sockfd);
    WSA_RELEASE
    return 0;
}