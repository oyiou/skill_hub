//
// Created by leever on 6/15/2022.
//
#include "primer.h"

char &get_val(std::string &str, std::string::size_type ix) {
    return str[ix];
}
int main() {
    std::string s("a value");
    std::cout << s << std::endl;
    get_val(s, 0) = 'A';
    std::cout << s << std::endl;
    return 0;
}