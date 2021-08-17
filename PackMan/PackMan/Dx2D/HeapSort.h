#pragma once
#define GET_PARENTS_INDEX(I) ((I+1) * 0.5f - 1)
#define GET_CHILD_INDEX_LEFT(I) ((I*2) + 1)
#define GET_CHILD_INDEX_RIGHT(I) ((I*2) + 2)

template <typename T>
class HeapSort
{
private:
	vector<T> m_vecData;

private:
	void Swap(int src, int dest);
	void UpdateUpper();
	void UpdateLower();

public:
	HeapSort();
	~HeapSort();

	void Insert(T data);
	T GetData();
};


template<typename T>
inline HeapSort<T>::HeapSort()
{
}

template<typename T>
inline HeapSort<T>::~HeapSort()
{
	m_vecData.clear();
}


template<typename T>
inline void HeapSort<T>::Swap(int src, int dest)
{
	T temp = m_vecData[src];
	m_vecData[src] = m_vecData[dest];
	m_vecData[dest] = temp;
}

template<typename T>
inline void HeapSort<T>::UpdateUpper()
{
	bool isUpper = true;
	int currIndex = m_vecData.size() - 1;
	while (isUpper)
	{
		isUpper = false;
		if (currIndex > 0)
		{
			int parentIndex = GET_PARENTS_INDEX(currIndex);
			if (m_vecData[currIndex] < m_vecData[parentIndex])
			{
				Swap(currIndex, parentIndex);
				currIndex = parentIndex;
				isUpper = true;
			}
		}
	}
}


template<typename T>
inline void HeapSort<T>::Insert(T data)
{
	m_vecData.push_back(data);
	UpdateUpper();
}

template<typename T>
inline void HeapSort<T>::UpdateLower()
{
	if (m_vecData.size() > 0)
	{

		int child_L;
		int child_R;
		bool enableLeftLower ;
		bool enableRightLower;
		bool isLower = true;
		int currIndex = 0;

		while (isLower)
		{
			child_L = GET_CHILD_INDEX_LEFT(currIndex);
			child_R = GET_CHILD_INDEX_RIGHT(currIndex);

			enableLeftLower = false;
			enableRightLower = false;
			isLower = false;

			if (child_L <= m_vecData.size() - 1 && m_vecData[currIndex] > m_vecData[child_L])
				enableLeftLower = true;

			if (child_R <= m_vecData.size() - 1 && m_vecData[currIndex] > m_vecData[child_R])
				enableRightLower = true;

			if (enableLeftLower && enableRightLower)
			{
				if (m_vecData[child_L] < m_vecData[child_R])
				{
					Swap(currIndex, child_L);
					currIndex = child_L;
					isLower = true;
				}
				else
				{
					Swap(currIndex, child_R);
					currIndex = child_R;
					isLower = true;
				}
			}
			else if (enableLeftLower)
			{
				Swap(currIndex, child_L);
				currIndex = child_L;
				isLower = true;
			}
			else if (enableRightLower)
			{
				Swap(currIndex, child_R);
				currIndex = child_R;
				isLower = true;
			}
			else
			{
				break;
			}
		}
	}
}

template<typename T>
inline T HeapSort<T>::GetData()
{
	T root = *m_vecData.begin();
	Swap(0, m_vecData.size() - 1);
	m_vecData.pop_back();

	UpdateLower();

	return root;
}

/*
3
4	6



*/
