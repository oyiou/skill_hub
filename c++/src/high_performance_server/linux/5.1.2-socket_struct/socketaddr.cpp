//
// Created by leever on 2023/3/3.
//
#include <bits/socket.h>

struct sockaddr {
    sa_family_t sa_family;
    char sa_data[14];
};