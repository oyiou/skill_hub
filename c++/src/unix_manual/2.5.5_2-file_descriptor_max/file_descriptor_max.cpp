//
// Created by leever on 9/5/2022.
//

#include "file_descriptor_max.h"

long open_max() {
#ifdef _WIN32
#else
    if(openmax == 0) {
        errno = 0;
        if((openmax = sysconf(_SC_OPEN_MAX)) < 0) {
            if(errno = 0)
                openmax = OPEN_MAX_GUESS;
            else
                err_sys("sysconf error for _SC_OPEN_MAX")
        }
    }
    return openmax;
#endif
}