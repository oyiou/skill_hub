//
// Created by leever on 2023/3/9.
//

#ifndef C_WINDOWS_HIGH_PERFORMANCE_SERVER_H
#define C_WINDOWS_HIGH_PERFORMANCE_SERVER_H

#include "common.h"

#include <winsock2.h>
#pragma comment(lib,"ws2_32.lib")
#include <windows.h>
#pragma comment(lib, "wsock32.lib")
#include <ws2tcpip.h>
#include <namedpipeapi.h>
#pragma comment(lib, "Kernel32.lib")

#define WSA_INIT \
WSADATA wsaData; \
int nResult; \
nResult = WSAStartup(MAKEWORD(2, 2), &wsaData); \
if (nResult != 0) \
{ \
printf("WSAStartup failed: %d\n", nResult); \
return 1; \
}

#define WSA_RELEASE WSACleanup();

#endif //C_WINDOWS_HIGH_PERFORMANCE_SERVER_H
