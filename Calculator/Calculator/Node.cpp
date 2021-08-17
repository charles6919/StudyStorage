#include "stdafx.h"
#include "Node.h"


Node::Node()
	: m_pNext(NULL)
	, m_strData('\0')
{
}

Node::Node(char* str)
	: m_pNext(NULL)
	, m_strData(str)
{
}

Node::Node(Node* prevTop, char* str)
	: m_pNext(prevTop)
	, m_strData(str)
{
}


Node::~Node()
{
}

void Node::Insert(char* str)
{
	if (m_pNext != NULL)
		m_pNext->Insert(str);
	else
		m_pNext = new Node(str);
}

void Node::Delete(LPNODE* ppNext, char* str)
{
	if (m_strData == str)
	{
		*ppNext = m_pNext;
		delete this;
	}
	else if (m_pNext)
	{
		m_pNext->Delete(&m_pNext, str);
	}
	else
	{
		cout << "The data is not found" << endl;
	}
}

void Node::Print()
{
	cout << m_strData << endl;

	if (m_pNext)
		m_pNext->Print();
}

void Node::Reverse(Node* prev)
{
	if (m_pNext)
		m_pNext->Reverse(this);
	m_pNext = prev;
}

Node* Node::GetTail()
{
	if (m_pNext)
		return m_pNext->GetTail();

	return this;
}
