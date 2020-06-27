#pragma once
#ifndef __MYQUEUE_H
#define __MYQUEUE_H
#include<iostream>
using namespace std;

template<typename T>
class Ring_buffer
{
public:
	Ring_buffer(int capacity);
	virtual ~Ring_buffer();
	void clear();
	bool empty() const;
	bool full() const;
	int length() const;
	bool push(T element);
	bool pop(T &element);
	bool front(T &element);
	void print();
private:
	T *m_pQ;
	int m_size;
	int m_capacity;
	int m_head;
	int m_tail;
};
int ring_test(void);

#endif // !MYQUEUE_H
