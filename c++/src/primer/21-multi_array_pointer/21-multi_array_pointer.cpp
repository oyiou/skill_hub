//
// Created by leever on 6/8/2022.
//
#include "primer.h"

int main() {
    int ia[3][4];
    for(auto p = ia; p != ia + 3; ++p) {
        for(auto q = *p; q != *p + 4; ++ q)
            std::cout << *q << ' ';
        std::cout << std::endl;
    }
}