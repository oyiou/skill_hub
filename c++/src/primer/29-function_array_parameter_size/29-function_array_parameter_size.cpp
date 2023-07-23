//
// Created by leever on 6/14/2022.
//
#include "primer.h"

void print(const int ia[], size_t size) {
    for(size_t i = 0; i != size; ++i) {
        std::cout << ia[i] << std::endl;
    }
}
int main() {
    int ia[] = {1,2,3};
    print(ia, sizeof(ia));
    return 0;
}