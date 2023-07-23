//
// Created by leever on 2023/2/1.
//

#include <cstdio>
#include <pthread.h>

int pthread_create(
        pthread_t*,
        const pthread_attr_t*,
        void * (*)(void *),
        void *
        ) __attribute__ ((weak));

int main()
{
    if(pthead_create) {
        printf("This is multi-thread version!\n");
        // run th multi-thread version
        // main_multi_thread()
    } else {
        printf("This is single-thread version!\n");
        // run the single-thread version
        // main_single_thread
    }
}
