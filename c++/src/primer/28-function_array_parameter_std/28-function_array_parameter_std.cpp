//
// Created by leever on 6/14/2022.
//
#include "primer.h"

void print(const int *beg, const int *end) {
    while(beg != end)
        std::cout << *beg++ << std::endl;
}
int main() {
    int arr[] = {1,2,3};
    print(std::begin(arr), std::end(arr));
    return 0;
}