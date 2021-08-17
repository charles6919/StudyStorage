#pragma once

class Node;

typedef Node* LPNODE;

class Node
{
public:
	Node*	m_pNext;
	char*	m_strData;

	int		m_arrDummy[1024];

public:
	Node();

	Node(char* str);
	Node(Node* prevTop, char* str);
	~Node();

	void Insert(char* str);
	void Delete(LPNODE* ppNext, char* str);
	void Print();
	void Reverse(Node* prev);
	Node* GetTail();
};

