#pragma once
template<typename T>
class Circular_Queue
{
private:
	T* m_arrNode;
	int m_nFront;
	int m_nRear;
	const int size;

public:
	Circular_Queue(const int arrSize);
	~Circular_Queue();

	bool IsEmpty();
	bool IsFull();
	void EnQueue(T data);
	T DeQueue();
	T Peek();
};

template<typename T>
inline Circular_Queue<T>::Circular_Queue(const int arrSize)
	:
	size(arrSize)
{
	m_nFront = m_nRear = 0;
	m_arrNode = new T[size];

}

template<typename T>
inline Circular_Queue<T>::~Circular_Queue()
{
	delete[] m_arrNode;
}

template<typename T>
inline bool Circular_Queue<T>::IsEmpty()
{
	if (m_nFront == m_nRear)
		return true;
	else
		return false;
}

template<typename T>
inline bool Circular_Queue<T>::IsFull()
{
	if ((m_nRear + 1) %  size == m_nFront )
		return true;
	else
		return false;
}

template<typename T>
inline void Circular_Queue<T>::EnQueue(T data)
{
	if (IsFull())
	{
		cout << "Circular_Queue is Full" << endl;
		Sleep(1000);
		return;
	}
	else
	{
		m_arrNode[m_nRear] = data;
		m_nRear++;
		m_nRear %= size;
	}

}

template<typename T>
inline T Circular_Queue<T>::DeQueue()
{
	T temp;

	if (IsEmpty())
	{
		cout << "Memory Error!! Circular_Queue is Empty!!" << endl;
		exit(-1);
	}
	else
	{
		temp = m_arrNode[m_nFront];
		m_nFront++;
		m_nFront %= size;
	}

	return temp;
}

template<typename T>
inline T Circular_Queue<T>::Peek()
{
	T temp;

	if (IsEmpty())
	{
		cout << "Memory Error!! Circular_Queue is Empty!!" << endl;
		exit(-1);
	}
	else
	{
		temp = m_arrNode[m_nFront];
	}

	return temp;
}
