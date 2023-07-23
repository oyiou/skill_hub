//
// Created by leever on 5/26/2022.
//
#include "primer.h"
int main() {
    int sum = 0, value = 0;
    while (std::cin >> value)
        sum += value;
    std::cout << "Sum is: " << sum << std::endl;
    return 0;
}