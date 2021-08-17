#pragma once
#include "iGameNode.h"
#include "Map.h"
#include "Player.h"
#include "Item.h"
#include "Enemy.h"
#include "PlayDijkstra.h"

#define DEFAULT_NUM_ENEMY 4

class PlayScene : public iGameNode
{
private:
	Map*				m_pMap;
	vector<Item*>		m_vecScoreItems;
	vector<Item*>		m_vecAttackItems;
	Player*				m_pPlayer;
	vector<Enemy*>		m_vecEnemy;
	PlayDijkstra*		m_pDijkstra;

	bool m_isClear;

	int		m_nlevel;
	float	m_fRespawnSpeed;
	float	m_fRespawnTimer;
	int		m_numEnemyJailed;

public:
	PlayScene() {};
	~PlayScene() {};

	virtual void Init() override;
	virtual void Update() override;
	virtual void Render() override;
	virtual void Release() override;

	void StageInit();

	void Collision();
};

