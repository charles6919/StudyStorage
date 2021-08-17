#pragma once
#include "GameObject2D.h"
class Character :
	public GameObject2D
{
protected:
	int				m_nHp;
	bool			m_isDead;
	CharacterDir	m_eDir;			//애니메이션을 설정 하기 위한 방향

	float			m_fMoveSpeed;
	D3DXVECTOR2		m_vDir;			//이동, 점프할 방향의 D3DXVECTOR2

public:
	Character();
	~Character();

	virtual void Init()		override;
	virtual void Update()	override;
	virtual void Render()	override;

	int GetHp() { return m_nHp; }
	void SetHp(int hp) { m_nHp = hp; }

	bool GetIsDead() { return m_isDead; }
	void SetIsDead(bool b) { m_isDead = b; }

	CharacterDir GetCharacterDir() { return m_eDir; }
	void SetCharacterDir(CharacterDir dir) { m_eDir = dir; }

	float GetMoveSpeed() { return m_fMoveSpeed; }
	void SetMoveSpeed(float f) { m_fMoveSpeed = f; }

	void StaticDir();

	void Move();
	void TakeDmg(int dmg) { m_nHp -= dmg; }
};

