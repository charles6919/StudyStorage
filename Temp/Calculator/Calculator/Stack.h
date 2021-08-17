#pragma once

class Node;

class Stack
{
public:
	Node*	m_pTop;

public:
	Stack();
	~Stack();

	bool IsEmpty();
	void Push(char* str);
	Node* Pop();
	void Print();
};

