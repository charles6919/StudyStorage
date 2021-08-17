#pragma once
template<typename T>
class Node
{
public:
	Node*	m_pNext;
	T		m_tData;

public:
	Node() {};
	Node(T data);
	~Node();
};

template<typename T>
inline Node<T>::Node(T data)
	:m_tData(data),
	m_pNext(NULL)
{
}

template<typename T>
inline Node<T>::~Node()
{
}
