//
// Created by leever on 8/31/2022.
//

#include "std_read_to_write.h"

int main() {
    int n;
    char buf[BUFFSIZE];
    while((n = read(STDIN_FILENO, buf, BUFFSIZE)) > 0)
        if(write(STDOUT_FILENO, buf, n) != n)
            err_sys("write error");
    if(n < 0)
        err_sys("read error");
    exit(0);
}