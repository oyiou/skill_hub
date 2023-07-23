//
// Created by leever on 2023/3/22.
//

#ifndef C_PROCESSPOOL_H
#define C_PROCESSPOOL_H

#include "high_performance_server.h"
// 描述一个子进程的类，m_pid 是目标子进程的 PID，m_pipe_fd 是父进程和子进程通信用的管道
class process {
public:
    pid_t m_pid;
    int m_pipe_fd[2];
public:
    process(): m_pid(-1) {}
};
// 进程池类，将它定义为模板类是为了代码复用。其模板参数是处理逻辑任务的类
template<typename T>
class processpool {
private:
    // 进程池允许的最大子进程数量
    static const int MAX_PROCESS_NUMBER = 16;
    // 每个子进程最多能处理的客户数量
    static const int USER_PER_PROCESS = 65536;
    // epoll 最多能处理的事件数
    static const int MAX_EVENT_NUMBER = 10000;
    // 进程池中的进程总数
    int m_process_number;
    // 子进程在池中的序号，从 0 开始
    int m_idx;
    // 每个进程都有一个 epoll 内核事件表，用 m_epoll_fd 标识
    int m_epoll_fd;
    // 监听 socket
    int m_listen_fd;
    // 子进程通过 m_stop 来决定是否停止运行
    int m_stop;
    // 保存所有子进程的描述信息
    process *m_sub_process;
    // 进程池静态实例
    static processpool<T> *m_instance;
private:
    void setup_sig_pipe();
    void run_parent();
    void run_child();
private:
    // 将构造函数定义为私有的，因此只能通过后面的 create 静态函数来创建 processpool 实例
    processpool(int listen_fd, int process_number = 8);
public:
    // 单体模式，以保证程序最多创建一个 processpool 实例，这是程序正确处理信号的必要条件
    static processpool<T> *create(int listen_fd, int process_number = 8);
    ~processpool();
    // 启动进程池
    void run();
};

// 用于处理信号的管道，以实现统一事件源，后面称之为信号管道
static int sig_pipe_fd[2];

static int set_non_blocking (int fd);

static void add_fd (int epoll_fd, int fd);

// 从 epoll_fd 标识的 epoll 内核事件表中删除 fd 上的所有注册事件
static void remove_fd (int epoll_fd, int fd);

static void sig_handler (int sig);

static void add_sig (int sig, void (handler)(int), bool restart = true);

#endif //C_PROCESSPOOL_H
