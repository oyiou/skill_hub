//
// Created by oyiou on 2023/10/25.
//
#include <iostream>
#include <stack>

using namespace std;

int main() {
    stack<int> mystack;

    for (int i = 0; i < 10; i++) {
        mystack.push(i);
    }

    while (!mystack.empty()) {
        cout << mystack.top() << endl;
        mystack.pop();
    }

    return 0;
}