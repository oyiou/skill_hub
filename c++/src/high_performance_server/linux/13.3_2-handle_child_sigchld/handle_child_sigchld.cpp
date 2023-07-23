//
// Created by leever on 2023/3/21.
//
#include "high_performance_server.h"

static void handle_child(int sig) {
    pid_t pid;
    int stat;
    while ((pid = waitpid(-1, &stat, WNOHANG)) > 0) {
        // 对结束的子进程进行善后处理
    }
}