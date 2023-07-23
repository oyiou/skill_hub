//
// Created by leever on 9/3/2022.
//

#include "malloc_for_pathname.h"

char *path_alloc(size_t *size_p) {	// also return allocated size, if nonnull
#ifdef _WIN32
    // Win7 或者更高级的版本
    if (IsWindows7OrGreater()) {
        posix_version = 7;
    } else if (IsWindows7SP1OrGreater()) {
        posix_version = 7.1;
    } else if (IsWindows8OrGreater()) {
        posix_version = 8;
    } else if (IsWindows8Point1OrGreater()) {
        posix_version = 8.1;
    } else if (IsWindows10OrGreater()) {
        posix_version = 10;
    }
#else
    char *ptr;
    size_t size;
    if(posix_version == 0)
        posix_version = sysconf(_SX_VERSION);
    if(xsi_version == 0)
        xsi_version = sysconf(_SC_XOPEN_VERSION);
    if(pathmax == 0) {	// first time through
        errno = 0;
        if((pathmax = pathconf("/", _PC_PATH_MAX)) < 0) {
            if(errno == 0)
                pathmax = PATH_MAX_GUESS;	// it's indeterminate
            else
                err_sys("pathconfi error for _PC_PATH_MAX");
        } else {
            pathmax++;	// add one since it's relative to root
        }
    }
    if((posix_version < 200112L) && (xsi_version < 4))
        size = pathmax + 1;
    else
        size = pathmax;
    if((ptr = static_cast<char *>(malloc(size))) == nullptr)
        err_sys("malloc error for pathname");
    if(size_p != NULL)
        *size_p = size;
    return(ptr);
#endif
}