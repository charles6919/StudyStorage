#pragma once
#include "SingletonBase.h"
#include "Bullet.h"
#define g_pBulletManager BulletManager::GetInstance()
class BulletManager
	: public SingletonBase<BulletManager>
{
private:
	vector<Bullet*> m_vecBullet;
	CircleCollider m_circleCollider;
	Animation<BulletAniState>* m_pAnimation;

	void UpdateRender();

public:
	void Init();
	void Update();
	void Render();
	void Release();

	vector<Bullet*>& GetBulletVector() { return m_vecBullet; }
	CircleCollider GetCircleCollider() { return m_circleCollider; }
};

