//
// Created by leever on 8/31/2022.
//

#include "std_getc_to_putc.h"

int main() {
    int c;
    while((c = getc(stdin)) != EOF)
        if(putc(c, stdout) == EOF)
            err_sys("output error");
    if(ferror(stdin))
        err_sys("input error");
    exit(0);
}