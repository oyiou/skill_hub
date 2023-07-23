//
// Created by leever on 2023/3/23.
//
#include "processpool.h"

// 用于处理客户 CGI 请求的类，它可以作为 processpool 类的模板参数
class cgi_conn {
private:
    // 读缓冲区的大小
    static const int BUFFER_SIZE = 1024;
    static int m_epoll_fd;
    int m_sock_fd;
    sockaddr_in m_address;
    char m_buf[BUFFER_SIZE];
    // 标记读缓冲区已经读入的客户数据的最后一个字节的下一个位置
    int m_read_idx;
public:
    cgi_conn() {}
    ~cgi_conn() {}
    // 初始化客户连接，清空读缓冲区
    void init(int epoll_fd, int sock_fd, const sockaddr_in &client_addr) {
        m_epoll_fd = epoll_fd;
        m_sock_fd = sock_fd;
        m_address = client_addr;
        memset(m_buf, '\0', BUFFER_SIZE);
        m_read_idx = 0;
    }

    void process() {
        int idx = 0;
        int ret = -1;
        // 循环读取和分析客户数据
        while (true) {
            idx = m_read_idx;
            ret = recv(m_sock_fd, m_buf + idx, BUFFER_SIZE - 1 - idx, 0);
            // 如果读操作发生错误，则关闭客户连接，但如果是暂时无数据可读，则退出循环
            if (ret < 0) {
                if (errno != EAGAIN) {
                    remove_fd(m_epoll_fd, m_sock_fd);
                }
                break;
            } else if (ret == 0) {  // 如果对方关闭连接，则服务器也关闭连接
                remove_fd(m_epoll_fd, m_sock_fd);
                break;
            } else {
                m_read_idx += ret;
                printf("user content is: %s\n", m_buf);
                // 如果遇到字符 \r\n，则开始处理客户请求
                for (; idx < m_read_idx; ++idx) {
                    if ((idx >= 1) && (m_buf[idx - 1] == '\r') && (m_buf[idx] == '\n')) {
                        break;
                    }
                }
                // 如果没有遇到字符 \r\n，则需要读取更多客户数据
                if (idx == m_read_idx) {
                    continue;
                }
                m_buf[idx - 1] = '\0';

                char *file_name = m_buf;
                // 判断客户要运行的 CGI 程序是否存在
                if (access(file_name, F_OK) == -1) {
                    remove_fd(m_epoll_fd, m_sock_fd);
                    break;
                }
                // 创建子进程来执行 CGI 程序
                ret = fork();
                if (ret == -1) {
                    remove_fd(m_epoll_fd, m_sock_fd);
                    break;
                } else if (ret > 0) {
                    // 父进程只需关闭连接
                    remove_fd(m_epoll_fd, m_sock_fd);
                    break;
                } else {
                    // 子进程将标准输出定向到 m_sock_fd，并执行 CGI 程序
                    close(STDOUT_FILENO);
                    dup(m_sock_fd);
                    execl(m_buf, m_buf, 0);
                    exit(0);
                }
            }
        }
    }
};
int cgi_conn::m_epoll_fd = -1;

// 主函数
int main(int argc, char *argv[]) {
    if (argc <= 2) {
        printf("usage: %s ip_address port_number\n", basename(argv[0]));
        return 1;
    }
    const char *ip = argv[1];
    int port = atoi(argv[2]);

    int listen_fd = socket(PF_INET, SOCK_STREAM, 0);
    assert(listen_fd >= 0);

    int ret = 0;
    struct sockaddr_in address;
    bzero(&address, sizeof(address));
    address.sin_family = AF_INET;
    inet_pton(AF_INET, ip, &address.sin_addr);
    address.sin_port = htons(port);

    ret = bind(listen_fd, (struct sockaddr*)&address, sizeof(address));
    assert(ret != -1);

    ret = listen(listen_fd, 5);
    assert(ret != -1);

    processpool<cgi_conn>* pool = processpool<cgi_conn>::create(listen_fd);
    if (pool) {
        pool->run();
        delete pool;
    }
    close(listen_fd);   // main 函数创建了文件描述符 listen_fd，那么就由
    return 0;
}