//
// Created by leever on 2023/3/21.
//
#include "high_performance_server.h"

int pthread_create(pthread_t *thread, const pthread_attr_t *attr, void *(*start_routine)(void *), void *arg);