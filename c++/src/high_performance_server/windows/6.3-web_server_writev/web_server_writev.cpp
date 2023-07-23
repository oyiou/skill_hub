//
// Created by leever on 2023/3/11.
//
#include "custom/uio.h"
#include "high_performance_server.h"

#define BUFFER_SIZE 1024
// 定义两种 HTTP 状态码和状态信息
static const char *status_line[2] = {"200 OK", "500 Internal server error"};

int main(int argc, char *argv[]) {
    if (argc <= 3) {
        printf("usage: %s ip_address port_number filename\n", basename(argv[0]));
        return 1;
    }
    WSA_INIT
    const char *ip = argv[1];
    char *endptr;
    int port = (int)strtol(argv[2], &endptr, 0);
    // 将目标文件作为程序的第三个数据参数传入
    const char *file_name = argv[3];

    struct sockaddr_in address{};
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

    struct sockaddr_in client{};
    socklen_t client_addrlength = sizeof(client);
    SOCKET connfd = accept(sock, (struct sockaddr*)&client, &client_addrlength);
    if (connfd == INVALID_SOCKET) {
        printf("WSAGetLastError is: %d\n", WSAGetLastError());
    } else {
        // 用于保存 HTTP 应答的状态行、头部字段和一个空行的缓存区
        char header_buf[BUFFER_SIZE];
        memset(header_buf, '\0', BUFFER_SIZE);
        // 用于存放目标文件内同的应用程序缓存
        char *file_buf;
        // 用于获取目标文件的属性，比如是否为目录，文件大小等
        struct stat file_stat{};
        // 记录目标文件是否是有效文件
        bool valid = true;
        // 缓存区 header_buf 目前已经使用了多少字节的空间
        int len = 0;
        if (stat(file_name, &file_stat) < 0) {  // 目标文件不存在
            valid = false;
        } else {
            if (S_ISDIR(file_stat.st_mode)) {   // 目标文件是一个目录
                valid = false;
            } else if (file_stat.st_mode & S_IROTH) {   // 当前用户有读取目标文件的权限
                // 动态分配缓存区 file_buf，并指定其大小为目标文件的大小加一，然后将目标文件读入缓存区 file_buf 中
                int fd = open(file_name, O_RDONLY);
                file_buf = new char [file_stat.st_size + 1];
                memset(file_buf, '\0', file_stat.st_size + 1);
                if (read(fd, file_buf, file_stat.st_size) < 0) {
                    valid = false;
                }
            } else {
                valid = false;
            }
        }
        // 如果目标文件有效，则发送正常的 HTTP 应答
        if (valid) {
            // 将 HTTP 应答的状态行、“Content-Length”头部字段和一个空行依次加入 header_buf 中
            ret = snprintf(header_buf, BUFFER_SIZE-1, "%s %ld\r\n", "Content-Length: %d\r\n", file_stat.st_size);
            len += ret;
            ret = snprintf(header_buf, BUFFER_SIZE-1, "%s %s\r\n", "HTTP/1.1", status_line[0]);

            len += ret;
            snprintf(header_buf + len, BUFFER_SIZE-1-len, "%s", "\r\n");
            // 利用 writev 将 header_buf 和 file_buf 的内容一并写出
            struct iovec iv[2];
            iv[0].iov_base = header_buf;
            iv[0].iov_len = strlen(header_buf);
            iv[1].iov_base = file_buf;
            iv[1].iov_len = file_stat.st_size;
            writev(connfd, iv, 2);
        } else {
            ret = snprintf(header_buf, BUFFER_SIZE-1, "%s %zu\r\n", "HTTP/1.1", strlen(status_line[1]));

            len += ret;
            snprintf(header_buf + len, BUFFER_SIZE-1-len, "%s", "\r\n");
            send(connfd, header_buf, (int)strlen(header_buf), 0);
        }
        closesocket(connfd);
        delete [] file_buf;
    }
    closesocket(sock);
    WSA_RELEASE
    return 0;
}