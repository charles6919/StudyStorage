#include "stdafx.h"
#include "Stack.h"
#include "Node.h"


Stack::Stack()
	: m_pTop(NULL)
{
}


Stack::~Stack()
{
}

bool Stack::IsEmpty()
{
	if (m_pTop)
		return false;
	else
		return true;
}

void Stack::Push(char* str)
{
	m_pTop = new Node(m_pTop, str);
}

Node* Stack::Pop()
{
	if (!m_pTop) return NULL;

	Node* temp = m_pTop;
	m_pTop = m_pTop->m_pNext;
	return temp;
}

void Stack::Print()
{
	if (m_pTop)
		m_pTop->Print();
}
