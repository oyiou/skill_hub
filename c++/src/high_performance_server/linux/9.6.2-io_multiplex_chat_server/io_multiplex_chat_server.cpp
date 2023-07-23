//
// Created by leever on 2023/3/15.
//
#define _GNU_SOURCE 1
#include "high_performance_server.h"

#define USER_LIMIT 5    // 最大用户数量
#define BUFFER_SIZE 64  // 读缓冲区的大小
#define FD_LIMIT 65535  // 文件描述符数量限制
// 客户数据：客户端 socket 地址、待写到客户端的数据的位置、从客户端读入的数据
struct client_data {
    sockaddr_in address;
    char *write_buf;
    char buf[BUFFER_SIZE];
};

int set_non_blocking (int fd) {
    int old_option = fcntl(fd, F_GETFL);
    int new_option = old_option | O_NONBLOCK;
    fcntl(fd, F_SETFL, new_option);
    return old_option;
}

int main (int argc, char *argv[]) {
    if (argc <= 2) {
        printf("usage: %s ip_address port_number\n", basename(argv[0]));
        return 1;
    }
    const char *ip = argv[1];
    int port = atoi(argv[2]);

    int ret = 0;
    struct sockaddr_in address;
    bzero(&address, sizeof(address));
    address.sin_family = AF_INET;
    inet_pton(AF_INET, ip, &address.sin_addr);
    address.sin_port = htons(port);

    int listen_fd = socket(PF_INET, SOCK_STREAM, 0);
    assert(listen_fd >= 0);

    ret = bind(listen_fd, (struct sockaddr*)&address, sizeof(address));
    assert(ret != -1);

    ret = listen(listen_fd, 5);
    assert(ret != -1);

    // 创建 users 数组，分配 FD_LIMIT 个 client_data 对象。可以预期：每个可能的 socket 连接都可以获得一个这样的对象，并且 socket 的值可以直接用来索引（作为数组的下标）socket 连接对应的 client_data 对象，这是将 socket 和客户数据关联的简单而高效的方式
    client_data *users = new client_data[FD_LIMIT];
    // 尽管分配了足够多的 client_data 对象，但为了提高 poll 的性能，仍然有必要限制用户的数量
    pollfd fds[USER_LIMIT + 1];
    int user_counter = 0;
    for (int i = 0; i < USER_LIMIT; ++i) {
        fds[i].fd = -1;
        fds[i].events = 0;
    }
    fds[0].fd = listen_fd;
    fds[0].events = POLLIN | POLLERR;
    fds[0].revents = 0;

    while (1) {
        ret = poll(fds, user_counter + 1, -1);
        if (ret < 0) {
            printf("poll failure\n");
            break;
        }

        for (int i = 0; i < user_counter + 1; ++i) {
            if ((fds[i].fd == listen_fd) && (fds[i].revents & POLLIN)) {
                struct sockaddr_in client_address;
                socklen_t client_addr_length = sizeof(client_address);
                int conn_fd = accept(listen_fd, (struct sockaddr*)&client_address, &client_addr_length);
                if (conn_fd < 0) {
                    printf("errno is: %d\n",errno);
                    continue;
                }
                // 如果请求太多，则关闭新到的连接
                if (user_counter >= USER_LIMIT) {
                    const char *info = "too many users\n";
                    printf("%s", info);
                    send(conn_fd, info, strlen(info), 0);
                    close(conn_fd);
                    continue;
                }
                // 对于新的连接，同时修改 fds 和 users 数组，users[conn_fd] 对应新连接文件描述符 conn_fd 的客户数据
                user_counter++;
                users[conn_fd].address = client_address;
                set_non_blocking(conn_fd);
                fds[user_counter].fd = conn_fd;
                fds[user_counter].events = POLLIN | POLLRDHUP | POLLERR;
                fds[user_counter].revents = 0;
                printf("comes a new user, new have %d uesrs\n", user_counter);
            } else if (fds[i].revents & POLLERR) {
                printf("get an error from %d\n", fds[i].fd);
                char errors[100];
                memset(errors, '\0', 100);
                socklen_t length = sizeof(errors);
                if (getsockopt(fds[i].fd, SOL_SOCKET, SO_ERROR, &errors, &length) < 0) {
                    printf("get socket option failed\n");
                }
                continue;
            } else if (fds[i].revents & POLLRDHUP) {
                // 如果客户端关闭连接，则服务器也关闭对应的连接，并将用户总数减一
                users[fds[i].fd] = users[fds[user_counter].fd];
                close(fds[i].fd);
                fds[i] = fds[user_counter];
                i--;
                user_counter--;
                printf("a client left\n");
            } else if (fds[i].revents & POLLIN) {
                int conn_fd = fds[i].fd;
                memset(users[conn_fd].buf, '\0', BUFFER_SIZE);
                ret = recv(conn_fd, users[conn_fd].buf, BUFFER_SIZE - 1, 0);
                printf("get %d bytes of client data %s from %d\n", ret, users[conn_fd].buf, conn_fd);
                if (ret < 0) {
                    // 如果读操作出错，则关闭连接
                    if (errno != EAGAIN) {
                        close(conn_fd);
                        users[fds[i].fd] = users[fds[user_counter].fd];
                        fds[i] = fds[user_counter];
                        i--;
                        user_counter--;
                    }
                } else if (ret == 0) {

                } else {
                    // 如果接收到客户数据，则通知其他 socket 连接准备写数据
                    for (int j = 1; j < user_counter; ++j) {
                        if (fds[j].fd == conn_fd) {
                            continue;
                        }
                        fds[j].events |= ~POLLIN;
                        fds[j].events |= POLLOUT;
                        users[fds[j].fd].write_buf = users[conn_fd].buf;
                    }
                }
            } else if (fds[i].revents & POLLOUT) {
                int conn_fd = fds[i].fd;
                if (!users[conn_fd].write_buf) {
                    continue;
                }
                ret = send(conn_fd, users[conn_fd].write_buf, strlen(users[conn_fd].write_buf), 0);
                users[conn_fd].write_buf = NULL;
                // 写完数据后需要重新注册 fds[i] 上的可读事件
                fds[i].events |= ~POLLOUT;
                fds[i].events |= POLLIN;
            }
        }
    }

    delete [] users;
    close(listen_fd);
    return 0;
}