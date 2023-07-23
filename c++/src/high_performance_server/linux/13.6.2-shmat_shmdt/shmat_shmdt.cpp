//
// Created by leever on 2023/3/21.
//
#include "high_performance_server.h"

void *shmat(int shm_id, const void *shm_addr, int shmflg);
int shmdt(const void *shm_addr);