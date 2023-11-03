//
// Created by oyiou on 2023/10/26.
//
#include <iostream>
#include <set>

using namespace std;

int main() {
    int num[] = {1,2,3,4,5};
    set<int> myset(num, num + sizeof(num)/ sizeof(int ));

    myset.insert(6);

    myset.erase(2);

    auto it = myset.find(3);

    cout << *it << endl;

    return 0;
}