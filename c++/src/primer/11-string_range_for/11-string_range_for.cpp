//
// Created by leever on 6/2/2022.
//
#include "primer.h"
int main() {
    std::string s("Hello World!!!");
    decltype(s.size()) punct_cnt = 0;
    for(auto c:s)
        if(std::ispunct(c))
            ++punct_cnt;
    std::cout << punct_cnt << " punctuation characters in" << s << std::endl;
    return 0;
}