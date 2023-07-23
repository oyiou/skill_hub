//
// Created by leever on 2023/3/9.
//
#include "high_performance_server.h"

int getsockopt(int sockfd, int level, int option_name, void *option_value, socklen_t* restrict option_len);
int setsockopt(int sockfd, int level, int option_name, const void *option_value, socklen_t option_len);