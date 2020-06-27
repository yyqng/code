#ifndef __queue_H
#define __queue_H
#include <iostream>
#include <thread>
#include <list>
#include <mutex> 
#include <condition_variable>
#include <time.h>
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
class Queue : noncopyable {
public:
    Queue(size_t size) : m_ring(size) {}
    void push(const T& ele);
    void pop(T& ele);
    bool empty() const;
    bool full() const;
private:
    Ring_buffer<T> m_ring;
    mutable std::mutex m_mutex;
    std::condition_variable m_writable;
    std::condition_variable m_readable;
};

void queue_test();

#endif
