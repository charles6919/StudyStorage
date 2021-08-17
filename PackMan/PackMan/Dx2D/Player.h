#pragma once
#include "Unit.h"

#define PLAYER_MOVESPEED 300.0f

class Map;

enum class PLAYER_STATE
{
	READY = -1,
	Move,
	Dead,
	MAX
};

class Player : public Unit<PLAYER_STATE>
{
private:
	D3DXVECTOR2 m_vMoveDir;
	D3DXVECTOR2 m_vReservationDir;

	POINT		m_ptCurr;
	POINT		m_ptNext;

	bool m_enableToRotate;
	bool m_isTurnBack;


	Circle* m_pHitCollider;
	float m_fHitColliderRange;

	Circle* m_pAggroCollider;
	float m_fAggroRange;

	Map* m_pMap;

	int m_nLife;
	int m_nScore;

	bool m_isAttacking;
	float m_fAttackDuration;
	float m_fElapsedTime;

	bool m_isDead;
	float m_fElapsedDeadTime;
	float m_fDeadDelay;

	bool m_isGameOver;


private:
	void SetCurrentPt();
	void SetNextPt();
	void SettingPOINT();

	void Keyboard();
	bool CheckEnableMove();
	void UpdateRotation();
	void TurnBack();

	

public:
	Player();
	~Player();

	void Init() override;
	void Update() override;
	void Render() override;

	void SetMap(Map* p) { m_pMap = p; }
	void SetHitCollider(Circle* p) { m_pHitCollider = p; }
	void SetAggroCollider(Circle* p) { m_pAggroCollider = p; }
	void SetIsAttacking(bool b) { m_isAttacking = b; }
	void SetElapsedTime(float f) { m_fElapsedTime = f; }
	void DecreaseLife() { m_nLife--; }
	void IncreaseLife() { m_nLife++; }
	void TakeScore(int score) { m_nScore += score; }

	void StageInit();

	Circle* GetHitCollider() { return m_pHitCollider; }
	Circle* GetAggroCollider() { return m_pAggroCollider; }
	bool GetGameOver() { return m_isGameOver; }
	bool GetIsDead() { return m_isDead; }
	bool GetIsAttacking() { return m_isAttacking; }

	void Move();
	void Dead();
};

