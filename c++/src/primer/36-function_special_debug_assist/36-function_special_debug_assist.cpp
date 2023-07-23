//
// Created by leever on 6/16/2022.
//
#include "primer.h"

int main() {
    char c;
    if(std::cin >> c)
        std::cerr << "Error: " << __FILE__
        << " : in function " << __func__
        << " at line " << __LINE__ << std::endl
        << " at " << __TIME__ << std::endl
        << " Word read was \"" << c
        << "\": Length too short" << std::endl;
    return 0;
}