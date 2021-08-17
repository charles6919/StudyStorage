#pragma once

class Node;

class Queue
{
public:
	Node*	m_pFront;
	Node*	m_pRear;

public:
	Queue();
	~Queue();

	bool IsEmpty();
	void Enqueue(char* str);
	void Enqueue(Node* p);
	Node* Dequeue();
	void Print();
};

