//
// Created by leever on 2023/3/21.
//
#include "high_performance_server.h"

extern char **environ;

int execl(const char *path, const char *arg, ...);
int execlp(const char *file, const char *arg, ...);
int execle(const char *path, const char *arg, ..., char *const envp[]);
int execv(const char *path, const char *arg[]);
int execvp(const char *file, const char *arg[]);
int execve(const char *path, const char *arg[], char *const envp[]);