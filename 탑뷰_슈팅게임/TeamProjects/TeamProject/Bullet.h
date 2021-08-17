#pragma once
#include "GameObject2D.h"

#define TRACKING_DELAY 0.5f


enum class BulletType
{
	DIRECT,
	TRACKING
};

class Bullet :
	public GameObject2D
{
private:
	BulletType		m_eType;
	D3DXVECTOR2		m_vStartPos;
	D3DXVECTOR2		m_vViaPos;
	D3DXVECTOR2		m_vDestPos;
	D3DXVECTOR2		m_vPrevPos;
	int				m_nDamage;
	D3DXVECTOR2		m_vMoveDir;
	D3DXVECTOR2*	m_pTargetPos;
	float			m_fMoveSpeed;
	float			m_fTrackingTimer;
	bool			m_isTracking;
	bool			m_isActive;

public:
	Bullet();
	~Bullet();

	void Init();
	void Update();

	void SetBulletType(BulletType type) { m_eType = type; }
	void SetStartPos(D3DXVECTOR2 pos) { m_vStartPos = pos; }
	void SetViaPos(D3DXVECTOR2 pos) { m_vViaPos = pos; }
	void SetDestPos(D3DXVECTOR2 pos) { m_vDestPos = pos; }
	void SetMoveDir(D3DXVECTOR2 dir) { m_vMoveDir = dir; }
	void SetDamage(int dmg) { m_nDamage = dmg; }
	void SetMoveSpeed(float speed) { m_fMoveSpeed = speed; }
	void SetIsActive(bool b) { m_isActive = b; }
	void SetIsTracking(bool b) { m_isTracking = b; }
	void SetTargetPos(D3DXVECTOR2* p) { m_pTargetPos = p; }
	void SettingBullet(D3DXVECTOR2 start, D3DXVECTOR2 via, D3DXVECTOR2 dest, BulletType type, float angle, int dmg);
	
	BulletType GetBulletType() { return m_eType; }
	D3DXVECTOR2 GetStartPos() { return m_vStartPos; }
	D3DXVECTOR2 GetViaPos() { return m_vViaPos; }
	D3DXVECTOR2 GetDestPos() { return m_vDestPos; }
	int GetDamage() { return m_nDamage; }
	D3DXVECTOR2 GetMoveDir() { return m_vMoveDir; }
	float GetMoveSpeed() { return m_fMoveSpeed; }
	bool GetIsActive() { return m_isActive; }
	bool GetIsTracking() { return m_isTracking; }
	D3DXVECTOR2* GetTargetPos() { return m_pTargetPos; }

	void Move();
};

