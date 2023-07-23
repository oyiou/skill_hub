//
// Created by leever on 3/6/23.
//
#include <netinet/in.h>

struct sockaddr_in
{
    sa_family_t sin_family; // 地址族：AF_INET
    u_int16_t sin_port; // 端口号，要用网络字节序表示
    struct in_addr sin_addr;    // IPv4 地址结构体
};
struct in_addr
{
    u_int32_t s_addr;   // IPv4 地址，要用网络字节序表示
};
struct sockaddr_in6
{
    sa_family_t sin6_family;    // 地址族：AF_INET6
    u_int16_t sin6_port;    // 端口号，要用网络字节序表示
    u_int32_t sin6_flowinfo;    // 流信息，应设置为 0
    struct in6_addr sin6_addr;  // IPv6 地址结构体
    u_int32_t sin6_scope_id;    // scope ID，尚处于实验阶段
};
struct in6_addr
{
    unsigned char sa_addr[16];  // IPv6 地址，要用网络字节序表示
};