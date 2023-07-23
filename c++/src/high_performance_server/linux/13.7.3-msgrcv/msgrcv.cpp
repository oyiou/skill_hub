//
// Created by leever on 2023/3/21.
//
#include "high_performance_server.h"

int msgrcv(int msqid, void *msg_ptr, size_t msg_sz, long int msgtype, int msgflg);