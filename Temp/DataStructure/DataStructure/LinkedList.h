#pragma once
#include "Node.h"


template<typename T>
class LinkedList
{
private:
	Node<T>* m_pHead;


public:
	LinkedList();
	~LinkedList();

	bool IsEmpty();
	void Insert(T data);
	void Delete(T data);
	void Print();
	void Reverse();
	void Clear();
};

template<typename T>
inline LinkedList<T>::LinkedList()
	:
	m_pHead(NULL)
{

}

template<typename T>
inline LinkedList<T>::~LinkedList()
{
	Node<T>* temp = m_pHead;
	Node<T>* pCurr;
	
	while (temp)
	{
		pCurr = temp;
		temp = pCurr->m_pNext;
		delete pCurr;
	}
}

template<typename T>
inline bool LinkedList<T>::IsEmpty()
{
	if (m_pHead == NULL)
		return true;
	else
		return false;
}

template<typename T>
inline void LinkedList<T>::Insert(T data)
{

	if (m_pHead == NULL)
	{
		m_pHead = new Node<T>(data);
	}
	else
	{
		Node<T>* temp = m_pHead;

		while (temp->m_pNext != NULL)
		{
			temp = temp->m_pNext;
		}
		temp->m_pNext = new Node<T>(data);
	}
}

template<typename T>
inline void LinkedList<T>::Delete(T data)
{
	if (m_pHead == NULL) return;

	Node<T>* find = m_pHead;
	Node<T>* prev = NULL;

	while (find)
	{
		if (find->m_tData == data)
		{
			break;
		}
		prev = find;
		find = find->m_pNext;
	}

	if (find == NULL)
		cout << "The data is not found" << endl;
	else
	{
		if (prev == NULL)
		{
			m_pHead = find->m_pNext;
		}
		else
			prev->m_pNext = find->m_pNext;
		delete find;

	}
}

template<typename T>
inline void LinkedList<T>::Print()
{
	if (m_pHead == NULL)
	{
		cout << "Linked List is Empty." << endl;
		return;
	}

	Node<T>* temp = m_pHead;

	while (temp != NULL)
	{
		cout << temp->m_tData << " , ";
		temp = temp->m_pNext;
	}
	cout << endl;
}

template<typename T>
inline void LinkedList<T>::Reverse()
{
	if (m_pHead == NULL) return;

	Node<T>* newHead;
	Node<T>* next;

	newHead = m_pHead;
	next = m_pHead->m_pNext;
	int count = 0;

	while (next)
	{
		newHead = next;
		next = newHead->m_pNext;
		newHead->m_pNext = m_pHead;
		if (count == 0)
		{
			m_pHead->m_pNext = NULL;
			count++;
		}
		m_pHead = newHead;
	}
}

template<typename T>
inline void LinkedList<T>::Clear()
{
	Node<T>* newHead;
	newHead = m_pHead;
	
	while (!IsEmpty())
	{
		m_pHead = m_pHead->m_pNext;
		delete newHead;
	}
}
