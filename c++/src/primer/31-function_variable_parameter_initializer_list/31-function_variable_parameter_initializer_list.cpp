//
// Created by leever on 6/15/2022.
//
#include "primer.h"
#include <initializer_list>

void error_msg(std::initializer_list<std::string> il) {
    for(const auto & beg : il)
        std::cout << beg << " ";
    std::cout << std::endl;
}
int main(int argc, char *argv[]) {
    std::string expected = argv[1];
    std::string actual = argv[2];
    if(expected != actual)
        error_msg({"functionX", expected, actual});
    else
        error_msg({"functionX","okay"});
}