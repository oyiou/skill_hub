//
// Created by leever on 2023/3/10.
//
#include "high_performance_server.h"

struct hostent *gethostbyname(const char *name);
struct hostent *gethostbyaddr(const void *addr, size_t len, int type);