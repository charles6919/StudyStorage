#pragma once
#include "GameObject2D.h"

#define ENEMY_DEFAULTSIZEX 75
#define ENEMY_DEFAULTSIZEY 75


enum class EnemyState
{
	READY = -1,
	Idle,
	Run,
	Dead
};

enum class EnemyType
{
	Normal,
	Elite,
	Boss
};

class Enemy :
	public GameObject2D
{
private:
	EnemyState	m_eState;
	EnemyType	m_eType;
	int			m_nCurrFrameIndex;
	
	int			m_nHp;
	int			m_nScore;

	D3DXVECTOR2 m_vTargetPos;
	float		m_fMoveSpeed;
	bool		m_isDead;
	float       m_fPatternTimer;
	float		m_fPatternDuration;
	bool		m_isTracking;

public:
	Enemy();
	~Enemy();

	virtual void Init();
	virtual void Update();

	void Move();
	void Rotate();
	void TakeDmg(int dmg) { m_nHp -= dmg; }

	void SetTarget(D3DXVECTOR2 pos) { m_vTargetPos = pos; }
	void SetCurrFrameIndex(int n) { m_nCurrFrameIndex = n; }
	void SetIsDead(bool b) { m_isDead = true; }
	void SetIsTracking(bool b) { m_isTracking = b; }
	void SetPatternTimer(float f) { m_fPatternTimer = f; }

	float GetPatternDuration() { return m_fPatternDuration; }
	D3DXVECTOR2 GetTargetPos() { return m_vTargetPos; }
	bool GetIsDead() { return m_isDead; }
	EnemyState GetState() { return m_eState; }
	int GetCurrFrameIndex() { return m_nCurrFrameIndex; }


	
};

