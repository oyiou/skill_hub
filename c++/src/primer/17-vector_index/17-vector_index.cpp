//
// Created by leever on 6/8/2022.
//
#include "primer.h"

int main() {
    std::vector<unsigned> scores(11, 0);
    unsigned grade;
    while(std::cin >> grade) {
        if(grade <= 100)
            ++scores[grade / 10];
    }
}