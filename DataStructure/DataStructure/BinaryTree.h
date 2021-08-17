#pragma once
#include "Binary_Node.h"
template<typename T>
class BinaryTree
{
private:
	Binary_Node<T>* m_pRoot;

public:
	BinaryTree();
	~BinaryTree();

	bool IsEmpty();
	void Insert(int key, T data);
	void Delete(int key);
	T	 Search(int key);
	void Print();
};

template<typename T>
inline BinaryTree<T>::BinaryTree()
	:
	m_pRoot(nullptr)
{
}

template<typename T>
inline BinaryTree<T>::~BinaryTree()
{

}

template<typename T>
inline bool BinaryTree<T>::IsEmpty()
{
	if (m_pRoot)
		return false;
	else
		return true;
}

template<typename T>
inline void BinaryTree<T>::Insert(int key, T data)
{
	if (IsEmpty())
	{
		m_pRoot = new Binary_Node<T>(key, data);
	}
	else
		m_pRoot->Insert(key, data);
}

template<typename T>
inline void BinaryTree<T>::Delete(int key)
{
	if (IsEmpty()) return;

	m_pRoot->Delete(key, &m_pRoot);
}

template<typename T>
inline T BinaryTree<T>::Search(int key)
{
	if (IsEmpty())
	{
		cout << "Search Error : Tree is Empty!!" << endl;
		exit(-1);
	}

	Binary_Node<T>* find = m_pRoot->Find(key);

	if (find)
		return find->m_tData;
	else
	{
		cout << "Search Faliure : unavilable key value" << endl;
		exit(-1);
	}
}

template<typename T>
inline void BinaryTree<T>::Print()
{
	if (IsEmpty()) return;

	m_pRoot->Print();
}
