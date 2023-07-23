//
// Created by leever on 2023/3/10.
//
#include "high_performance_server.h"

struct addrinfo hints;
struct addrinfo *result;

bzero(&hints, sizeof(hints));
hints.ai_socktype = SOCK_STREAM;
getaddrinfo("ernest-laptop", "daytime", &hints, &result);