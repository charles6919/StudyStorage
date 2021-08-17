#pragma once
#include "iGameNode.h"
#include "HeapSort.h"
class SortTest : public iGameNode
{

#define NUM_DATA 10
	vector<int> m_vecData;
	vector<int> m_vecSortData;
	HeapSort<int> m_vecHeapData;
	int m_nSortNum;


public:
	SortTest();
	~SortTest();

	virtual void Init()		override;
	virtual void Update()	override;
	virtual void Render()	override;
	virtual void Release()	override;
};

