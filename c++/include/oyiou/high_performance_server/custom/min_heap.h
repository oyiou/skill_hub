//
// Created by leever on 2023/3/20.
//

#ifndef C_MIN_HEAP_H
#define C_MIN_HEAP_H

#include "high_performance_server.h"

using std::exception;

#define BUFFER_SIZE 64

class heap_timer;   // 前向声明
// 绑定 socket 和定时器
struct client_data {
    sockaddr_in address;
    int sock_fd;
    char buf[BUFFER_SIZE];
    heap_timer *timer;
};
// 定时器类
class heap_timer {
public:
    heap_timer(int delay);
public:
    time_t expire;  // 定时器生效的绝对时间
    void (*cb_func)(client_data*);  // 定时器的对调函数
    client_data *user_data; // 用户数据
};
// 时间堆类
class time_heap {
public:
    // 构造函数之一，初始化一个大小为 cap 的空堆
    time_heap(int cap) throw(std::exception);
    // 构造函数之二，用已有数组来初始化堆
    time_heap(heap_timer **init_array, int size, int capacity) throw(std::exception);
    // 销毁时间堆
    ~time_heap();
public:
    // 添加目标定时器 timer
    void add_timer(heap_timer *timer) throw(std::exception);
    // 删除目标定时器 timer
    void del_timer(heap_timer *timer);
    // 获得堆顶部的定时器
    heap_timer *top() const;
    // 删除堆顶部的定时器
    void pop_timer();
    // 心搏函数
    void tick();
    bool empty() const;
private:
    // 最小堆的下虑操作，它确保堆数组中以第 hole 个节点作为根的子树拥有最小堆性质
    void percolate_down(int hole);
    // 将堆数组容量扩大一倍
    void resize() throw(std::exception);
private:
    heap_timer **array; // 堆数组
    int capacity;   // 堆数组的容量
    int cur_size;   // 堆数组当前包含元素的个数
};

#endif //C_MIN_HEAP_H
