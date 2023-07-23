//
// Created by leever on 6/14/2022.
//
#include "primer.h"

std::string::size_type find_char(const std::string &s, char c, std::string::size_type *occurs) {
    auto ret = s.size();
    occurs = nullptr;
    for(decltype(ret) i = 0; i != s.size(); ++i) {
        if(s[i] == c) {
            if(ret == s.size())
                ret = i;
            ++occurs;
        }
    }
    return ret;
}
int main() {
    std::string str = "some string";
    std::string::size_type *count = nullptr;
    find_char(str, 'i', count);
    return 0;
}