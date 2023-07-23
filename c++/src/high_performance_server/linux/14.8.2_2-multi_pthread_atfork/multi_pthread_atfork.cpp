//
// Created by leever on 2023/3/22.
//
#include "high_performance_server.h"

int pthread_atfork(void (*prepare)(void), void (*parent)(void), void (*child)(void));

void prepare() {
    pthread_mutex_lock(&mutex);
}
void infork() {
    pthread_mutex_unlock(&mutex);
}
pthread_atfork(prepare, infork, infork);