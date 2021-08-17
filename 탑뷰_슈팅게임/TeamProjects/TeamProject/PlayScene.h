#pragma once
#include "iGameNode.h"
#include "Player.h"
#include "Enemy.h"
#include "Map.h"
#include "Item.h"

struct stEnemy
{
	Animation<EnemyState>* _pAni;
	CircleCollider2D* _pHitCollider;
};

class PlayScene : public iGameNode
{
private:
	Player* m_pPlayer;
	Map* m_pMap;
	vector<Enemy*> m_vecEnemy;
	vector<Item*> m_vecItem;
	stEnemy* m_pNormalEnemy;

	float m_fRespawnSpeed;
	float m_fElapsedTimer;

	float m_fRespawnItemSpeed;
	float m_fElapsedItemTimer;
	


public:
	virtual void Init()		override;
	virtual void Update()	override;
	virtual void Render()	override;
	virtual void Release()	override;

	void Collision();
	void Respawn();
	void RespawnItem();
};

