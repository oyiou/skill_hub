//
// Created by leever on 6/8/2022.
//
#include "primer.h"

int main() {
    int ia[2][3];
    size_t cnt = 0;
    for(auto &row : ia)
        for(auto &col : row) {
            col = cnt;
            ++cnt;
        }
}