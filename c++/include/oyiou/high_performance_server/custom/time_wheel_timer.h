//
// Created by leever on 2023/3/20.
//

#ifndef C_TIME_WHEEL_TIMER_H
#define C_TIME_WHEEL_TIMER_H

#include "high_performance_server.h"

#define BUFFER_SIZE 64
class tw_timer;
// 绑定 socket 和定时器
struct client_data {
    sockaddr_in address;
    int sock_fd;
    char buf[BUFFER_SIZE];
    tw_timer *timer;
};
// 定时器类
class tw_timer {
public:
    tw_timer(int rot, int ts);
public:
    int rotation;   // 记录定时器在时间轮多少圈后生效
    int time_slot;  // 记录定时器属于时间轮上哪个槽
    void (*cb_func)(client_data*);  // 定时器回调函数
    client_data *user_data; // 客户数据
    tw_timer *next; // 指向下一个定时器
    tw_timer *prev; // 指向前一个定时器
};

class time_wheel {
public:
    time_wheel();
    ~time_wheel();
    // 根据定时值 timeout 创建一个定时器，并把它插入合适的槽中
    tw_timer *add_timer (int timeout);
    // 删除目标定时器 timer
    void del_timer (tw_timer *timer);
    // SI 时间到后，调用该函数，时间轮向前滚动一个槽的间隔
    void tick();
private:
    // 时间轮上槽的数目
    static const int N = 60;
    // 每 1s 时间轮转动一次，即槽间隔为 1s
    static const int SI = 1;
    // 时间轮的槽，其中每个元素指向一个定时器链表，链表无序
    tw_timer *slots[N];
    int cur_slot;   // 时间轮的当前槽
};

#endif //C_TIME_WHEEL_TIMER_H
