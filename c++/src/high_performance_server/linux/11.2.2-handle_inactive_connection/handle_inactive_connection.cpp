//
// Created by leever on 2023/3/20.
//
#include "lst_timer.h"

#define FD_LIMIT 65535
#define MAX_EVENT_NUMBER 1024
#define TIMESLOT 5

static int pipe_fd[2];
// 利用上节中的升序链表来管理定时器
static sort_timer_lst timer_lst;
static int epoll_fd = 0;

int set_non_blocking (int fd) {
    int old_option = fcntl(fd, F_GETFL);
    int new_option = old_option | O_NONBLOCK;
    fcntl(fd, F_SETFL, new_option);
    return old_option;
}

void add_fd (int epoll_fd, int fd) {
    epoll_event event;
    event.data.fd = fd;
    event.events = EPOLLIN | EPOLLET;
    epoll_ctl (epoll_fd, EPOLL_CTL_ADD, fd, &event);
    set_non_blocking(fd);
}

void sig_handler (int sig) {
    int save_errno = errno;
    int msg = sig;
    send(pipe_fd[1], (char *)&msg, 1, 0);
    errno = save_errno;
}

void add_sig (int sig) {
    struct sigaction sa;
    memset(&sa, '\0', sizeof(sa));
    sa.sa_handler = sig_handler;
    sa.sa_flags |= SA_RESTART;
    sigfillset(&sa.sa_mask);
    assert(sigaction(sig, &sa, NULL) != -1);
}

void timer_handler () {
    // 定时处理任务，实际上就是调用 tick 函数
    timer_lst.tick();
    // 因为一次 alarm 调用只会引起一次 SIGALRM 信号，所以要重新定时，以不断触发 SIGALRM 信号
    alarm(TIMESLOT);
}

// 定时器回调函数，它删除非活动连接 socket 上的注册事件，并关闭之
void cb_func (client_data *user_data) {
    epoll_ctl(epoll_fd, EPOLL_CTL_DEL, user_data->sock_fd, 0);
    assert(user_data);
    close(user_data->sock_fd);
    printf("close fd %d\n", user_data->sock_fd);
}

int main (int argc, char *argv[]) {
    if (argc <= 2) {
        printf("usage: %s ip_address port_number\n", basename(argv[0]));
        return 1;
    }
    const char *ip = argv[1];
    int port = atoi(argv[2]);

    int ret = 0;
    struct sockaddr_in address;
    bzero(&address, sizeof(address));
    address.sin_family = AF_INET;
    inet_pton(AF_INET, ip, &address.sin_addr);
    address.sin_port = htons(port);

    int listen_fd = socket(PF_INET, SOCK_STREAM, 0);
    assert(listen_fd >= 0);

    ret = bind(listen_fd, (struct sockaddr*)&address, sizeof(address));
    assert(ret != -1);

    ret = listen(listen_fd, 5);
    assert(ret != -1);

    epoll_event events[MAX_EVENT_NUMBER];
    int epoll_fd = epoll_create(5);
    assert(epoll_fd != -1);
    add_fd(epoll_fd, listen_fd);

    ret = socketpair(PF_UNIX, SOCK_STREAM, 0, pipe_fd);
    assert(ret != -1);
    set_non_blocking(pipe_fd[1]);
    add_fd(epoll_fd, pipe_fd[0]);

    // 设置信号处理函数
    add_sig(SIGALRM);
    add_sig(SIGTERM);
    bool stop_server = false;

    client_data *users = new client_data[FD_LIMIT];
    bool timeout = false;
    alarm(TIMESLOT);    // 定时

    while (!stop_server) {
        int number = epoll_wait(epoll_fd, events, MAX_EVENT_NUMBER, -1);
        if ((number < 0) && (errno != EINTR)) {
            printf("epoll failure\n");
            break;
        }

        for (int i = 0; i < number; i++) {
            int sock_fd = events[i].data.fd;
            // 处理新的客户连接
            if (sock_fd == listen_fd) {
                struct sockaddr_in client_address;
                socklen_t client_addr_length = sizeof(client_address);
                int conn_fd = accept(listen_fd, (struct sockaddr*)&client_address, &client_addr_length);
                add_fd(epoll_fd, conn_fd);
                users[conn_fd].address = client_address;
                users[conn_fd].sock_fd = conn_fd;
                // 创建定时器，设置其回调函数与超时时间，然后绑定定时器与用户数据，最后将定时器添加到链表 timer_lst 中
                util_timer *timer = new util_timer;
                timer->user_data = &users[conn_fd];
                timer->cb_func = cb_func;
                time_t cur = time(NULL);
                timer->expire = cur + 3 * TIMESLOT;
                users[conn_fd].timer = timer;
                timer_lst.add_timer(timer);
            } else if ((sock_fd == pipe_fd[0]) && (events[i].events & EPOLLIN)) {   // 处理信号
                int sig;
                char signals[1024];
                ret = recv(pipe_fd[0], signals, sizeof(signals), 0);
                if (ret == -1) {
                    // handle the error
                    continue;
                } else if (ret == 0) {
                    continue;
                } else {
                    for (int j = 0; j < ret; ++j) {
                        switch (signals[j]) {
                            case SIGALRM: {
                                // 用 timeout 变量标记有定时任务需要处理，但不立即处理定时任务，这是因为定时任务的优先级不是很高，优先处理其他重要的任务
                                timeout = true;
                                break;
                            }
                            case SIGTERM: {
                                stop_server = true;
                            }
                        }
                    }
                }
            } else if (events[i].events & EPOLLIN) {    // 处理客户端连接上接收到的数据
                memset(users[sock_fd].buf, '\0', BUFFER_SIZE);
                ret = recv(sock_fd, users[sock_fd].buf, BUFFER_SIZE - 1, 0);
                printf("get %d bytes of client data %s from %d\n", ret, users[sock_fd].buf, sock_fd);

                util_timer *timer = users[sock_fd].timer;
                if (ret < 0) {
                    // 如果发生读错误，则关闭连接，并移除其对应的定时器
                    if (errno != EAGAIN) {
                        cb_func(&users[sock_fd]);
                        if (timer) {
                            timer_lst.del_timer(timer);
                        }
                    }
                } else if (ret == 0) {
                    // 如果对方已经关闭连接，则也关闭连接，并移除对应的定时器
                    cb_func(&users[sock_fd]);
                    if (timer) {
                        timer_lst.del_timer(timer);
                    }
                } else {
                    // 如果某个客户连接上有数据可读，则要调整该连接对应的定时器，以延迟该连接被关闭的时间
                    if (timer) {
                        time_t cur = time(NULL);
                        timer->expire = cur + 3 * TIMESLOT;
                        printf("abjust timer once\n");
                        timer_lst.abjust_timer(timer);
                    }
                }
            } else {
                // others
            }
        }

        // 最后处理时事件，因为 I/O 事件有更高的优先级。当然，这样做将导致定时任务不能精确地按照预期的事件执行
        if (timeout) {
            timer_handler();
            timeout = false;
        }
    }

    close(listen_fd);
    close(pipe_fd[1]);
    close(pipe_fd[0]);
    delete [] users;
    return 0;
}