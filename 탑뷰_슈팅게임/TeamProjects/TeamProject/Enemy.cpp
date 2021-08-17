#include "stdafx.h"
#include "Enemy.h"

Enemy::Enemy()
{
	Init();
}

Enemy::~Enemy()
{
}

void Enemy::Init()
{
	GameObject2D::Init();
	m_pTransform2D->SetScale(ENEMY_DEFAULTSIZEX, ENEMY_DEFAULTSIZEY);
	m_pTransform2D->SetPosition(OBJECT_DEFAULTV);

	m_eState			= EnemyState::Idle;
	m_eType				= EnemyType::Normal;
	m_nCurrFrameIndex	= 0;

	m_nHp				= 10;
	m_nScore			= 10;

	m_vTargetPos		= {0,0};
	m_fMoveSpeed		= 150.0f;

	m_fPatternTimer		= 0.0f;
	m_fPatternDuration	= 5.0f;

	m_isTracking		= false;
	m_isDead			= false;
}

void Enemy::Update()
{
	if (m_nHp <= 0)
	{
		this->Init();
		m_isDead = true;
		m_eState = EnemyState::Dead;
	}

	if (m_isDead == false)
	{
		if (!m_isTracking)
		{
			if (m_fPatternTimer >= m_fPatternDuration)
			{
				m_vTargetPos.x = rand() % MAPSIZEX;
				m_vTargetPos.y = rand() % MAPSIZEY;
				m_fPatternTimer = 0.0f;
			}
			else
			{
				m_fPatternTimer += g_pTimeManager->GetDeltaTime();
			}
		}
		else
		{
			
		}
		Rotate();
		Move();

	}

}

void Enemy::Move()
{
	D3DXVECTOR2 moveDir;
	moveDir.x = cosf(m_pTransform2D->GetRotation().z);
	moveDir.y = sinf(m_pTransform2D->GetRotation().z);
	m_pTransform2D->Translate2D(moveDir.x * m_fMoveSpeed * g_pTimeManager->GetDeltaTime(), 
		moveDir.y * m_fMoveSpeed * g_pTimeManager->GetDeltaTime());
}

void Enemy::Rotate()
{
	m_pTransform2D->SetRotation(0, 0, GetRadian(m_pTransform2D->GetPosition(), m_vTargetPos));
}
