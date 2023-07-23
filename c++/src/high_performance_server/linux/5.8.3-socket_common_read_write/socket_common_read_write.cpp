//
// Created by leever on 2023/3/9.
//
#include "high_performance_server.h"

ssize_t recvmsg(int sockfd, struct msghdr* msg, int flags);
ssize_t sendmsg(int sockfd, struct msghdr* msg, int flags);