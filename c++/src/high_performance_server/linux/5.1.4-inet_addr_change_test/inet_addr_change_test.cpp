//
// Created by leever on 2023/3/9.
//
#include "high_performance_server.h"

#define FIX 0
#define ANOTHER_WAY 0

#if FIX
#include <string.h>
#include <stdlib.h>
#else
#endif

int main()
{
    char *ipStr1 = "1.2.3.4",*ipStr2 = "10.194.71.69";
    struct in_addr inAddr1, inAddr2;
#if ANOTHER_WAY
    inet_aton(ipStr1, &inAddr1);
    inet_aton(ipStr2, &inAddr2);
#else
    in_addr_t ip1, ip2;
    ip1 = inet_addr(ipStr1);
    ip2 = inet_addr(ipStr2);
    inAddr1.s_addr = ip1;
    inAddr2.s_addr = ip2;
#endif
    printf("ip1: %d\n", inAddr1.s_addr);
    printf("ip2: %d\n", inAddr2.s_addr);
    char *szValue1, *szValue2;
#if FIX
    char *tmp;
    tmp = inet_ntoa(inAddr1);
    szValue1 = (char *) malloc(sizeof(tmp));
    strcpy(szValue1, tmp);
    tmp = inet_ntoa(inAddr2);
    szValue2 = (char *) malloc(sizeof(tmp));
    strcpy(szValue2, tmp);
#else
    szValue1 = inet_ntoa(inAddr1);
    szValue2 = inet_ntoa(inAddr2);
#endif
    printf("address 1: %s\n", szValue1);
    printf("address 2: %s\n", szValue2);
#if FIX
    free(szValue1);
    free(szValue2);
#else
#endif
    return 0;
}