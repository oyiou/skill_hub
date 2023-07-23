//
// Created by leever on 6/2/2022.
//
#include "primer.h"
int main() {
    std::string s("some string");
    if(!s.empty())
        std::cout << s[0] << std::endl;
    for(decltype(s.size()) index = 0; index != s.size() && !std::isspace(s[index]); ++index)
        s[index] = (char)toupper(s[index]);
}