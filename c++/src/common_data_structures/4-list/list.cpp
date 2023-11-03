//
// Created by oyiou on 2023/10/25.
//
#include <iostream>
#include <list>

using namespace std;

int main() {
    int num[] = {1,2,3,4,5};
    list<int> mylist(num, num  + sizeof(num)/ sizeof(int));

    for (int & it1 : mylist) {
        cout << it1 << " ";
    }

    auto it2 = mylist.begin();
    for (int i = 0; i < 5; i++) {
        mylist.insert(it2, i);
    }

    cout << endl;
    for (int & it3 : mylist) {
        cout << it3 << " ";
    }

    return 0;
}