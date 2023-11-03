//
// Created by leever on 3/6/23.
//
#include "oyiou/high_performance_server/windows/high_performance_server.h"

static bool stop = false;
// SIGTERM 信号的处理函数，触发时结束主进程中的循环
static void handle_term(int sig)
{
    stop = true;
}
int main(int argc, char *argv[])
{
    signal(SIGTERM, handle_term);
    if (argc <= 3)
    {
        printf("usage: %s ip_address port_number backlog\n", basename(argv[0]));
        return 1;
    }

    WSA_INIT

    const char *ip = argv[1];
    char *endptr;
    int port = (int)strtol(argv[2], &endptr, 0);
    int backlog = (int)strtol(argv[3], &endptr, 0);

    SOCKET sock = socket(PF_INET, SOCK_STREAM, 0);
    assert(sock != INVALID_SOCKET);

    // 创建一个 IPv4 socket 地址
    struct sockaddr_in address;
    memset(&address, 0, sizeof(address));
    address.sin_family = AF_INET;
    inet_pton(AF_INET, ip, &address.sin_addr);
    address.sin_port = htons(port);

    int ret = bind(sock, (struct sockaddr*)&address, sizeof(address));
    assert(ret != SOCKET_ERROR);

    ret = listen(sock, backlog);
    assert(ret != SOCKET_ERROR);

    // 循环等待连接，直到有 SIGTERM 信号将它中断
    while (!stop)
    {
        sleep(1);
    }

    // 关闭 socket
    closesocket(sock);
    WSA_RELEASE
    return 0;
}