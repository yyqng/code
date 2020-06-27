#ifndef __Myqueue_H
#define __Myqueue_H
#include <iostream>
#include <fstream>
#include <string>
#include <thread>
#include <chrono>
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
#include "ring_buffer.h"

using namespace std;

class noncopyable
{
 public:
  noncopyable(const noncopyable&) = delete;
  void operator=(const noncopyable&) = delete;

 protected:
  noncopyable() = default;
  ~noncopyable() = default;
};

template<typename T>
class Myqueue : noncopyable {
public:
    Myqueue(size_t size) : m_ring(size) {}
    void push(const T& ele);
    bool try_push(const T& ele);
    void pop(T& ele);
    bool try_pop(const T& ele);
    size_t size() const;
    size_t capacity() const;
    bool empty() const;
    bool full() const;
private:
    Ring_buffer<T> m_ring;
    boost::condition_variable m_cond_not_full;
    boost::condition_variable m_cond_not_empty;
    mutable boost::mutex m_mutex;
};

int myqueue_test(const int concurrency);

#endif
