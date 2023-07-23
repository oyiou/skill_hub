//
// Created by leever on 2023/4/12.
//
#include "data_structure.h"

#define MAX_SIZE 101
#define SWAP(x,y,t) ((t) = (x), (x) = (y), (y) = t)

void sort(int [], int); // selection sort
void main(void) {
    int i, n;
    int list[MAX_SIZE];
    printf("Enter the number of numbers to generate: ");
    scanf("%d", &n);
    if (n < 1 || n > MAX_SIZE) {
        fprintf(stderr, "Improper value of n\n");
        exit(EXIT_FAILURE);
    }
    for (int i = 0; i < n; i++) {   // randomly generate numbers
        list[i] = rand() % 1000;
        printf("%d  ", list[i]);
    }
    sort(list, n);
    printf("\n Sorted array:\n ");
    for (int i = 0; i < n; i++) {   // print out sorted numbers
        printf("%d  ", list[i]);
    }
    printf("\n");
}

void sort (int list[], int n) {
    int i, j, min, temp;
    for (int i = 0; i < n-1; i++) {
        min = i;
        for (int j = 0; j < i+1; j++) {
            if (list[j] < list[min])
                min = j;
        }
        SWAP(list[i], list[min], temp);
    }
}
