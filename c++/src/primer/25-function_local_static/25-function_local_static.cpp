//
// Created by leever on 6/13/2022.
//
#include "primer.h"

size_t count_calls() {
    static size_t ctr = 0;
    return ++ctr;
}
int main() {
    for(size_t i = 0; i != 10; ++i)
        std::cout << count_calls() << std::endl;
    return 0;
}