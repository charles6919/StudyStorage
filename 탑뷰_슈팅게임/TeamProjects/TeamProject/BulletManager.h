#pragma once
#include "SingletonBase.h"
#include "Bullet.h"

#define g_pBulletManager BulletManager::GetInstance()

struct stBullet
{
	Sprite* _pSprite;
	CircleCollider2D* _pHitCollider;
	CircleCollider2D* _pTrakingRange;
};

class BulletManager :
	public SingletonBase<BulletManager>
{
private:
	vector<Bullet*> m_vecBullet;
	stBullet* m_pBullet;

public:
	BulletManager();
	~BulletManager();

	void Init();
	void Update();
	void Render();
	void Release();

	void AddBullet(Bullet* p) { m_vecBullet.push_back(p); }
	void DeleteBullet(int index) 
	{
		m_vecBullet.erase(m_vecBullet.begin() + index);
	}

	Bullet* GetBullet(int index) { return m_vecBullet[index]; }
	int GetBulletVecIndex() { return m_vecBullet.size(); }

};

