//
// Created by oyiou on 2023/10/25.
//
#include <iostream>
#include <queue>

using namespace std;

int main() {
    queue<int> myqueue;
    for (int i = 0; i < 10; i++) {
        myqueue.push(i);
    }

    while (!myqueue.empty()) {
        cout << myqueue.front() << endl;
        myqueue.pop();
    }

    return 0;
}