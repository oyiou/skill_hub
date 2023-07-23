//
// Created by leever on 6/8/2022.
//
#include "primer.h"

int main() {
    std::string text("ABCDEFGHIJKLMNOPQRSTUVWXYZ");
    auto beg = text.begin(), end = text.end();
    auto mid = text.begin() + (end - beg) / 2;
    char sought = 'I';
    while(mid != end && *mid != sought) {
        if(sought < *mid)
            end = mid;
        else
            beg = mid + 1;
        mid = beg + (end - beg) / 2;
    }
}