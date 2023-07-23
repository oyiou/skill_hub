//
// Created by leever on 9/5/2022.
//

#ifndef UNIX_MANUAL_FILE_DESCRIPTOR_MAX_H
#define UNIX_MANUAL_FILE_DESCRIPTOR_MAX_H

#include "apue.h"

#ifdef _WIN32
#else
#ifdef OPEN_MAX
static long openmax = OPEN_MAX;
#else
static long openmax = 0;
#endif
#endif
// If PATH_MAX is indeterminate, no guarantee this is adequate
#define OPEN_MAX_GUESS 256

long open_max();

class file_descriptor_max {

};


#endif //UNIX_MANUAL_FILE_DESCRIPTOR_MAX_H
