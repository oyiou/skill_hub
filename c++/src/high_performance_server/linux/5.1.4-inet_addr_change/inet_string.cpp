//
// Created by leever on 3/6/23.
//
#include <arpa/inet.h>
in_addr_t inet_addr(const char *strptr);
int inet_aton(const char *cp, struct in_addr* inp);
char *inet_ntoa(struct in_addr in);