//
// Created by oyiou on 2023/10/25.
//

#include <iostream>
#include <array>

using namespace std;

int main() {
    array<int, 10> myarray{};

    for (int i = 0; i < 10; i++) {
        myarray[i] = i;
    }

    cout << "遍历数据" << endl;
    for (int & it : myarray) {
        cout << it << '\t';
    }

    cout << endl;
    cout << "size of array is " << myarray.size() << endl;

    cout << "第四个元素值为： " << myarray[3] << endl;
    return 0;
}