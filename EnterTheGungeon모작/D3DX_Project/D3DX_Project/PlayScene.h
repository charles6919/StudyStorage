#pragma once
#include "iGameNode.h"
#include "Player.h"
#include "Boss.h"
#include "Enemy.h"
#include "Interface.h"

struct SummonInfo
{
	D3DXVECTOR2 position;
	float m_fElapsedTime;
};

class PlayScene :
	public iGameNode
{

private:
	tagTileInfo m_stTile[NUM_TILE_Y][NUM_TILE_X];
	vector<POINT> m_vecWalkableTile;
	vector<Sprite*> m_vecTerrain;
	vector<Sprite*> m_vecWall;
	vector<Sprite*> m_vecCeiling;

	Player* m_pPlayer;
	Boss* m_pBoss;
	vector<Enemy*> m_vecEnemy;
	D3DXVECTOR2 m_vCameraTarget;

	ProgressBar* m_pBossHpProgressBar;
	
	Interface* m_pInterface;

	int			m_nWave;
	float		m_fElapsedSummonTimer;
	float		m_fSummonDelay;
	int			m_nSummon;
	int			m_nRemainWave;

	vector<SummonInfo> m_vecSummonInfo;

	float m_fElapsedWaveTimer;
	float m_fWaveDuration;

	float m_fElapsedBossDeadTimer;
	float m_fBossDeadDuration;

	float m_fElapsedBossDeadExplosionTimer;
	float m_fBossDeadExplosionSpeed;

private:
	void UpdateTargetPos();	//카메라의 포지션값 계산
	void CollisionUpdate();		//충돌 업데이트

public:
	PlayScene();
	~PlayScene();

	virtual void Init();
	virtual void Update();
	virtual void Render();
	virtual void Release();
	
	void Summon_Effect(POINT pt);
	void Summon_Boss();
	void Wave_Update();

};

