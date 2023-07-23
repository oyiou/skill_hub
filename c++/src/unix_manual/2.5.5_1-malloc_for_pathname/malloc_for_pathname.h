//
// Created by leever on 9/3/2022.
//

#ifndef UNIX_MANUAL_MALLOC_FOR_PATHNAME_H
#define UNIX_MANUAL_MALLOC_FOR_PATHNAME_H

#include "apue.h"


#ifdef _WIN32
static float posix_version = 0.0;
static long xsi_version = 0;
#else
#ifdef PATH_MAX
static long pathmax = PATH_MAX;
#else
static long pathmax = 0;
#endif

static long posix_version = 0;
static long xsi_version = 0;
#endif
// If PATH_MAX is indeterminate, no guarantee this is adequate
#define PATH_MAX_GUESS 1024

char *path_alloc(size_t *size_p);

class malloc_for_pathname {

};


#endif //UNIX_MANUAL_MALLOC_FOR_PATHNAME_H
