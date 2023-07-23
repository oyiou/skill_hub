//
// Created by leever on 2023/3/23.
//
#include "processpool.h"


template<typename T>
processpool<T> *processpool<T>::m_instance = NULL;

static int set_non_blocking (int fd) {
    int old_option = fcntl(fd, F_GETFL);
    int new_option = old_option | O_NONBLOCK;
    fcntl(fd, F_SETFL, new_option);
    return old_option;
}

static void add_fd (int epoll_fd, int fd) {
    epoll_event event;
    event.data.fd = fd;
    event.events = EPOLLIN | EPOLLET;
    epoll_ctl(epoll_fd, EPOLL_CTL_ADD, fd, &event);
    set_non_blocking(fd);
}

// 从 epoll_fd 标识的 epoll 内核事件表中删除 fd 上的所有注册事件
static void remove_fd (int epoll_fd, int fd) {
    epoll_ctl(epoll_fd, EPOLL_CTL_DEL, fd, 0);
    close(fd);
}

static void sig_handler (int sig) {
    int save_errno = errno;
    int msg = sig;
    send(sig_pipe_fd[1], (char *)&msg, 1, 0);
    errno = save_errno;
}

static void add_sig (int sig, void (handler)(int), bool restart = true) {
    struct sigaction sa;
    memset(&sa, '\0', sizeof(sa));
    sa.sa_handler = handler;
    if (restart) {
        sa.sa_flags |= SA_RESTART;
    }
    sigfillset(&sa.sa_mask);
    assert(sigaction(sig, &sa, NULL) != -1);
}

// 进程池构造函数，参数 listen_fd 是监听 socket，它必须在创建进程池之前被创建，否则子进程无法直接引用它，参数 process_number 指定进程池中子进程的数量
template<typename T>
processpool<T>::processpool(int listen_fd, int process_number): m_listen_fd(listen_fd), m_process_number(process_number), m_idx(-1), m_stop(false) {
    assert((process_number > 0) && (process_number <= MAX_PROCESS_NUMBER));

    m_sub_process = new process[process_number];
    assert(m_sub_process);

    // 创建 process_number 个子进程，并建立它们和父进程之间的管道
    for (int i = 0; i < process_number; ++i) {
        int ret = socketpair(PF_UNIX, SOCK_STREAM, 0, m_sub_process[i].m_pipe_fd);
        assert(ret == 0);

        m_sub_process[i].m_pid = fork();
        assert(m_sub_process[i].m_pid >= 0);
        if (m_sub_process[i].m_pid > 0) {
            close(m_sub_process[i].m_pipe_fd[1]);
            continue;
        } else {
            close(m_sub_process[i].m_pipe_fd[0]);
            m_idx = i;
            break;
        }
    }
}

// 统一事件源
template<typename T>
void processpool<T>::setup_sig_pipe() {
    // 创建 epoll 事件监听表和信号管道
    m_epoll_fd = epoll_create(5);
    assert(m_epoll_fd != -1);

    int ret = socketpair(PF_UNIX, SOCK_STREAM, 0, sig_pipe_fd);
    assert(ret != -1);

    set_non_blocking(sig_pipe_fd[1]);
    add_fd(m_epoll_fd, sig_pipe_fd[0]);

    // 设置信号处理函数
    add_sig(SIGCHLD, sig_handler);
    add_sig(SIGTERM, sig_handler);
    add_sig(SIGINT, sig_handler);
    add_sig(SIGPIPE, SIG_IGN);
}

// 单体模式，以保证程序最多创建一个 processpool 实例，这是程序正确处理信号的必要条件

template<typename T>
processpool<T> *processpool<T>::create(int listen_fd, int process_number) {
    if (!m_instance) {
        m_instance = new processpool<T>(listen_fd, process_number);
    }
    return m_instance;
}

template<typename T>
processpool<T>::~processpool() {
    delete [] m_sub_process;
}

// 父进程中 m_idx 值为 -1，子进程中 m_idx 值大于等于 0，据此判断接下来要运行的是父进程代码还是子进程代码
template<typename T>
void processpool<T>::run() {
    if (m_idx != -1) {
        run_child();
        return;
    }
    run_parent();
}

