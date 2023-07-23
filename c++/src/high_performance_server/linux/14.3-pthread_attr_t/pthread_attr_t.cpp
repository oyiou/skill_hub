//
// Created by leever on 2023/3/21.
//
#include "high_performance_server.h"

#define __SIZEOF_PTHREAD_ATTR_T 36
typedef union  {
    char __size[__SIZEOF_PTHREAD_ATTR_T];
    long int __align;
} pthread_attr_t;