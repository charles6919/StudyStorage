#pragma once
struct Hanoi_Tower
{
	Stack<int>* Tower;
	string Name;
};

class Hanoi
{
public:
	Hanoi_Tower m_stTower[3];
	int m_nCount;

public:
	Hanoi(int num);
	~Hanoi();

	void Move(int num, Hanoi_Tower start, Hanoi_Tower via, Hanoi_Tower dest);
};

