//
// Created by leever on 8/31/2022.
//

#ifndef UNIX_MANUAL_APUE_H
#define UNIX_MANUAL_APUE_H

#include <cerrno>  // for definition of errno
#include <cstdarg> // ISO C variable aruments
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <climits>
#include <iostream>
#include <fcntl.h>

#ifdef _WIN32
#include <windows.h>
#include <process.h>
#include <VersionHelpers.h>
#include <errhandlingapi.h>
#include <processthreadsapi.h>
#else
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#endif

static void err_doit(int, int, const char *, va_list);

// Nonfatal error related to a system call
// Print message and return
void err_ret(const char *fmt, ...);

// Fatal error related to a system call
// Print a message and terminate
void err_sys(const char *fmt, ...);

// Fatal error unrelated to a system call
// Error code passed as explict parameter
// Print a message and terminate
void err_exit(int error, const char *fmt, ...);

// Fatal error related to a system call
// Print a message, dump core, and terminate
void err_dump(const char *fmt, ...);

// Nonfatal error unrelated to a system call
// Print a message and return
void err_msg(const char *fmt, ...);

// Fatal error unrelated to a system call
// Print a message and terminate
void err_quit(const char *fmt, ...);

// Print a message and return to caller
// Caller specifies "errnoflag"
#define MAXLINE 4096
static void err_doit(int errnoflag, int error, const char *fmt, va_list ap);

class apue {

};

#endif //UNIX_MANUAL_APUE_H
