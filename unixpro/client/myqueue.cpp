#include "myqueue.h"

template<typename T>
void Myqueue<T>::push(const T& ele) {
    boost::unique_lock<boost::mutex> lk(m_mutex);
    while (m_ring.full()) {
        m_cond_not_full.wait(lk);
    }
    m_ring.push(ele);
    m_cond_not_empty.notify_one();
}
template<typename T>
bool Myqueue<T>::try_push(const T& ele) {
    boost::unique_lock<boost::mutex> lk(m_mutex);
    if (!m_ring.full()) {
        m_ring.push(ele);
        m_cond_not_empty.notify_one();
        return true;
    }
    return false;
}
template<typename T>
void Myqueue<T>::pop(T& ele) {
    boost::unique_lock<boost::mutex> lk(m_mutex);
    while (m_ring.empty()) {
        m_cond_not_empty.wait(lk);
    }
    ele = m_ring.front();
    m_ring.pop_front();
    m_cond_not_full.notify_one();
}
template<typename T>
bool Myqueue<T>::try_pop(const T& ele) {
    boost::unique_lock<boost::mutex> lk(m_mutex);
    if (!m_ring.empty()) {
        ele = m_ring.front();
        m_ring.pop_front();
        m_cond_not_full.notify_one();
        return true;
    }
    return false;
}
template<typename T>
size_t Myqueue<T>::size() const
{
    boost::unique_lock<boost::mutex> lk(m_mutex);
    return m_ring.size();
}
template<typename T>
size_t Myqueue<T>::capacity() const {
    boost::unique_lock<boost::mutex> lk(m_mutex);
    return m_ring.capacity();
}

int myqueue_test(const int concurrency)
{
    const int num = 1000 * 1000;
    Myqueue<int> q(10);
    boost::thread_group thg;
    struct timespec start;
    clock_gettime(CLOCK_MONOTONIC, &start);
    for (int tr = 0; tr < concurrency; ++tr) {
        thg.create_thread([&]() {
            int idata;
            for (int i = 0; i < num; ++i) {
                //q.wait_pull_front(dat);
                //q.wait_pull_front(dat);
            }
        });
    }
    thg.join_all();
    printTime(start, "bbq_test.");
    return 0;
}
