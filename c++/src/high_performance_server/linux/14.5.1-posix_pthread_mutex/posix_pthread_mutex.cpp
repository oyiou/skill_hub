//
// Created by leever on 2023/3/21.
//
#include "high_performance_server.h"

int pthread_mutex_init(pthread_mutex_t *mutex, const pthread_mutex_t *mutexattr);
int pthread_mutex_destroy(pthread_mutex_t *mutex);
int pthread_mutex_lock(pthread_mutex_t *mutex);
int pthread_mutex_trylock(pthread_mutex_t *mutex);
int pthread_mutex_unlock(pthread_mutex_t *mutex);