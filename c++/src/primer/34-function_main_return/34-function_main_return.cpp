//
// Created by leever on 6/15/2022.
//
#include <cstdlib>

int main(int argc, char *argv[]) {
    bool some_failure = argv[1];
    if(some_failure)
        return EXIT_FAILURE;
    else
        return EXIT_SUCCESS;
}