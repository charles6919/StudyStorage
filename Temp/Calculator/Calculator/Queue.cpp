#include "stdafx.h"
#include "Queue.h"
#include "Node.h"


Queue::Queue()
	: m_pFront(NULL)
	, m_pRear(NULL)
{
}


Queue::~Queue()
{
	Node* curr = m_pFront;
	Node* prev;

	while (curr)
	{
		prev = curr;
		curr = curr->m_pNext;
		delete prev;
	}
}

bool Queue::IsEmpty()
{
	if (m_pFront)
		return false;
	else
		return true;
}

void Queue::Enqueue(char* str)
{
	if (m_pFront)
		m_pRear->Insert(str);
	else
		m_pFront = m_pRear = new Node(str);
}

void Queue::Enqueue(Node* p)
{
	if (m_pFront)
	{
		m_pRear->m_pNext = p;
		m_pRear = p;
	}
	else
		m_pFront = m_pRear = p;
}

Node* Queue::Dequeue()
{
	if (!m_pFront) return NULL;

	Node* temp = m_pFront;
	m_pFront = m_pFront->m_pNext;
	return temp;
}

void Queue::Print()
{
	if (m_pFront)
		m_pFront->Print();
}
