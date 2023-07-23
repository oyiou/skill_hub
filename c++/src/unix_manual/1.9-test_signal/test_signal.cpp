//
// Created by leever on 9/2/2022.
//

#include "test_signal.h"

static void sig_int(int);
int main(int argc, char *argv[]) {
    char buf[MAXLINE];
    pid_t pid;
    if(signal(SIGINT, sig_int) == SIG_ERR)
        err_sys("signal error");
    printf("%% ");
    while(fgets(buf, MAXLINE, stdin) != nullptr) {
        if(buf[strlen(buf) - 1] == '\n')
            buf[strlen(buf) - 1] = 0;
#ifdef _WIN32
        STARTUPINFO             si; // 在产生子进程时，子进程的窗口相关信息
        PROCESS_INFORMATION     pi; // 子进程的ID/线程相关信息
        ZeroMemory( &si, sizeof(si) );
        si.cb = sizeof(si);
        ZeroMemory( &pi, sizeof(pi) );
        if( argc != 2 ) {
            printf("Usage: %s [cmdline]\n", argv[0]);
            return 0;
        }
        if(!CreateProcess(
                nullptr, argv[1], nullptr, nullptr,  FALSE,
                0, nullptr, nullptr, &si, &pi)) {
            printf( "CreateProcess failed (%lu).\n", GetLastError());
            return 0;
        }
        pid = pi.dwProcessId;
#else
        pid = fork();
#endif
        if(pid == 0) {
            execlp(buf, buf, (char *)0);
            err_ret("couldn't execute: %s", buf);
            exit(127);
        }
#ifdef _WIN32
        DWORD returnCode;//用于保存子程进的返回值;
        std::cout << "process is running..." << std::endl;
        //等待子进程结束
        WaitForSingleObject(pi.hProcess, -1);
        std::cout << "process is finished"  << std::endl;
        //获取子进程的返回值
        GetExitCodeProcess(pi.hProcess, &returnCode);
        std::cout << "process return code:" << returnCode << std::endl;
#else
        int status;
        int pid = waitpid(pid, &status, 0);
        if(pid < 0)
            err_sys("waitpid error");
#endif
        printf("%% ");
    }
    exit(0);
}