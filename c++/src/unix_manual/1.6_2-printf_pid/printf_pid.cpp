//
// Created by leever on 8/31/2022.
//

#include "printf_pid.h"

int main() {
#ifdef _WIN32
    int Pid = _getpid();
#else
    int Pid = getpid();
#endif
    printf("hello world from process ID %ld\n", (long)Pid);
    exit(0);
}