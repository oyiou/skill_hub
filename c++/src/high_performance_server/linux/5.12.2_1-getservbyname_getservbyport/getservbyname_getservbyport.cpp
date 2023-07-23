//
// Created by leever on 2023/3/10.
//
#include "high_performance_server.h"

struct servent *getservbyname(const char *name, const char *proto);
struct servent *getservbyport(int port, const char *proto);