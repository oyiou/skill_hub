//
// Created by leever on 2023/3/21.
//
#include "high_performance_server.h"

pid_t wait(int *stat_loc);
pid_t waitpid(pid_t pid, int *stat_loc, int options);