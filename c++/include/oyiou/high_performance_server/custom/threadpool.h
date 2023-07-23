//
// Created by leever on 2023/3/23.
//

#ifndef C_THREADPOOL_H
#define C_THREADPOOL_H

#include "locker.h"

// 进程池类，将它定义为模板类是为了代码复用，模板参数 T 是任务类
template<typename T>
class threadpool {
private:
    int m_thread_number;    // 线程池中的线程数
    int m_max_requests; // 请求队列中允许的最大请求数
    pthread_t* m_threads;    // 描述线程池的数组，其大小为 m_thread_number
    std::list<T*> m_work_queue; // 请求队列
    locker m_queue_locker;  // 保护请求队列的互斥锁
    sem m_queue_stat;   // 是否有任务需要处理
    bool m_stop;    // 是否结束线程
private:
    // 工作线程运行的函数，它不断从工作队列中取出任务并执行之
    static void* worker(void *arg);
    void run();
public:
    // 参数 thread_number 是线程池中线程的数量，max_requests 是请求队列中最多允许的、等待处理的请求的数量
    threadpool(int thread_number = 8, int max_requests = 10000);
    ~threadpool();
    // 往请求队列中添加任务
    bool append(T* request);
};

#endif //C_THREADPOOL_H
