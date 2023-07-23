//
// Created by leever on 3/6/23.
//
#include <sys/un.h>

struct  sockaddr_un
{
    sa_family_t sin_family; // 地址族：AF_UNIX
    char sun_path[108]; // 文件路径名
};