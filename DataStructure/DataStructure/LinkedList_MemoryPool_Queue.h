#pragma once
#include "Node.h"
template<typename T>
class LinkedList_MemoryPool_Queue
{
private:
	Queue<T>* m_pQueue;
	Queue<T>* m_pMemoryPool;

public:
	LinkedList_MemoryPool_Queue();
	~LinkedList_MemoryPool_Queue();

	bool	IsQueueEmpty();
	bool	IsMemoryPoolEmpty();
	void	EnQueue(T data);
	T		DeQueue();
	T		Peek();
	void	Clear();
	
};

template<typename T>
inline LinkedList_MemoryPool_Queue<T>::LinkedList_MemoryPool_Queue()
	:
	m_pQueue(nullptr),
	m_pMemoryPool(nullptr)
{
	m_pQueue = new Queue<T>;
	m_pMemoryPool = new Queue<T>;
}

template<typename T>
inline LinkedList_MemoryPool_Queue<T>::~LinkedList_MemoryPool_Queue()
{
	if (m_pMemoryPool)
	{
		m_pMemoryPool->Clear();
		delete m_pMemoryPool;
	}

	if (m_pQueue)
	{
		m_pQueue->Clear();
		delete m_pQueue;
	}
}

template<typename T>
inline bool LinkedList_MemoryPool_Queue<T>::IsQueueEmpty()
{
	if (m_pQueue->IsEmpty())
		return true;
	else
		return false;
}

template<typename T>
inline bool LinkedList_MemoryPool_Queue<T>::IsMemoryPoolEmpty()
{
	if (m_pMemoryPool->IsEmpty())
		return true;
	else
		return false;
}

template<typename T>
inline void LinkedList_MemoryPool_Queue<T>::EnQueue(T data)
{
	if (IsMemoryPoolEmpty())
	{
		m_pQueue->Enqueue(data);
	}
	else
	{
		Node<T>* temp = m_pMemoryPool->PopNode();
		temp->m_pNext = nullptr;
		temp->m_tData = data;
		m_pQueue->PushNode(temp);
	}
}

template<typename T>
inline T LinkedList_MemoryPool_Queue<T>::DeQueue()
{
	if (m_pQueue->IsEmpty())
	{
		cout << "Memory Error!! LinkedList MemoryPool Queue is Empty!!" << endl;
		exit(-1);
	}
	else
	{
		T temp = m_pQueue->Peek();
		m_pMemoryPool->PushNode(m_pQueue->PopNode());
		return temp;
	}
}

template<typename T>
inline T LinkedList_MemoryPool_Queue<T>::Peek()
{
	if (m_pQueue->IsEmpty())
	{
		cout << "Memory Error!! LinkedList MemoryPool Queue is Empty!!" << endl;
		exit(-1);
	}
	else
	{
		return m_pQueue->Peek();
	}
}

template<typename T>
inline void LinkedList_MemoryPool_Queue<T>::Clear()
{
	if (m_pMemoryPool)
		m_pMemoryPool->Clear();

	if (m_pQueue)
		m_pQueue->Clear();
}
