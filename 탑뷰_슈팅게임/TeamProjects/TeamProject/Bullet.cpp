#include "stdafx.h"
#include "Bullet.h"

Bullet::Bullet()
{
	m_pTargetPos = NULL;
	Init();
}

Bullet::~Bullet()
{
}

void Bullet::Init()
{
	GameObject2D::Init();
	m_pTransform2D->SetScale(15,15);
	m_eType			= BulletType::DIRECT;
	m_vStartPos		= {0,0};
	m_vViaPos		= {0,0};
	m_vDestPos		= { 0,0 };
	m_vPrevPos		= {0,0};
	m_nDamage		= 1;
	m_vMoveDir		= {0,0};
	m_fMoveSpeed	= 600.0f;
	m_fTrackingTimer = 0.0f;
	m_isActive = false;
}

void Bullet::Update()
{
	if (m_isActive)
	{
		Move();

		if (m_isTracking)
			m_fTrackingTimer += g_pTimeManager->GetDeltaTime();
	}

	if (m_pTransform2D->GetPosition().x > MAPSIZEX ||
		m_pTransform2D->GetPosition().x < 0 ||
		m_pTransform2D->GetPosition().y > MAPSIZEY ||
		m_pTransform2D->GetPosition().y < 0)
		m_isActive = false;
	
}

void Bullet::SettingBullet(D3DXVECTOR2 start, D3DXVECTOR2 via, D3DXVECTOR2 dest, BulletType type, float angle,int dmg)
{
	m_vStartPos = start;
	m_pTransform2D->SetPosition(m_vStartPos);
	m_vPrevPos = m_pTransform2D->GetPosition();
	m_vViaPos = via;
	m_vDestPos = dest;
	m_eType = type;
	m_nDamage = dmg;
	m_isActive = true;
	m_pTransform2D->SetRotation(0,0,angle);
	m_fMoveSpeed = 1200.0f;
	m_vMoveDir = dest;
}

void Bullet::Move()
{

	m_vPrevPos = m_pTransform2D->GetPosition();

	switch (m_eType)
	{
	case BulletType::DIRECT:
		m_pTransform2D->Translate2D(m_vMoveDir.x * m_fMoveSpeed * g_pTimeManager->GetDeltaTime(), m_vMoveDir.y * m_fMoveSpeed * g_pTimeManager->GetDeltaTime());
		break;
	case BulletType::TRACKING:
		if (m_isTracking)
		{
			m_pTransform2D->SetPosition(BezierCurve(m_vStartPos, m_vViaPos, *m_pTargetPos, m_fTrackingTimer / TRACKING_DELAY));
			m_pTransform2D->SetRotation(0, 0, GetRadian(m_vPrevPos, m_pTransform2D->GetPosition()));
		}
		else
		{
			m_pTransform2D->Translate2D(m_vMoveDir.x * m_fMoveSpeed * g_pTimeManager->GetDeltaTime(), m_vMoveDir.y * m_fMoveSpeed * g_pTimeManager->GetDeltaTime());

		}
		
		break;
	}
}
