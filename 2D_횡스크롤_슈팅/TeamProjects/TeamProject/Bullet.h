#pragma once
#include "GameObject2D.h"

enum class Bullet_Type
{
	Player_Normal,
	Enemy_Normal,
	Enemy_Curve,
	Max
};

class Bullet :
	public GameObject2D
{
private:
	D3DXVECTOR2 m_vMoveDir;
	D3DXVECTOR2 m_vStart;
	D3DXVECTOR2 m_vVia;
	D3DXVECTOR2 m_vTarget;
	Bullet_Type m_eBulletType;
	int			m_nDamage;
	float		m_fMoveSpeed;
	float		m_fTime;
	float		m_fElapsedTime;

public:
	virtual void Init();
	virtual void Update();
	virtual void Render();

	void SetDamage(int dmg) { m_nDamage = dmg; }
	int GetDamage() { return m_nDamage; }

	void SetMoveDir(D3DXVECTOR2 v) { m_vMoveDir = v; }
	void SetMoveDir(float x, float y) { SetMoveDir(D3DXVECTOR2(x,y)); }
	D3DXVECTOR2 GetMoveDir() { return m_vMoveDir; }

	void SetBulletType(Bullet_Type type) { m_eBulletType = type; }
	Bullet_Type GetBulletType() { return m_eBulletType; }

	void SetMoveSpeed(float f) { m_fMoveSpeed = f;}
	float GetMoveSpeed() { return m_fMoveSpeed; }

	void SetStart(D3DXVECTOR2 v) { m_vStart = v; }
	D3DXVECTOR2 GetStart() { return m_vStart; }

	void SetTarget(D3DXVECTOR2 v) { m_vTarget = v;}
	D3DXVECTOR2 GetTarget() { return m_vTarget; }

	void SetVia(D3DXVECTOR2 v) { m_vVia = v; }
	D3DXVECTOR2 GetVia() { return m_vVia; }

	void SetTime(float f) { m_fTime = f; }
	float GetTime() { return m_fTime; }

	void SetElapsedTime(float f) { m_fElapsedTime = f; }
	float GetElapsedTime() { return m_fElapsedTime; }
	
};

