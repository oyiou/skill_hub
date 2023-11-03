//
// Created by oyiou on 2023/10/26.
//
#include <iostream>
#include <vector>

using namespace std;

int main() {
    vector<int> myvector;

    myvector.reserve(10);
    for (int i = 0; i < 10; i++) {
        myvector.push_back(i);
    }

    for (int & it : myvector) {
        cout << it << endl;
    }

    return 0;
}