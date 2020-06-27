#include "bbq.h"

template<typename T>
void blocking_queue<T>::push(const T& val) {
    boost::unique_lock<boost::mutex> lk(m_mutex);
    m_queue.push(val);
    m_cond.notify_one();
}

template<typename T>
void blocking_queue<T>::pop(T& val) {
    boost::unique_lock<boost::mutex> lk(m_mutex);
    while (m_queue.empty()) {
        m_cond.wait(lk);
    }
    val = m_queue.front();
    m_queue.pop();
}

template<typename T>
bool blocking_queue<T>::try_pop(T& val) {
    boost::unique_lock<boost::mutex> lk(m_mutex);
    if (!m_queue.empty()) {
        val = m_queue.front();
        m_queue.pop();
        return true;
    }
    return false;
}



template<typename T>
void bounded_blocking_queue_1 <T>::push(const T& val) {
    boost::unique_lock<boost::mutex> lk(m_mutex);
    while (m_queue.full()) {
        m_cond_not_full.wait(lk);
    }
    m_queue.push_back(val);
    m_cond_not_empty.notify_one();
}
template<typename T>
bool bounded_blocking_queue_1 <T>::try_push(const T& val) {
    boost::unique_lock<boost::mutex> lk(m_mutex);
    if (!m_queue.full()) {
        m_queue.push_back(val);
        m_cond_not_empty.notify_one();
        return true;
    }
    return false;
}
template<typename T>
void bounded_blocking_queue_1 <T>::pop(T& val) {
    boost::unique_lock<boost::mutex> lk(m_mutex);
    while (m_queue.empty()) {
        m_cond_not_empty.wait(lk);
    }
    val = m_queue.front();
    m_queue.pop_front();
    m_cond_not_full.notify_one();
}
template<typename T>
bool bounded_blocking_queue_1 <T>::try_pop(const T& val) {
    boost::unique_lock<boost::mutex> lk(m_mutex);
    if (!m_queue.empty()) {
        val = m_queue.front();
        m_queue.pop_front();
        m_cond_not_full.notify_one();
        return true;
    }
    return false;
}
template<typename T>
size_t bounded_blocking_queue_1 <T>::size() const {
    boost::unique_lock<boost::mutex> lk(m_mutex);
    return m_queue.size();
}
template<typename T>
size_t bounded_blocking_queue_1 <T>::capacity() const {
    boost::unique_lock<boost::mutex> lk(m_mutex);
    return m_queue.capacity();
}

template<typename T>
void sync_queue<T>::push(const T& elem) {
    boost::unique_lock<boost::mutex> lk(sync_queue_base<T>::m_mtx);
    sync_queue_base<T>::throw_if_closed(lk);
    push(elem, lk);
}
template<typename T>
void sync_queue<T>::push(const T& elem, boost::unique_lock<boost::mutex>& lk) {
    m_data.push_back(elem);
    sync_queue_base<T>::notify_not_empty_if_needed(lk);
}

template<typename T>
void sync_queue<T>::pull(T& elem) {
    boost::unique_lock<boost::mutex> lk(m_mtx);
    const bool has_been_closed = sync_queue_base<T>::wait_until_not_empty_or_closed(lk);
    if (has_been_closed) {
        sync_queue_base<T>::throw_if_closed(lk);
    }
    pull(elem, lk);
}
template<typename T>
void sync_queue<T>::pull(T& elem, boost::unique_lock<boost::mutex>& lk) {
    elem = sync_queue_base<T>::m_data.front(); // 这里应该用move
    sync_queue_base<T>::m_data.pop_front();
}


template<typename T>
queue_op_status sync_queue<T>::try_push(const T& elem) {
    boost::unique_lock<boost::mutex> lk(sync_queue_base<T>::m_mtx);
    return try_push(elem, lk);
}
template<typename T>
queue_op_status sync_queue<T>::try_push(const T& elem, boost::unique_lock<boost::mutex>& lk) {
    if (sync_queue_base<T>::closed(lk)) {
        return queue_op_status::closed;
    }
    push(elem, lk);
    return queue_op_status::success;
}


