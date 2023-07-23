//
// Created by leever on 8/30/2022.
//

#include "ls.h"

int main(int argc, char *argv[]) {
    DIR *dp;
    struct dirent *dirp;
    if(argc != 2)
        err_quit("usage: ls directory_name");
    if((dp = opendir(argv[1])) == nullptr)
        err_sys("can't open %s", argv[1]);
    while((dirp = readdir(dp)) != nullptr)
        printf("%s\n", dirp->d_name);
    closedir(dp);
    exit(0);
}