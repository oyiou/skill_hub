//
// Created by oyiou on 2023/10/25.
//
#include <iostream>
#include <map>

using namespace std;

int main() {
    map<char, int> mymap;

    mymap['a'] = 1;

    mymap.insert(pair<char, int>('b', 2));

    mymap.erase('a');

    auto it = mymap.find('b');
    cout << it->first << " " << it->second << endl;

    return 0;
}