//
// Created by leever on 2023/3/14.
//
#include "high_performance_server.h"

int main(int argc, char *argv[]) {
    if (argc <= 2) {
        printf("usage: %s ip_address port_number\n", basename(argv[0]));
        return 1;
    }

    WSA_INIT

    const char *ip = argv[1];
    char *end_ptr;
    int port = (int)strtol(argv[2], &end_ptr, 0);

    int ret = 0;
    struct sockaddr_in address;
    memset(&address, '\0', sizeof(address));
    address.sin_family = AF_INET;
    inet_pton(AF_INET, ip, &address.sin_addr);
    address.sin_port = htons(port);

    SOCKET listen_fd = socket(PF_INET, SOCK_STREAM, 0);
    assert(listen_fd != INVALID_SOCKET);
    ret = bind(listen_fd, (struct sockaddr*)&address, sizeof(address));
    assert(ret != SOCKET_ERROR);
    ret = listen(listen_fd, 5);
    assert(ret != SOCKET_ERROR);

    struct sockaddr_in client_address;
    socklen_t client_addr_length = sizeof(client_address);
    SOCKET conn_fd = accept(listen_fd, (struct sockaddr*)&client_address, &client_addr_length);
    if (conn_fd == INVALID_SOCKET) {
        printf("errno is: %d\n", errno);
        closesocket(listen_fd);
    }

    char buf[1024];
    fd_set read_fds;
    fd_set exception_fds;
    FD_ZERO(&read_fds);
    FD_ZERO(&exception_fds);

    while (1) {
        memset(buf, '\0', sizeof(buf));
        // 每次调用 select 前都要重新在 read_fds 和 exception_fds 中设置文件描述符 conn_fd 因为事件发生后，文件描述符集合将被内核修改
        FD_SET(conn_fd, &read_fds);
        FD_SET(conn_fd, &exception_fds);
        ret = select(conn_fd, &read_fds, nullptr, &exception_fds, nullptr);
        if (ret < 0) {
            printf("selection failure\n");
            break;
        }

        // 对于可读事件，采用普通的 recv 函数读取数据
        if (FD_ISSET(conn_fd, &read_fds)) {
            ret = recv(conn_fd, buf, sizeof(buf) - 1, 0);
            if (ret <= 0) {
                break;
            }
            printf("get %d bytes of normal date: %s\n", ret, buf);
        } else if (FD_ISSET(conn_fd, &exception_fds)) { // 对于异常事件，采用带 MSG_OOB 标志的 recv 函数读取带外数据
            ret = recv(conn_fd, buf, sizeof(buf) - 1, MSG_OOB);
            if (ret <= 0) {
                break;
            }
            printf("get %d bytes of oob data: %s\n", ret, buf);
        }
    }
    closesocket(conn_fd);
    closesocket(listen_fd);
    WSA_RELEASE
    return 0;
}