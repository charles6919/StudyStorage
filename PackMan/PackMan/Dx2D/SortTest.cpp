#include "stdafx.h"
#include "SortTest.h"


SortTest::SortTest()
{
}

SortTest::~SortTest()
{
}

void SortTest::Init()
{


	for (int i = 0; i < NUM_DATA; i++)
	{
		int rnd = rand() % 100;

		m_vecHeapData.Insert(rnd);
		m_vecData.push_back(rnd);

	}

	m_nSortNum = 0;

}

void SortTest::Update()
{
	if (g_pKeyManager->isOnceKeyDown('1'))
	{
		for (int i = 0; i < NUM_DATA - 1; i++)
		{
			int min = INT_MAX;
			int minIndex = 0;
			for (int j = i; j < NUM_DATA; j++)
			{
				if (m_vecSortData[j] < min)
				{
					min = m_vecSortData[j];
					minIndex = j;
				}
				m_nSortNum++;
			}
			int temp = m_vecSortData[i];
			m_vecSortData[i] = m_vecSortData[minIndex];
			m_vecSortData[minIndex] = temp;

		}
	}
	else if (g_pKeyManager->isOnceKeyDown('2'))
	{
		for (int i = 1; i < NUM_DATA; i++)
		{
			int currIndex = i;
			for (int j = currIndex - 1; j >= 0; j--)
			{
				if (m_vecSortData[currIndex] < m_vecSortData[j])
				{
					int temp = m_vecSortData[currIndex];
					m_vecSortData[currIndex] = m_vecSortData[j];
					m_vecSortData[j] = temp;
					currIndex--;
				}
				else
					break;
				m_nSortNum++;
			}
		}
	}
	else if (g_pKeyManager->isOnceKeyDown('3'))
	{
		bool isSort = false;
		for (int i = NUM_DATA -1 ; i >= 1; i--)
		{
			isSort = false;
			for (int j = 0; j < i; j++)
			{
				if (m_vecSortData[j] > m_vecSortData[j + 1])
				{
					isSort = true;
					int temp = m_vecSortData[j];
					m_vecSortData[j] = m_vecSortData[j + 1];
					m_vecSortData[j + 1] = temp;
				}
				m_nSortNum++;
			}
			if (!isSort)
			{
				break;
			}
		}
	}
	else if (g_pKeyManager->isOnceKeyDown('4'))
	{
		for (int i = 0; i < NUM_DATA; i++)
		{
			m_vecSortData.push_back(m_vecHeapData.GetData());
		}
	}


	if (g_pKeyManager->isOnceKeyDown(VK_ESCAPE))
	{
		g_pLoadManager->ChangeScene(SCENE_KIND::Title);
	}


}

void SortTest::Render()
{
	for (int i = 0; i < m_vecSortData.size(); i++)
	{
		g_pTextManager->IntRender(m_vecSortData[i], 10 + i * 120, HALFSIZEY, 50, NumberType::Gold);
		g_pTextManager->IntRender(m_vecData[i], 10 + i * 120, HALFSIZEY - 110, 50, NumberType::Blue);
	}
}

void SortTest::Release()
{
}
