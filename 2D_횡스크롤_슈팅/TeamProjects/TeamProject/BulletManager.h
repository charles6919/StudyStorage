#pragma once
#include "SingletonBase.h"
#include "Bullet.h"

#define g_pBulletManager BulletManager::GetInstance()

class Player;
class Boss;

class BulletManager :
	public SingletonBase<BulletManager>
{
private:
	struct stBullet
	{
		Sprite*				_pSprite;
	};

	stBullet* m_stBullet[(int)Bullet_Type::Max];
	vector<Bullet*> m_vecPlayerBullet;
	vector<Bullet*> m_vecEnemyBullet;

	Player* m_pPlayer;
	Boss* m_pBoss;


public:
	BulletManager();
	~BulletManager();

	void Init();
	void Update();
	void Render();

	void SetPlayer(Player* p) { m_pPlayer = p; }
	void SetBoss(Boss* p) { m_pBoss = p; }
	
	void AddPlayerBullet(Bullet* p) { m_vecPlayerBullet.push_back(p); }
	void AddEnemyBullet(Bullet* p) { m_vecEnemyBullet.push_back(p); }
};

