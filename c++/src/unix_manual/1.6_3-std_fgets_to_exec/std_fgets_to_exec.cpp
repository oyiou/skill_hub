//
// Created by leever on 8/31/2022.
//

#include "std_fgets_to_exec.h"

int main(int argc, char *argv[]) {
    char buf[MAXLINE];
    pid_t pid;
    printf("%% ");
    while(fgets(buf, MAXLINE, stdin) != nullptr) {
        if(buf[strlen(buf) - 1] == '\n')
            buf[strlen(buf) - 1] = 0;
#ifdef _WIN32
        LPCTSTR                 lpApplicationName       = nullptr;  // 应用程序名称
        LPTSTR                  lpCommandLine           = argv[1];  // 命令行字符串
        LPSECURITY_ATTRIBUTES   lpProcessAttributes     = nullptr;  // 进程的安全属性
        LPSECURITY_ATTRIBUTES   lpThreadAttributes      = nullptr;  // 线程的安全属性
        BOOL                    bInheritHandles         = FALSE;    // 是否继承父进程的属性
        DWORD                   dwCreationFlags         = 0;        // 创建标志
        LPVOID                  lpEnvironment           = nullptr;  // 指向新的环境块的指针
        LPCTSTR                 lpCurrentDirectory      = nullptr;  // 指向当前目录名的指针
        LPSTARTUPINFO           lpStartupInfo           = nullptr;  // 传递给新进程的信息
        LPPROCESS_INFORMATION   lpProcessInformation    = nullptr;  // 新进程返回的信息

        STARTUPINFO             si; // 在产生子进程时，子进程的窗口相关信息
        PROCESS_INFORMATION     pi; // 子进程的ID/线程相关信息

        ZeroMemory( &si, sizeof(si) );
        si.cb = sizeof(si);
        ZeroMemory( &pi, sizeof(pi) );

        if( argc != 2 ) {
            printf("Usage: %s [cmdline]\n", argv[0]);
            return 0;
        }

        // Start the child process.
        if(!CreateProcess( lpApplicationName,       // No module name (use command line)        // 指向一个NULL结尾的、用来指定可执行模块的宽字节字符串
                            lpCommandLine,          // Command line                             // 命令行字符串
                            lpProcessAttributes,    // Process handle not inheritable           // 指向一个SECURITY_ATTRIBUTES结构体，这个结构体决定是否返回的句柄可以被子进程继承。
                            lpThreadAttributes,     // Thread handle not inheritable            // 如果lpProcessAttributes参数为空（NULL），那么句柄不能被继承。<同上>
                            bInheritHandles,        // Set handle inheritance to FALSE          // 指示新进程是否从调用进程处继承了句柄。
                            dwCreationFlags,        // No creation flags                        // 指定附加的、用来控制优先类和进程的创建的标
                                                                                                    // CREATE_NEW_CONSOLE   新控制台打开子进程
                                                                                                    // CREATE_SUSPENDED     子进程创建后挂起，直到调用ResumeThread函数
                            lpEnvironment,          // Use parent's environment block           // 指向一个新进程的环境块。如果此参数为空，新进程使用调用进程的环境
                            lpCurrentDirectory,     // Use parent's starting directory          // 指定子进程的工作路径
                            &si,         // Pointer to STARTUPINFO structure         // 决定新进程的主窗体如何显示的STARTUPINFO结构体
                            &pi    // Pointer to PROCESS_INFORMATION structure // 接收新进程的识别信息的PROCESS_INFORMATION结构体
                            )) {
            printf( "CreateProcess failed (%lu).\n", GetLastError());
            return 0;
            // 下面两行关闭句柄，解除本进程和新进程的关系，不然有可能不小心调用TerminateProcess函数关掉子进程
            // CloseHandle(pi.hProcess);
            // CloseHandle(pi.hThread);
        }
        pid = pi.dwProcessId;
#else
        pid = fork();
#endif
        if(pid < 0) {
            err_sys("fork error");
        } else if(pid == 0) {
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
#endif
        if(pid < 0)
            err_sys("waitpid error");
        printf("%% ");
    }
    exit(0);
}