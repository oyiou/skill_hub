//
// Created by leever on 2023/4/12.
//
#include "data_structure.h"

void print1 (int *ptr, int rows) {
    int i;
    printf("Address Contents\n");
    for (i = 0; i < rows; i++) {
        printf("%8u%5d\n", ptr+i, *(ptr+i));
    }
}