#ifndef __BBQ_H
#define __BBQ_H
#include <bitset>
#include <set>
#include <map>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <ios>
#include <iostream>
#include <fstream>
#include <string>
#include <thread>
#include <chrono>
//#include <boost/chrono>
#include <cstring>
#include <pthread.h>
#include <mutex> 
#include <assert.h>
#include <boost/thread.hpp>
#include <exception>
#include <condition_variable>
#include <atomic>
#include <future>
#include <time.h>
#include <queue>
#include <boost/circular_buffer.hpp>
#include "tools.h"

using namespace std;

template<typename T>
class blocking_queue : boost::noncopyable {
    std::queue<T> m_queue;
    boost::condition_variable m_cond;
    mutable boost::mutex m_mutex;
public:
    blocking_queue() {}
    void push(const T& val);
    void pop(T& val);
    bool try_pop(T& val);
    size_t size() const;
    bool empty() const;
};

template<typename T>
class bounded_blocking_queue_1 : boost::noncopyable {
    boost::circular_buffer<T> m_queue;
    boost::condition_variable m_cond_not_full;
    boost::condition_variable m_cond_not_empty;
    mutable boost::mutex m_mutex;
public:
    bounded_blocking_queue_1(size_t max_size) : m_queue(max_size) {}
    void push(const T& val);
    bool try_push(const T& val);
    void pop(T& val);
    bool try_pop(const T& val);
    size_t size() const;
    size_t capacity() const;
    bool empty() const;
    bool full() const;
};


// boost/thread/concurrent_queues/queue_op_status.hpp
enum queue_op_status {
    success = 0, 
    empty, 
    full, 
    closed, 
    busy, 
    timeout, 
    not_ready
};

template <typename T>
class sync_queue_base {
public:
    typedef T value_type;
    typedef std::queue<T> underlying_queue_type;
    typedef typename std::queue<T>::size_type size_type;
    sync_queue_base();
    ~sync_queue_base();
public:
    bool empty() const;
    bool full() const;
    size_type size() const;
    bool closed() const;
    void close();
protected:
    mutable boost::mutex m_mtx;
    boost::condition_variable m_cond_not_empty;
    underlying_queue_type m_data;
    bool m_closed;
};

template <typename T>
class sync_queue: public sync_queue_base<T> {
public:
    typedef T value_type;
    sync_queue();
    ~sync_queue();
public:
    typedef std::queue<T> underlying_queue_type;
    mutable boost::mutex m_mtx;
    boost::condition_variable m_cond_not_empty;
    underlying_queue_type m_data;
    bool m_closed;

    void push(const value_type& x);
    void push(const value_type& elem, boost::unique_lock<boost::mutex>& lk);
    queue_op_status try_push(const value_type& x);
    queue_op_status try_push(const value_type& elem, boost::unique_lock<boost::mutex>& lk);
    queue_op_status nonblocking_push(const value_type& x);
    queue_op_status wait_push(const value_type& x);
    queue_op_status wait_push(const value_type& elem, boost::unique_lock<boost::mutex>& lk);
    // 我们愉快地忽略右值版本
    void pull(value_type& elem, boost::unique_lock<boost::mutex>& lk);
    void pull(value_type& elem);
    value_type pull();
    value_type pull(boost::unique_lock<boost::mutex>& lk);
    queue_op_status try_pull(value_type& elem);
    queue_op_status try_pull(T& elem, boost::unique_lock<boost::mutex>& lk);
    queue_op_status nonblocking_pull(value_type& elem);
    queue_op_status wait_pull(value_type& elem);
    queue_op_status wait_pull(T& elem, boost::unique_lock<boost::mutex>& lk);
};

int bbq_test(const int concurrency);

#endif
