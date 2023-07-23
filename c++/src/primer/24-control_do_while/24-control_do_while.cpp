//
// Created by leever on 6/13/2022.
//
#include "primer.h"

int main() {
    std::string rsp;
    do {
        std::cout << "Please enter two values: ";
        int val1 = 0, val2 = 0;
        std::cin >> val1 >> val2;
        std::cout << "The sum of " << val1 << " and " << val2
                  << " = " << val1 + val2 << "\n\n"
                  << "More? Enter yes or no: ";
        std::cin >> rsp;
    } while(!rsp.empty() && rsp[0] != 'n');
}