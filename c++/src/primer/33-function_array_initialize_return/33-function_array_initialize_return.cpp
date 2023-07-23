//
// Created by leever on 6/15/2022.
//
#include "primer.h"

std::string expected;
std::string actual;
std::vector<std::string> process() {
    if(expected.empty())
        return {};
    else if(expected == actual)
        return {"functionX", "okay"};
    else
        return {"functionX", expected, actual};
}
int main() {
    process();
}