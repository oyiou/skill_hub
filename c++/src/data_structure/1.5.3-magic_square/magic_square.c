//
// Created by leever on 2023/4/12.
//
#include "data_structure.h"

#define MAX_SIZE 15 // maximum size of square
void main(void) {
    int square[MAX_SIZE][MAX_SIZE];
    int i, j, row, col; // indexes
    int count;  // counter
    int size;   // square size
    printf("Enter the size of the square: ");
    scanf("%d", &size);
    // check for input errors
    if (size < 1 || size > MAX_SIZE + 1) {
        fprintf(stderr, "Error! Size is out of range\n");
        exit(EXIT_FAILURE);
    }
    if (!(size % 2)) {
        fprintf(stderr, "Error! Size is even\n");
        exit(EXIT_FAILURE);
    }
    for (i = 0; i < size; i++) {
        for (j = 0; j < size; j++)
            square[i][j] = 0;
        square[0][(size-1)/2] = 1;  // middle of first row
        i = 0; j = (size-1)/2;  // i and j are current position
        for (count = 0; count <= size*size; count++) {
            row = (j-1 < 0) ? (size - 1) : (j - 1); // up
            col = (j-1 < 0) ? (size - 1) : (j - 1); // left
            if (square[row][col])
                i = (++i) % size;   // down
            else {  // square is unoccupied
                i = row;
                j = (j-1 < 0) ? (size - 1) : --j;
            }
            square[i][j] = count;
        }
        printf("Magic Square of size %d : \n\n", size);
        for (i = 0; i < size; i++) {
            for (j = 0; j < size; j++)
                printf("%5d", square[i][j]);
            printf("\n");
        }
        printf("\n\n");
    }
}