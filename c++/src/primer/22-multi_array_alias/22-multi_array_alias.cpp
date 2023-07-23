//
// Created by leever on 6/8/2022.
//
#include "primer.h"

int main() {
    int ia[3][4];
    using int_array = int[4];
    typedef int int_array[4];
    for(int_array *p = ia; p != ia + 3; ++p) {
        for(int *q = *p; q != *p + 4; ++q)
            std::cout << *q << ' ';
        std::cout << std::endl;
    }
}