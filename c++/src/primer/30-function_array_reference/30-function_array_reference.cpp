//
// Created by leever on 6/14/2022.
//
#include "primer.h"

void print(int (&arr)[10]) {
    for(auto elem : arr)
        std::cout << elem << std::endl;
}
int main() {
    int arr[] = {0,1,2,3,4,5,6,7,8,9};
    print(arr);
    return 0;
}