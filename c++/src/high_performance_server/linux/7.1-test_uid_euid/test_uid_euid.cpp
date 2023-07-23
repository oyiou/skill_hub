//
// Created by leever on 2023/3/13.
//
#include "high_performance_server.h"

int main() {
    uid_t uid = getuid();
    uid_t euid = geteuid();
    printf("userid is %d, effective userid id: %d\n", uid, euid);
    return 0;
}