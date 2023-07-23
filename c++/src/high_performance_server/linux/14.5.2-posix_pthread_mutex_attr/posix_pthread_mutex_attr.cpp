//
// Created by leever on 2023/3/21.
//
#include "high_performance_server.h"

// 初始化互斥锁属性对象
int pthread_mutexattr_init(pthread_mutexattr_t *attr);
// 销毁互斥锁属性对象
int pthread_mutexattr_destroy(pthread_mutexattr_t *attr);
// 获取和设置互斥锁的 pshared 属性
int pthread_mutexattr_getpshared(const pthread_mutexattr_t *attr, int *pshared);
int pthread_mutexattr_setpshared(pthread_mutexattr_t *attr, int pshared);
// 获取和设置互斥锁的 type 属性
int pthread_mutexattr_gettype(const pthread_mutexattr_t *attr, int *type);
int pthread_mutexattr_settype(pthread_mutexattr_t *attr, int type);