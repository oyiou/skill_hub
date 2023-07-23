//
// Created by leever on 2023/3/20.
//
#include "high_performance_server.h"

#define BUF_SIZE 1024

static int conn_fd;
// SIGURG 信号处理函数
void sig_urg (int sig) {
    int save_errno = errno;
    char buffer[BUF_SIZE];
    memset(buffer, '\0', BUF_SIZE);
    int ret = recv(conn_fd, buffer, BUF_SIZE - 1, MSG_OOB); // 接收带外数据
    printf("got %d bytes of oob data '%s'\n", ret, buffer);
    errno = save_errno;
}

void add_sig (int sig, void (*sig_handler)(int )) {
    struct sigaction sa;
    memset(&sa, '\0', sizeof(sa));
    sa.sa_handler = sig_handler;
    sa.sa_flags |= SA_RESTART;
    sigfillset(&sa.sa_mask);
    assert(sigaction(sig, &sa, NULL) != -1);
}