template<typename T>
queue_op_status sync_queue<T>::wait_push(const T& elem) {
    boost::unique_lock<boost::mutex> lk(sync_queue_base<T>::m_mtx);
    return wait_push(elem, lk);
}
template<typename T>
queue_op_status sync_queue<T>::wait_push(const T& elem, boost::unique_lock<boost::mutex>& lk) {
    if (sync_queue_base<T>::closed(lk)) {
        return queue_op_status::closed;
    }
    push(elem, lk);
}


template<typename T>
queue_op_status sync_queue<T>::nonblocking_push(const T& elem) {
    boost::unique_lock<boost::mutex> lk(sync_queue_base<T>::m_mtx, boost::try_to_lock);
    if (!lk.owns_lock()) {
        return queue_op_status::busy;
    }
    return try_push(elem, lk);
}

template<typename T>
queue_op_status sync_queue<T>::try_pull(T& elem) {
    boost::unique_lock<boost::mutex> lk(sync_queue_base<T>::m_mtx);
    return try_pull(elem, lk);
}
template<typename T>
queue_op_status sync_queue<T>::try_pull(T& elem, boost::unique_lock<boost::mutex>& lk) {
    if (sync_queue_base<T>::empty(lk)) {
        if (sync_queue_base<T>::closed(lk)) {
            return queue_op_status::closed;
        }
        return queue_op_status::empty;
    }
    pull(elem, lk);
    return queue_op_status::success;
}
template<typename T>
queue_op_status sync_queue<T>::nonblocking_pull(T& elem) {
    boost::unique_lock<boost::mutex> lk(sync_queue_base<T>::m_mtx, boost::try_to_lock);
    if (!lk.owns_lock()) {
        return queue_op_status::busy;
    }
    return try_pull(elem, lk);
}
template<typename T>
queue_op_status sync_queue<T>::wait_pull(T& elem) {
    boost::unique_lock<boost::mutex> lk(sync_queue_base<T>::m_mtx);
    return wait_pull(elem, lk);
}
template<typename T>
queue_op_status sync_queue<T>::wait_pull(T& elem, boost::unique_lock<boost::mutex>& lk) {
    const bool has_been_closed = sync_queue_base<T>::wait_until_not_empty_or_closed(lk);
    if (has_been_closed) {
        return queue_op_status::closed;
    }
    pull(elem, lk);
    return queue_op_status::success;
}
template<typename T>
//sync_queue<T>::value_type sync_queue<T>::pull() {
T sync_queue<T>::pull() {
    boost::unique_lock<boost::mutex> lk(m_mtx);
    const bool has_been_closed = sync_queue_base<T>::wait_until_not_empty_or_closed(lk);
    if (has_been_closed) {
        sync_queue_base<T>::throw_if_closed(lk);
    }
}
template<typename T>
T sync_queue<T>::pull(boost::unique_lock<boost::mutex>& lk) {
    // 还是有move的时候才提供这个版本比较好
    //typename T ret = std::move(sync_queue_base<T>::m_data.front()); 
    T ret = std::move(sync_queue_base<T>::m_data.front()); 
    sync_queue_base<T>::m_data.pop_front();
    return ret;
}


int bbq_test(const int concurrency) {
    const int num = 1000 * 1000;
    typedef boost::shared_ptr<int> data_type;
    blocking_queue<data_type> queue;
    boost::thread_group thg;
    struct timespec start;
    clock_gettime(CLOCK_MONOTONIC, &start);
    for (int tr = 0; tr < concurrency; ++tr) {
        thg.create_thread([&]() {
            data_type dat;
            for (int i = 0; i < num; ++i) {
                //queue.wait_pull_front(dat);
                //queue.wait_pull_front(dat);
            }
        });
    }
    for (int tr = 0; tr < concurrency; ++tr) {
        thg.create_thread([&]() {
            data_type dat(new int(42));
            for (int i = 0; i < num; ++i) {
                //queue.wait_push_back(dat);
            }
        });
    }
    thg.join_all();
    printTime(start, "bbq_test.");
    return 0;
}
