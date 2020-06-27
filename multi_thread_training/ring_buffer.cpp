#include "ring_buffer.h"

template<typename T>
Ring_buffer<T>::Ring_buffer(int capacity)
{
	m_capacity = capacity;
	m_pQ = new T[m_capacity];
	clear();
}

template<typename T>
Ring_buffer<T>::~Ring_buffer()
{
	delete[] m_pQ;
	m_pQ = NULL;
}

template<typename T>
void Ring_buffer <T>::clear()
{
	m_head = 0;
	m_tail = 0;
	m_size = 0;
}

template<typename T>
bool Ring_buffer <T>::empty() const
{
	return m_size == 0 ? true : false;
}

template<typename T>
int Ring_buffer <T>::length() const
{
	return m_size;
}

template<typename T>
bool Ring_buffer <T>::full() const
{
	return m_size == m_capacity ? true : false;
}

template<typename T>
bool Ring_buffer <T>::push(T element)
{
	if (full()) {
		return false;
	} else {
		m_pQ[m_tail] = element;
		m_tail++;
		m_tail = m_tail % m_capacity;
		m_size++;
		return true;
	}
}

template<typename T>
bool Ring_buffer <T>::pop(T &element)
{
	if (empty()) {
		return false;
	} else {
		element = m_pQ[m_head] ;
		m_head++;
		m_head = m_head % m_capacity;
		m_size--;
		return true;
	}
}

template<typename T>
void Ring_buffer <T>::print()
{
	for (int i = m_head; i < m_size + m_head; i++) {
		cout << m_pQ[i % m_capacity] << endl;
	}
	cout << endl;
}

int ring_test(void)
{
	Ring_buffer<int> ring(4);
	ring.push(10);
	ring.push(12);
	ring.push(14);
	int e = 0;
	ring.print();

	ring.pop(e);
	cout << e << endl << endl;

	ring.print();
	return 0;
}
