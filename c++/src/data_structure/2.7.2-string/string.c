//
// Created by leever on 2023/4/12.
//
#include "data_structure.h"

template <typename T>
struct String {
    String<T> null(int m);

    String<T> init(T m);

    int compare(String<T> s, String<T> t);

    bool isNull(String<T> s);

    int length(String<T> s);

    String<T> strCat(String<T> s, String<T> t);

    String<T> subStr(String<T> s, int start, int end);

    String<T> oprater=(T s);

    T *_data;
    usize _size;
};
