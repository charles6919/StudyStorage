#pragma once

template<typename T>
class Binary_Node
{
public:
	int m_nKey;
	T m_tData;
	Binary_Node<T>* m_pLeft;
	Binary_Node<T>* m_pRight;

	int m_nDummy[1000000];

public:
	Binary_Node(int key, T data);
	~Binary_Node();

	void Insert(int key, T data);
	void Delete(int key, Binary_Node<T>** ppPrev);
	void Print();
	Binary_Node<T>* Find(int key);
};

template<typename T>
inline Binary_Node<T>::Binary_Node(int key, T data)
	:
	m_nKey(key),
	m_tData(data),
	m_pLeft(nullptr),
	m_pRight(nullptr)
{
}

template<typename T>
inline Binary_Node<T>::~Binary_Node()
{
	if(m_pLeft)
		delete m_pLeft;

	if (m_pRight)
		delete m_pRight;
}

template<typename T>
inline void Binary_Node<T>::Insert(int key, T data)
{
	if (key == m_nKey)
	{
		cout << "Insert Error : 동일한 키값이 존재합니다." << endl;
	}
	else
	{
		if (key < m_nKey)
		{
			if (m_pLeft)
			{
				m_pLeft->Insert(key, data);
			}
			else
			{
				m_pLeft = new Binary_Node<T>(key, data);
			}
		}
		else
		{
			if (m_pRight)
			{
				m_pRight->Insert(key, data);
			}
			else
			{
				m_pRight = new Binary_Node<T>(key, data);
			}
		}
	}
}

template<typename T>
inline void Binary_Node<T>::Delete(int key, Binary_Node<T>** ppPrev)
{	

	if (key == this->m_nKey)
	{
		//키값이 일치
		if (!this->m_pLeft && !this->m_pRight)
		{
			//찾은 노드에 서브트리가 없는경우
			*ppPrev = nullptr;
			delete this;
		}
		else
		{
			//찾은 노드에 서브트리가 있는경우
			if (this->m_pLeft)
			{
				//왼쪽
				Binary_Node<T>* temp = this->m_pLeft;
				Binary_Node<T>** ppTempPrev = &this->m_pLeft;
				

				while (temp->m_pRight)
				{
					ppTempPrev = &temp->m_pRight;
					temp = temp->m_pRight;
				}

				this->m_nKey = temp->m_nKey;
				this->m_tData = temp->m_tData;

				if (temp->m_pLeft)
				{
					*ppTempPrev = temp->m_pLeft;
					temp->m_pLeft = nullptr;
					delete temp;
				}
				else
				{
					*ppTempPrev = nullptr;
					delete temp;
				}

			}
			else
			{
				//오른쪽
				Binary_Node<T>* temp = this->m_pRight;
				Binary_Node<T>** ppTempPrev = &this->m_pRight;

				while (temp->m_pLeft)
				{
					ppTempPrev = &temp->m_pLeft;
					temp = temp->m_pLeft;
				}

				this->m_nKey = temp->m_nKey;
				this->m_tData = temp->m_tData;

				if (temp->m_pRight)
				{
					*ppTempPrev = temp->m_pRight;
					temp->m_pRight = nullptr;
					delete temp;
				}
				else
				{
					*ppTempPrev = nullptr;
					delete temp;
				}
			}
		}	
	}
	else
	{
		//키값이 다름
		if (key > this->m_nKey)
		{
			//오른쪽으로 이동
			if (this->m_pRight)
				this->m_pRight->Delete(key, &this->m_pRight);
			else
				return;
		}
		else
		{
			//왼쪽으로 이동
			if (this->m_pLeft)
				this->m_pLeft->Delete(key, &this->m_pLeft);
			else
				return;
		}
	}
}

template<typename T>
inline void Binary_Node<T>::Print()
{
	if (m_pLeft)
		m_pLeft->Print();

	cout << "key-> " << this->m_nKey << " : " << this->m_tData << endl;

	if (m_pRight)
		m_pRight->Print();
}

template<typename T>
inline Binary_Node<T>* Binary_Node<T>::Find(int key)
{
	if (key == m_nKey)
	{
		return this;
	}
	else
	{
		if (key < m_nKey)
		{
			if (m_pLeft)
			{
				m_pLeft->Find(key);
			}
			else
			{
				return nullptr;
			}
		}
		else
		{
			if (m_pRight)
			{
				m_pRight->Find(key);
			}
			else
			{
				return nullptr;
			}
		}
	}
}
