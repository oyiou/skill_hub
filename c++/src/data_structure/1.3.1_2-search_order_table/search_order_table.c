//
// Created by leever on 2023/4/12.
//

int binsearch (int list[], searchnum, int left, int right) {
    int middle;
    while (left <= right) {
        middle = (left + right) / 2;
        switch (COMPARE(list[middle], searchnum)) {
            case -1:
                left = middle + 1;
                break;
            case 0:
                return middle;
            case 1:
                right = middle - 1;
        }
    }
    return -1;
}