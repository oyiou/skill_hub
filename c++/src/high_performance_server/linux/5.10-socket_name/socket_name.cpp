//
// Created by leever on 2023/3/9.
//
#include "high_performance_server.h"

int getsockname(int sockfd, struct sockaddr *address, socklen_t *address_len);
int getpeername(int sockfd, struct sockaddr *address, socklen_t *address_len);