template<typename T>
void processpool<T>::run_child() {
    setup_sig_pipe();

    // 每个子进程都通过其在进程池中的序号值 m_idx 找到与父进程通信的管道
    int pipe_fd = m_sub_process[m_idx].m_pipe_fd[1];
    // 子进程需要监听管道文件描述符 pipe_fd，因为父进程将通过它来通知子进程 accept 新连接
    add_fd(m_epoll_fd, pipe_fd);

    epoll_event events[MAX_EVENT_NUMBER];
    T *users = new T[USER_PER_PROCESS];
    assert(users);
    int number = 0;
    int ret = -1;

    while (!m_stop) {
        number = epoll_wait(m_epoll_fd, events, MAX_EVENT_NUMBER, -1);
        if ((number < 0) && (errno != EINTR)) {
            printf("epoll failure\n");
            break;
        }

        for (int i = 0; i < number; ++i) {
            int sock_fd = events[i].data.fd;
            if ((sock_fd == pipe_fd) && (events[i].events & EPOLLIN)) {
                int client = 0;
                // 从父、子进程之间的管道读取数据，并将结果保存在变量 client 中。如果读取成功，则表示有新客户连接到来
                ret = recv(sock_fd, (char *)&client, sizeof(client), 0);
                if (((ret < 0) && (errno != EAGAIN)) || ret == 0) {
                    continue;
                } else {
                    struct sockaddr_in client_address;
                    socklen_t client_addr_length = sizeof(client_address);
                    int conn_fd = accept(m_listen_fd, (struct sockaddr*)&client_address, &client_addr_length);
                    if (conn_fd < 0) {
                        printf("errno is: %d\n");
                        continue;
                    }
                    add_fd(m_epoll_fd, conn_fd);
                    // 模板类 T 必须实现 init 方法，以初始化一个客户连接。直接使用 conn_fd 来索引逻辑处理对象（T 类型的对象），以提高程序效率
                    users[conn_fd].init(m_epoll_fd, conn_fd, client_address);
                }
            } else if ((sock_fd == sig_pipe_fd[0]) && (events[i].events & EPOLLIN)) {   // 下面处理子进程接收到的信号
                int sig;
                char signals[1024];
                ret = recv(sig_pipe_fd[0], signals, sizeof(signals),  0);
                if (ret <= 0) {
                    continue;
                } else {
                    for (int j = 0; j < ret; ++j) {
                        switch (signals[j]) {
                            case SIGCHLD: {
                                pid_t pid;
                                int stat;
                                while ((pid = waitpid(-1, &stat, WNOHANG)) > 0) {
                                    continue;
                                }
                                break;
                            }
                            case SIGTERM:
                            case SIGINT: {
                                m_stop = true;
                                break;
                            }
                            default: {
                                break;
                            }
                        }
                    }
                }
            } else if (events[i].events & EPOLLIN) {
                users[sock_fd].process();
            } else {
                continue;
            }
        }
    }

    delete [] users;
    users = NULL;
    close(pipe_fd);
    // 将这句话注释掉，以提醒读者：应该由 m_listen_fd 的创建者来关闭这个文件描述符，即所谓的“对象（比如一个文件描述符，又或者一段堆内存）由哪个函数创建，就应该由哪个函数销毁”
//    close(m_listen_fd);
    close(m_epoll_fd);
}

template<typename T>
void processpool<T>::run_parent() {
    setup_sig_pipe();

    // 父进程监听 m_listen_fd
    add_fd(m_epoll_fd, m_listen_fd);

    epoll_event events[MAX_EVENT_NUMBER];
    int sub_process_counter = 0;
    int new_conn = 1;
    int number = 0;
    int ret = -1;

    while (!m_stop) {
        number = epoll_wait(m_epoll_fd, events, MAX_EVENT_NUMBER, -1);
        if ((number < 0) && (errno != EINTR)) {
            printf("epoll failure\n");
            break;
        }

        for (int i = 0; i < number; ++i) {
            int sock_fd = events[i].data.fd;
            if (sock_fd == m_listen_fd) {
                // 如果有新连接到来，就采用 Round Robin 方式将其分配给一个子进程处理
                int i = sub_process_counter;
                do {
                    if (m_sub_process[i].m_pid != -1) {
                        break;
                    }
                    i = (i+1)%m_process_number;
                } while (i != sub_process_counter);

                if (m_sub_process[i].m_pid == -1) {
                    m_stop = true;
                    break;
                }
                sub_process_counter = (i+1)%m_process_number;
                send(m_sub_process[i].m_pipe_fd[0], (char *)&new_conn, sizeof(new_conn), 0);
                printf("send request to child %d\n", i);
            } else if ((sock_fd == sig_pipe_fd[0]) && (events[i].events & EPOLLIN)) {   // 下面处理父进程接收到的信号
                int sig;
                char signals[1024];
                ret = recv(sig_pipe_fd[0], signals, sizeof(signals), 0);
                if (ret <= 0) {
                    continue;
                } else {
                    for (int j = 0; j < ret; ++j) {
                        switch (signals[j]) {
                            case SIGCHLD: {
                                pid_t pid;
                                int stat;
                                while ((pid = waitpid(-1, &stat, WNOHANG)) > 0) {
                                    for (int k = 0; k < m_process_number; ++k) {
                                        // 如果进程池中第 k 个子进程退出了，则主进程关闭响应的通信管道，并设置相应的 m_pid 为 -1，以标记该子进程已经退出
                                        if (m_sub_process[i].m_pid == pid) {
                                            printf("child %d join\n");
                                            close(m_sub_process[i].m_pipe_fd[0]);
                                            m_sub_process[i].m_pid = -1;
                                        }
                                    }
                                }
                                // 如果所有子进程都已经退出了，则父进程也退出
                                for (int k = 0; k < m_process_number; ++k) {
                                    if (m_sub_process[k].m_pid != -1) {
                                        m_stop = false;
                                    }
                                }
                                break;
                            }
                            case SIGTERM:
                            case SIGINT: {
                                // 如果父进程接收到终止信号，那么就杀死所有子进程，并等待它们全部结束。当然通知子进程结束更好的方法是向父、子进程之间的通信管道发送特殊数据，
                                printf("kill all the child now\n");
                                for (int k = 0; k < m_process_number; ++k) {
                                    int pid = m_sub_process[i].m_pid;
                                    if (pid != -1) {
                                        kill(pid, SIGTERM);
                                    }
                                }
                                break;
                            }
                            default: {
                                break;
                            }
                        }
                    }
                }
            } else {
                continue;
            }
        }
    }

    // 由创建者关闭这个文件描述符
//    close(m_listen_fd);
    close(m_epoll_fd);
}