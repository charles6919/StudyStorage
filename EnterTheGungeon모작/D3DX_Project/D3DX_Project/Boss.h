#pragma once
#include "Unit.h"
#define FLOAT_SPEED 25.0f
enum class BossState { READY, Idle, Dead};
enum class BossChairState {READY, Idle, Destroy, Spin};
enum class Pattern {Tracking ,Shot_1, Shot_2, Shot_3, Max};

class Boss :
	public Unit<BossState>
{
private:
	Animation<BossChairState>*		m_pChairAnimation;
	BossChairState					m_eChairState;
	CircleCollider					m_hitCollider;
	Pattern							m_eCurrPattern;

	D3DXVECTOR2*					m_pTarget;
	D3DXVECTOR2						m_vMoveDir;

	float							m_fElapsedPatternTimer;
	float							m_fPatternDuration;

	float							m_fElapsedShotTimer;
	float							m_fShotTime;

	int								m_nCountShot;	//¼¦ È½¼ö
	int								m_nSettingCount;//¼¼ÆÃµÈ ¼¦ È½¼ö

	float							m_fFloatingTimer;
	float							m_fFloatDirY;

	int								m_nMaxHp;
	bool							m_isSpining;

private:
	void ChangePattern();

public:
	Boss();
	~Boss();

	virtual void Init();
	virtual void Update();
	virtual void Render();

	void Move();										//ÀÌµ¿
	void UpdatePattern();
	void Shot(Bullet* bullet);
	void SetTargetPos(D3DXVECTOR2* pos);
	void Floating();

	D3DXVECTOR2* GetPosition() { return &m_transform2D.position; }
	CircleCollider GetHitCollider() { return m_hitCollider; }
	int GetCurrHp() { return m_nHp; }
	int GetMaxHp() { return m_nMaxHp; }

	void TakeDamage(int dmg) { m_nHp -= dmg; }




};

