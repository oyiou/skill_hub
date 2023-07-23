//
// Created by leever on 6/14/2022.
//
#include "primer.h"

void print(const char *cp) {
    if(cp)
        while(*cp)
            std::cout << *cp++;
}
int main() {
    const char *str = "a string";
    print(str);
    return 0;
}