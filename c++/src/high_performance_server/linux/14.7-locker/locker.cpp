//
// Created by leever on 2023/3/23.
//
#include "locker.h"

// 创建并初始化信号量
sem::sem() {
    if (sem_init(&m_sem, 0, 0) != 0) {
        // 构造函数没有返回值，可以通过抛出异常来报告错误
        throw std::exception();
    }
}
// 销毁信号量
sem::~sem() {
    sem_destroy(&m_sem);
}
// 等待信号量
bool sem::wait() {
    return sem_wait(&m_sem) == 0;
}
// 增加信号量
bool sem::post() {
    return sem_post(&m_sem) == 0;
}

// 创建并初始化互斥锁
locker::locker() {
    if (pthread_mutex_init(&m_mutex, NULL) != 0) {
        throw std::exception();
    }
}
// 销毁互斥锁
locker::~locker() {
    pthread_mutex_destroy(&m_mutex);
}
// 获取互斥锁
bool locker::lock() {
    return pthread_mutex_lock(&m_mutex) == 0;
}
// 释放互斥锁
bool locker::unlock() {
    return pthread_mutex_unlock(&m_mutex) == 0;
}

// 创建并初始化标间变量
cond::cond() {
    if (pthread_mutex_init(&m_mutex, NULL) != 0) {
        throw std::exception();
    }
    if (pthread_mutex_init(&m_cond, NULL) != 0) {
        // 构造函数中一旦出现问题，就应该立即释放已经成功分配了的资源
        pthread_mutex_destroy(&m_mutex);
        throw std::exception();
    }
}
// 销毁条件变量
cond::~cond() {
    pthread_mutex_destroy(&m_mutex);
    pthread_mutex_destroy(&m_cond);
}
// 等待条件变量
bool cond::wait() {
    int ret = 0;
    pthread_mutex_lock(&m_mutex);
    ret = pthread_cond_wait(&m_cond, &m_mutex);
    pthread_mutex_unlock(&m_mutex);
    return ret == 0;
}
// 唤醒等待条件变量的线程
bool cond::signal() {
    return pthread_cond_signal(&m_cond) == 0;
}
