//
// Created by leever on 2023/3/21.
//

#ifndef C_LOCKER_H
#define C_LOCKER_H

#include "high_performance_server.h"
// 封装信号的类
class sem {
private:
    sem_t m_sem;
public:
    // 创建并初始化信号量
    sem();
    // 销毁信号量
    ~sem();
    // 等待信号量
    bool wait();
    // 增加信号量
    bool post();
};
// 封装互斥锁的类
class locker {
private:
    pthread_mutex_t m_mutex;
public:
    // 创建并初始化互斥锁
    locker();
    // 销毁互斥锁
    ~locker();
    // 获取互斥锁
    bool lock();
    // 释放互斥锁
    bool unlock();
};
// 封装条件变量的类
class cond {
private:
    pthread_mutex_t m_mutex;
    pthread_cond_t m_cond;
public:
    // 创建并初始化标间变量
    cond();
    // 销毁条件变量
    ~cond();
    // 等待条件变量
    bool wait();
    // 唤醒等待条件变量的线程
    bool signal() ;
};

#endif //C_LOCKER_H
