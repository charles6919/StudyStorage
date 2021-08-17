#include "pch.h"
#include "Bullet.h"


Bullet::Bullet()
{

}

Bullet::~Bullet()
{

}

void Bullet::Init()
{
	m_stInfo.state = BulletState::Idle;
	m_stInfo.type = BulletType::Player;
	m_stInfo.shape = BulletShape::Default;
	m_stInfo.moveDir = { 0,0 };
	m_stInfo.moveSpeed = 200.0f;
	m_stInfo.currFrame = 0;
	m_stInfo.damage = 5;
	m_stInfo.ElapsedTime = 0.0f;

}

void Bullet::Update()
{
	Move();

	switch (m_stInfo.shape)
	{
		case BulletShape::Default:
		{
			if (m_stInfo.state == BulletState::Idle)
			{
				m_eAniState = BulletAniState::Default_Idle;
			}
			else
			{
				m_eAniState = BulletAniState::Default_Destroy;
			}
			break;
		}
		case BulletShape::Sword:
		{
			if (m_stInfo.state == BulletState::Idle)
			{
				m_eAniState = BulletAniState::Sword_Idle;
			}
			else
			{
				m_eAniState = BulletAniState::Sword_Destroy;
			}
			break;
		}
	}
}

void Bullet::Move()
{
	m_stInfo.transform.position.x += m_stInfo.moveDir.x * m_stInfo.moveSpeed * g_pTimeManager->GetDeltaTime();
	m_stInfo.transform.position.y += m_stInfo.moveDir.y * m_stInfo.moveSpeed * g_pTimeManager->GetDeltaTime();
}

void Bullet::UpdateAniState()
{
	switch (m_stInfo.shape)
	{
	case BulletShape::Default:
		if (m_stInfo.state == BulletState::Idle)
			m_eAniState = BulletAniState::Default_Idle;
		else if (m_stInfo.state == BulletState::Destroy)
			m_eAniState = BulletAniState::Default_Destroy;
		break;
	case BulletShape::Sword:
		if (m_stInfo.state == BulletState::Idle)
			m_eAniState = BulletAniState::Sword_Idle;
		else if (m_stInfo.state == BulletState::Destroy)
			m_eAniState = BulletAniState::Sword_Destroy;
		break;
	}
}


