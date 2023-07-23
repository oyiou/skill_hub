//
// Created by leever on 6/8/2022.
//
#include "primer.h"

int main() {
    std::string s("some string");
    if(s.begin() != s.end()) {
        auto it = s.begin();
        *it = (char )toupper(*it);
    }
}