//
// Created by leever on 2023/3/20.
//

#ifndef C_ASCEND_TIMER_LIST_H
#define C_ASCEND_TIMER_LIST_H

#include "high_performance_server.h"
#define BUFFER_SIZE 64
class util_timer;   // 前向声明
// 用户数据结构：客户端 socket 地址、socket 文件描述符、读缓存和定时器
struct client_data {
    sockaddr_in address;
    int sock_fd;
    char buf[BUFFER_SIZE];
    util_timer *timer;
};
// 定时器类
class util_timer {
public:
    util_timer(): prev(NULL), next(NULL) {}
public:
    time_t expire;  // 任务的超时时间，这里使用绝对时间
    void (*cb_func) (client_data*); // 任务回调函数
    // 回调函数处理的客户端，由定时器的执行者传递给回调函数
    client_data *user_data;
    util_timer *prev;    // 指向前一个定时器
    util_timer *next;   // 指向下一个定时器
};
// 定时器链表。它是一个升序、双向链表，且带有头节点和尾节点
class sort_timer_lst {
public:
    sort_timer_lst();
    // 链表被销毁时，删除其中所有的定时器
    ~sort_timer_lst();
    // 将目标定时器 timer 添加到链表中
    void add_timer (util_timer *timer);
    // 当某个定时任务发生变化时，调整对应的定时器在链表中的位置。这个函数只考虑被调整的定时器的超时时间延长的情况，即该定时器需要往链表的尾部移动
    void abjust_timer (util_timer *timer);
    // 将目标定时器 timer 从链表中删除
    void del_timer (util_timer *timer);
    // SIGALRM 信号每次被触发就在其信号处理函数（如果使用统一事件源，则是主函数）中执行一次 tick 函数，以处理表上到期的任务
    void tick();
private:
    // 一个重载的辅助函数，它被共有的 add_timer 函数和 abjust_timer 函数调用。该函数表示将目标定时器 timer 添加到节点 lst_head 之后的部分链表中
    void add_timer (util_timer *timer, util_timer *lst_head);
private:
    util_timer *head;
    util_timer *tail;
};

#endif //C_ASCEND_TIMER_LIST_H
