//
// Created by leever on 2023/3/9.
//
#include "high_performance_server.h"

int WSAAPI WSARecvFrom(
SOCKET                             s,
LPWSABUF                           lpBuffers,
DWORD                              dwBufferCount,
LPDWORD                            lpNumberOfBytesRecvd,
LPDWORD                            lpFlags,
struct sockaddr                    *lpFrom,
LPINT                              lpFromlen,
LPWSAOVERLAPPED                    lpOverlapped,
LPWSAOVERLAPPED_COMPLETION_ROUTINE lpCompletionRoutine
);
int WSAAPI WSASendMsg(
SOCKET                             Handle,
LPWSAMSG                           lpMsg,
DWORD                              dwFlags,
LPDWORD                            lpNumberOfBytesSent,
LPWSAOVERLAPPED                    lpOverlapped,
LPWSAOVERLAPPED_COMPLETION_ROUTINE lpCompletionRoutine
);