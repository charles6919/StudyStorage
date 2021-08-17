#include "stdafx.h"
#include "Hanoi.h"

Hanoi::Hanoi(int num)
{
	m_stTower[0].Name = "1번 타워";
	m_stTower[1].Name = "2번 타워";
	m_stTower[2].Name = "3번 타워";

	m_stTower[0].Tower = new Stack<int>;
	m_stTower[1].Tower = new Stack<int>;
	m_stTower[2].Tower = new Stack<int>;

	for (int i = 0; i < num; i++)
	{
		m_stTower[0].Tower->Push(num - i);
	}

	m_nCount = 0;
}

Hanoi::~Hanoi()
{
	for (int i = 0; i < 3; i++)
	{
		delete m_stTower[i].Tower;
	}
}

void Hanoi::Move(int num, Hanoi_Tower start, Hanoi_Tower via, Hanoi_Tower dest)
{
	if (num == 1)
	{
		int temp = start.Tower->Pop();
		dest.Tower->Push(temp);
		m_nCount++;
		cout << temp << " : " << start.Name << " -> " << dest.Name << " , 옮긴 횟수 : " << m_nCount << endl;
	}
	else
	{
		Move(num - 1, start, dest, via);
		Move(1, start, via, dest);
		Move(num - 1, via, start, dest);
	}
}



