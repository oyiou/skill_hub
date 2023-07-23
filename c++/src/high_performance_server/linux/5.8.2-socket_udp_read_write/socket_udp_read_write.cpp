//
// Created by leever on 2023/3/8.
//
#include "high_performance_server.h"

ssize_t recvfrom(int sockfd, void *buf, size_t len, int flags, struct sockaddr* src_addr, socklen_t* addrlen);
ssize_t sendto(int sockfd, const void *buf, size_t len, int flags, const struct sockaddr* dest_addr, socklen_t addrlen);