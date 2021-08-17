#pragma once
#include "Node.h"
template <typename T>
class Queue
{
private:
	Node<T>* m_pFront;
	Node<T>* m_pRear;

public:
	Queue();
	~Queue();

	bool IsEmpty();
	void Enqueue(T data);
	T DeQueue();
	T Peek();
	void Clear();

	Node<T>* PopNode();
	void PushNode(Node<T>* p);

};

template<typename T>
inline Queue<T>::Queue()
	:
	m_pFront(nullptr),
	m_pRear(nullptr)
{
	
}

template<typename T>
inline Queue<T>::~Queue()
{
	while (!IsEmpty())
	{
		DeQueue();
	}
}

template<typename T>
inline bool Queue<T>::IsEmpty()
{
	if (m_pFront == nullptr)
		return true;
	else
		return false;
}

template<typename T>
inline void Queue<T>::Enqueue(T data)
{
	Node<T>* rear = new Node<T>(data);
	rear->m_pNext = nullptr;

	if (IsEmpty())
	{
		m_pFront = m_pRear = rear;
	}
	else
	{
		m_pRear->m_pNext = rear;
		m_pRear = rear;
	}
	
}

template<typename T>
inline T Queue<T>::DeQueue()
{
	if (IsEmpty())
	{
		cout << "MemoryError!! Queue is Empty!!" << endl;
		exit(-1);
	}

	Node<T>* front;

	front = m_pFront;
	m_pFront = front->m_pNext;
	T data = front->m_tData;
	delete front;

	return data;
}

template<typename T>
inline T Queue<T>::Peek()
{
	if (IsEmpty())
	{
		cout << "MemoryError!! Queue is Empty!!" << endl;
		exit(-1);
	}

	return m_pFront->m_tData;
}

template<typename T>
inline void Queue<T>::Clear()
{
	while (!IsEmpty())
	{
		DeQueue();
	}
}

template<typename T>
inline Node<T>* Queue<T>::PopNode()
{
	if (IsEmpty())
	{
		cout << "MemoryError!! Queue is Empty!!" << endl;
		exit(-1);
	}

	Node<T>* front;

	front = m_pFront;
	m_pFront = m_pFront->m_pNext;
	front->m_pNext = nullptr;
	return front;
}

template<typename T>
inline void Queue<T>::PushNode(Node<T>* p)
{

	if (IsEmpty())
	{
		m_pFront = m_pRear = p;
	}
	else
	{
		m_pRear->m_pNext = p;
		m_pRear = p;
	}
}
