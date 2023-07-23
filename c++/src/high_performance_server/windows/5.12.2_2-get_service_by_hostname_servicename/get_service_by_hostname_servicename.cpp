//
// Created by leever on 2023/3/10.
//
#include "high_performance_server.h"

int main(int argc, char *argv[]) {
    assert(argc == 2);

    WSA_INIT

    char *host = argv[1];
    // 获取目标主机地址信息
    struct hostent *hostinfo = gethostbyname(host);
    assert(hostinfo);
    // 获取 daytime 服务信息
    struct servent *servinfo = getservbyname("daytime", "tcp");
    assert(servinfo);
    printf("daytime port is %d\n", htons(servinfo->s_port));

    struct sockaddr_in address;
    address.sin_family = AF_INET;
    address.sin_port = servinfo->s_port;
    // 因为 h_addr_list 本身是使用网络字节序的地址列表，所以使用其中的 IP 地址时，无须对目标地址转换字节序
    address.sin_addr = *(struct in_addr*)*hostinfo->h_addr_list;

    SOCKET sockfd = socket(AF_INET, SOCK_STREAM, 0);
    int result = connect(sockfd, (struct sockaddr*)&address, sizeof(address));
    printf("GetLastError is %lu\n", GetLastError());
    assert(result != SOCKET_ERROR);

    char buffer[128];
    result = recv(sockfd, buffer, 128-1, 0);
    assert(result != SOCKET_ERROR);
    buffer[result] = '\0';
    printf("the day time is %s", buffer);
    closesocket(sockfd);
    WSA_RELEASE
    return 0;
}