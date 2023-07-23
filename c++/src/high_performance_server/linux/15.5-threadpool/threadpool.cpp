//
// Created by leever on 2023/3/23.
//
#include "threadpool.h"

template<typename T>
threadpool<T>::threadpool(int thread_number, int max_requests): m_thread_number(thread_number), m_max_requests(max_requests), m_stop(
        false), m_threads(NULL) {
    if ((thread_number <= 0) || (max_requests <= 0)) {
        throw std::exception();
    }

    m_threads = new pthread_t [m_thread_number];
    if (!m_threads) {
        throw std::exception();
    }

    // 创建 thread_number 个线程，并将它们都设置为脱离线程
    for (int i = 0; i < thread_number; ++i) {
        printf("create the %dth thread\n", i);
        if (pthread_create(m_threads + i, NULL, worker, this) != 0) {
            delete [] m_threads;
            throw std::exception();
        }
    }
}

template<typename T>
threadpool<T>::~threadpool() {
    delete [] m_threads;
    m_stop = true;
}

template<typename T>
bool threadpool<T>::append(T* request) {
    // 操作工作队列时一定要加锁，因为它被所有线程共享
    m_queue_locker.lock();
    if (m_work_queue.size() > m_max_requests) {
        m_queue_locker.unlock();
        return false;
    }
    m_work_queue.push_back(request);
    m_queue_locker.unlock();
    m_queue_stat.post();
    return true;
}

template<typename T>
void *threadpool<T>::worker(void* arg) {
    threadpool *pool = (threadpool*)arg;
    pool->run();
    return pool;
}

template<typename T>
void threadpool<T>::run() {
    while (!m_stop) {
        m_queue_stat.wait();
        m_queue_locker.lock();
        if (m_work_queue.empty()) {
            m_queue_locker.unlock();
            continue;
        }
        T* request = m_work_queue.front();
        m_work_queue.pop_front();
        m_queue_locker.unlock();
        if (!request) {
            continue;
        }
        request->process();
    }
}