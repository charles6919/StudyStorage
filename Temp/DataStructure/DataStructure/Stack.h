#pragma once
#include "Node.h"

template<typename T>
class Stack
{
private:
	Node<T>* m_pTop;

public:
	Stack();
	~Stack();

	bool IsEmpty();
	void Push(T data);	
	T Pop();
	T Peek();
	
};

template<typename T>
inline Stack<T>::Stack()
	:
	m_pTop(nullptr)
{

}

template<typename T>
inline Stack<T>::~Stack()
{
	Node<T>* temp;

	while (!IsEmpty())
	{
		temp = m_pTop;
		m_pTop = m_pTop->m_pNext;
		delete temp;
	}


}

template<typename T>
inline bool Stack<T>::IsEmpty()
{
	if (m_pTop == nullptr)
		return true;
	else
		return false;
}

template<typename T>
inline void Stack<T>::Push(T data)
{
	Node<T>* temp = new Node<T>(data);
	temp->m_pNext = m_pTop;
	m_pTop = temp;
}

template<typename T>
inline T Stack<T>::Pop()
{
	if (IsEmpty())
	{
		cout << "MemoryError!! Stack is Empty!!" << endl;
		exit(-1);
	}

	Node<T>* temp = m_pTop;
	m_pTop = m_pTop->m_pNext;
	T data = temp->m_tData;
	delete temp;

	return data;
}

template<typename T>
inline T Stack<T>::Peek()
{
	if (IsEmpty())
	{
		cout << "MemoryError!! Stack is Empty!!" << endl;
		exit(-1);
	}
	
	return m_pTop->m_tData;
}
