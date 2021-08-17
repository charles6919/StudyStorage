#include "stdafx.h"
#include "Bullet.h"

void Bullet::Init()
{
	m_vMoveDir		= {1, 0};
	m_eBulletType	= Bullet_Type::Player_Normal;
	m_nDamage		= 1;
	m_fMoveSpeed	= 300.0f;

	m_vTarget	= {0,0};
	m_vVia		= {0,0};
	m_fTime		= 0.0f;
	m_fElapsedTime = 0.0f;

}

void Bullet::Update()
{

}

void Bullet::Render()
{

}

