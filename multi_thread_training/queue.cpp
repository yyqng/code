#include "queue.h"

template<typename T>
void Queue<T>::push(const T& ele) {
    std::unique_lock<std::mutex> uni_lk(m_mutex);
    while (m_ring.full()) {
        m_writable.wait(uni_lk);
    }
    m_ring.push(ele);
    m_readable.notify_one();
}

template<typename T>
void Queue<T>::pop(T& ele) {
    std::unique_lock<std::mutex> uni_lk(m_mutex);
    while (m_ring.empty()) {
        m_readable.wait(uni_lk);
    }
    m_ring.pop(ele);
    m_writable.notify_one();
}

int _queue_test(int qsize)
{
    Queue<int> q(qsize);
    int i = 9;
    int j = 0;
    q.push(i);
    cout << "push i = " << i << endl;
    cout << "pop  j = " << j << endl;
    q.push(i);
    q.push(i);
    q.pop(j);
    cout << "pop  j = " << j << endl;
    q.push(i);
    return 0;
}

int __queue_test(int thread_count, int qsize, int op_num)
{
    Queue<int> q(qsize);
    list<thread*> threads;
    struct timespec start;
    clock_gettime(CLOCK_MONOTONIC, &start);
    auto f  = [&](int base) {
        int data;
        for (int i = 0; i < op_num; ++i) {
            q.push(base * 10 + i);
            q.pop(data);
        }
    };
    // cat /proc/sys/kernel/pid_max to see the limit of thread_count(32768)
    for (int i = 0; i < thread_count; ++i) {
        std::thread *new_thread = new thread(f, i);
        threads.push_back(new_thread);
    }
    int i = 0;
    for(auto it : threads) {
        it->join();
        ++i;
        delete it;
    }
    struct timespec finish;
    double nm;
    clock_gettime(CLOCK_MONOTONIC, &finish);
    nm = (finish.tv_sec - start.tv_sec) * 1e9;
    nm += (finish.tv_nsec - start.tv_nsec);
    cout << "bounded blocking queue test:" << endl;
    cout << "number of threads:" << thread_count << endl;
    cout << "queue size :" << qsize << "(int)"  << endl;
    cout << "push + pop " << op_num << " times / thread" << endl;
    cout << "total time cost :" << nm / 1e9 << "s  " << endl;
    cout << nm / thread_count / op_num << " nm / (push + pop)" << endl;
    return 0;
}

void queue_test()
{
    int thread_count = 1e2; 
    int qsize = 1e2;
    int op_num = 1e2;
    __queue_test(thread_count, qsize, op_num);
//    thread_count = 1e4; 
//    qsize = 1e4;
//    op_num = 1000;
//    __queue_test(thread_count, qsize, op_num);
}
