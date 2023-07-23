//
// Created by leever on 6/2/2022.
//
#include "primer.h"
int main() {
    std::string s("Hello World!!!");
    for(auto &c:s)
        c = (char)toupper(c);
    std::cout << s << std::endl;
    return 0;
}