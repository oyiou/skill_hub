//
// Created by leever on 2023/3/23.
//
#include "min_heap.h"

heap_timer::heap_timer(int delay) {
    expire = time(NULL) + delay;
}

// 构造函数之一，初始化一个大小为 cap 的空堆
time_heap::time_heap(int cap) throw(std::exception): capacity(cap), cur_size(0) {
    array = new heap_timer*[capacity];   // 创建堆数组
    if (!array) {
        throw std::exception();
    }
    for (int i = 0; i < capacity; ++i) {
        array[i] = NULL;
    }
}
// 构造函数之二，用已有数组来初始化堆
time_heap::time_heap(heap_timer **init_array, int size, int capacity) throw(std::exception): cur_size(size), capacity(capacity) {
    if (capacity < size) {
        throw std::exception();
    }
    array = new heap_timer*[capacity];  // 创建堆数组
    if (!array) {
        throw std::exception();
    }
    for (int i = 0; i < capacity; ++i) {
        array[i] = NULL;
    }
    if (size != 0) {
        // 初始化堆数组
        for (int i = 0; i < size; ++i) {
            array[i] = init_array[i];
        }
        for (int i = (cur_size-1)/2; i >= 0; --i) {
            // 对数组中的第 [(cur_size-1)/2] ~ 0 个元素执行下虑操作
            percolate_down(i);
        }
    }
}
// 销毁时间堆
time_heap::~time_heap() {
    for (int i = 0; i < cur_size; ++i) {
        delete array[i];
    }
    delete [] array;
}

// 添加目标定时器 timer
void time_heap::add_timer(heap_timer *timer) throw(std::exception) {
    if (!timer) {
        return;
    }
    if (cur_size >= capacity) { // 如果当前堆数组容量不够，则将其扩大一倍
        resize();
    }
    // 新插入一个元素，当前堆大小加一，hole是新建空穴的位置
    int hole = cur_size++;
    int parent = 0;
    // 对从空穴到根节点的路径上的所有节点执行上虑操作
    for (; hole > 0; hole = parent) {
        parent = (hole-1)/2;
        if (array[parent]->expire <= timer->expire) {
            break;
        }
        array[hole] = array[parent];
    }
    array[hole] = timer;
}
// 删除目标定时器 timer
void time_heap::del_timer(heap_timer *timer) {
    if (!timer) {
        return;
    }
    // 仅仅将目标定时器的回调函数设置为空，即所谓的延迟销毁。这将节省真正删除该定时器造成的开销，但这样做容易使堆数组膨胀
    timer->cb_func = NULL;
}
// 获得堆顶部的定时器
heap_timer *time_heap::top() const {
    if (empty()) {
        return NULL;
    }
    return array[0];
}
// 删除堆顶部的定时器
void time_heap::pop_timer() {
    if (empty()) {
        return;
    }
    if (array[0]) {
        delete array[0];
        // 将原来的堆顶元素替换为数组中最后一个元素
        array[0] = array[--cur_size];
        percolate_down(0);  // 对新的堆元素执行下虑操作
    }
}
// 心搏函数
void time_heap::tick() {
    heap_timer *tmp = array[0];
    time_t cur = time(NULL);    // 循环处理堆中到期的定时器
    while (!empty()) {
        if (!tmp) {
            break;
        }
        // 如果堆顶定时器没到期，则退出循环
        if (tmp->expire > cur) {
            break;
        }
        // 否则就执行堆顶定时器中的任务
        if (array[0]->cb_func) {
            aray[0]->cb_func(array[0]->user_data);
        }
        // 将堆顶元素删除，同时生成新的堆顶定时器 array[0]
        pop_timer();
        tmp = array[0];
    }
}
bool time_heap::empty() const {return cur_size == 0;}
// 最小堆的下虑操作，它确保堆数组中以第 hole 个节点作为根的子树拥有最小堆性质
void time_heap::percolate_down(int hole) {
    heap_timer *temp = array[hole];
    int child = 0;
    for (; ((hole*2+1) <= (cur_size-1)); hole=child) {
        child = hole*2+1;
        if ((child < (cur_size-1)) && (array[child+1]->expire < array[child]->expire)) {
            ++child;
        }
        if (array[child]->expire < temp->expire) {
            array[hole] = array[child];
        } else {
            break;
        }
    }
    array[hole] = temp;
}
// 将堆数组容量扩大一倍
void time_heap::resize() throw(std::exception) {
    heap_timer **temp = new heap_timer *[2*capacity];
    for (int i = 0; i < 2 * capacity; ++i) {
        temp[i] = NULL;
    }
    if (!temp) {
        throw std::exception();
    }
    capacity = 2*capacity;
    for (int i = 0; i < 2 * capacity; ++i) {
        temp[i] = array[i];
    }
    delete [] array;
    array = temp;
}