#pragma once
#include "Unit.h"
#include "Gun.h"

#define GUN_DISTANCE 24

enum class EnemyState{Idle, Run, Die};
enum class Enemy_AniState 
{
	READY,
	Idle_RB, Idle_T, Idle_LB,
	Run_RT, Run_RB, Run_LT, Run_LB,
	Die,
	Max
};

class Enemy :
	public Unit<Enemy_AniState>
{
private:
	EnemyState						m_eEState;
	CircleCollider					m_HitCollider;

	bool							m_isAttack;

	int								m_nMaxHp;			//ÃÖ´ëÃ¼·Â

	Gun*							m_pGun;
	Transform2D						m_transform2DGun;	//ÃÑÀÇ Æ®·£½ºÆû

	float							m_fElapsedShotTimer;
	float							m_fElapsedReloadTimer;

	float							m_fElapsedAttackTimer;
	float							m_fAttackCoolTime;

	bool							m_enableToMove;
	bool							m_isShooting;

	D3DXVECTOR2						m_vMoveDir;
	D3DXVECTOR2*					m_pTarget;
	tagTileInfo						m_stTileInfo[NUM_TILE_Y][NUM_TILE_X];

public:
	float							m_fDeadTime;
	float							m_fElapsedDeadTimer;

private:
	void AngleUpdate();
	void StateUpdate();

public:
	Enemy();
	~Enemy();

	virtual void Init();
	virtual void Update();
	virtual void Render();

	void Rotate();
	void Move();
	void Dead();										//Á×À½
	void Shot();										//»ç°Ý
	void Hit(int dmg);									//ÇÇ°Ý
	void KnockBack(float power, D3DXVECTOR2 dir);		//³Ë¹é

	void SetTileInfo(tagTileInfo tileInfo[NUM_TILE_Y][NUM_TILE_X]);
	void SetPositionHitCollider(D3DXVECTOR2 pos) { m_HitCollider.transform2D.position = pos; }
	void SetRotationHitCollider(D3DXVECTOR3 rot) { m_HitCollider.transform2D.rotation = rot; }
	void SetScaleHitCollider(D3DXVECTOR2 scale) { m_HitCollider.transform2D.scale = scale; }
	void SetPositionGun(D3DXVECTOR2 pos) { m_transform2DGun.position = pos; }
	void SetRotationGun(D3DXVECTOR3 rot) { m_transform2DGun.rotation = rot; }
	void SetScaleGun(D3DXVECTOR2 scale) { m_transform2DGun.scale = scale; }
	void SetTargetPos(D3DXVECTOR2* target) { m_pTarget = target; }

	D3DXVECTOR2* GetPosition() { return &m_transform2D.position; }
	CircleCollider GetHitCollider() { return m_HitCollider; }
	bool GetIsAttack() { return m_isAttack; }
	int GetMaxHp() { return m_nMaxHp; }
};

