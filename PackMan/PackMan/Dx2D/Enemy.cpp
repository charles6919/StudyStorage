#include "stdafx.h"
#include "Enemy.h"
#include "Player.h"
#include "Map.h"


void Enemy::SetMoveDir()
{
	if (m_ptCurr.x - m_ptNext.x == 0)
	{
		m_vMoveDir.x = 0;
	}
	else if (m_ptCurr.x - m_ptNext.x > 0)
	{
		m_vMoveDir.x = -1;
	}
	else if (m_ptCurr.x - m_ptNext.x < 0)
	{
		m_vMoveDir.x = 1;
	}

	if (m_ptCurr.y - m_ptNext.y == 0)
	{
		m_vMoveDir.y = 0;
	}
	else if (m_ptCurr.y - m_ptNext.y > 0)
	{
		m_vMoveDir.y = -1;
	}
	else if (m_ptCurr.y - m_ptNext.y < 0)
	{
		m_vMoveDir.y = 1;
	}
}

Enemy::Enemy()
{
	Clip* clip = new Clip;
	for (int i = 0; i < 2; i++)
	{
		Sprite* sprite = new Sprite(L"Enemy_Red_Move", 2, 4, i);
		clip->AddFrame(sprite, 1 / 10.0f);
	}
	m_pAnimation->AddClip(ENEMY_STATE::Move, clip);

	//Move
	clip = new Clip;
	for (int i = 0; i < 2; i++)
	{
		Sprite* sprite = new Sprite(L"Enemy_Red_Move", 2, 4, i);
		clip->AddFrame(sprite, 1 / 10.0f);
	}
	m_pAnimation->AddClip(ENEMY_STATE::Move_R, clip);

	clip = new Clip;
	for (int i = 0; i < 2; i++)
	{
		Sprite* sprite = new Sprite(L"Enemy_Red_Move", 2, 4, i + 2 * 1);
		clip->AddFrame(sprite, 1 / 10.0f);
	}
	m_pAnimation->AddClip(ENEMY_STATE::Move_T, clip);

	clip = new Clip;
	for (int i = 0; i < 2; i++)
	{
		Sprite* sprite = new Sprite(L"Enemy_Red_Move", 2, 4, i + 2 * 2);
		clip->AddFrame(sprite, 1 / 10.0f);
	}
	m_pAnimation->AddClip(ENEMY_STATE::Move_L, clip);

	clip = new Clip;
	for (int i = 0; i < 2; i++)
	{
		Sprite* sprite = new Sprite(L"Enemy_Red_Move", 2, 4, i + 2 * 3);
		clip->AddFrame(sprite, 1 / 10.0f);
	}
	m_pAnimation->AddClip(ENEMY_STATE::Move_B, clip);

	//Jailed
	clip = new Clip;
	for (int i = 0; i < 1; i++)
	{
		Sprite* sprite = new Sprite(L"Enemy_Jailed", 4, 1, i);
		clip->AddFrame(sprite, 1 / 10.0f);
	}
	m_pAnimation->AddClip(ENEMY_STATE::Jailed_T, clip);

	clip = new Clip;
	for (int i = 0; i < 1; i++)
	{
		Sprite* sprite = new Sprite(L"Enemy_Jailed", 4, 1, i + 1);
		clip->AddFrame(sprite, 1 / 10.0f);
	}
	m_pAnimation->AddClip(ENEMY_STATE::Jailed_B, clip);

	clip = new Clip;
	for (int i = 0; i < 1; i++)
	{
		Sprite* sprite = new Sprite(L"Enemy_Jailed", 4, 1, i + 2);
		clip->AddFrame(sprite, 1 / 10.0f);
	}
	m_pAnimation->AddClip(ENEMY_STATE::Jailed_L, clip);

	clip = new Clip;
	for (int i = 0; i < 1; i++)
	{
		Sprite* sprite = new Sprite(L"Enemy_Jailed", 4, 1, i + 3);
		clip->AddFrame(sprite, 1 / 10.0f);
	}
	m_pAnimation->AddClip(ENEMY_STATE::Jailed_R, clip);

	//Scared
	clip = new Clip;
	for (int i = 0; i < 4; i++)
	{
		Sprite* sprite = new Sprite(L"Enemy_Scared", 4, 1, i);
		clip->AddFrame(sprite, 1 / 10.0f);
	}
	m_pAnimation->AddClip(ENEMY_STATE::Scared, clip);

	Circle* c = new Circle;
	m_pHitCollider = c;
}


Enemy::~Enemy()
{
	SAFE_DELETE(m_pHitCollider);
	SAFE_DELETE(m_pAnimation);
}

void Enemy::Init()
{
	Unit::Init();
	m_ptPosition = { (LONG)((NUM_TILE_X /2) * TILE_SIZE + TILE_SIZE*0.5f), (LONG)((NUM_TILE_Y / 2) * TILE_SIZE + TILE_SIZE * 0.5f) };
	m_vScale = { 35, 35 };
	m_fHitRange = 14;
	m_fChangeDestDelay = 5.0f;
	m_fElapsedTime = 0.0f;
	m_ptCurr = GET_TILE_INDEXPOINT(m_ptPosition.x, m_ptPosition.y);
	SetNextPt();
}

void Enemy::StageInit()
{
	m_vecRoute.clear();
	m_ptPosition = { (LONG)((NUM_TILE_X / 2) * TILE_SIZE + TILE_SIZE * 0.5f), (LONG)((NUM_TILE_Y / 2) * TILE_SIZE + TILE_SIZE * 0.5f) };
	m_isJailed = false;
	m_isTrackingPlayer = false;
	m_fElapsedTime = 0.0f;
	m_ptCurr = GET_TILE_INDEXPOINT(m_ptPosition.x, m_ptPosition.y);
	SetNextPt();
}

void Enemy::Update()
{
	if(m_pPlayer->GetIsDead() == false)
	{
		if (m_pPlayer->GetIsAttacking())
		{

			if (m_isJailed)
			{
				if (m_vMoveDir.x > 0)
					m_eState = ENEMY_STATE::Jailed_R;
				else if (m_vMoveDir.x < 0)
					m_eState = ENEMY_STATE::Jailed_L;
				if (m_vMoveDir.y > 0)
					m_eState = ENEMY_STATE::Jailed_T;
				else if (m_vMoveDir.y < 0)
					m_eState = ENEMY_STATE::Jailed_B;

				m_fMoveSpeed = 600.0f;
			}
			else
			{
				m_eState = ENEMY_STATE::Scared;
				m_fMoveSpeed = m_pPlayer->GetMoveSpeed() * 0.5f;
			}
		}
		else
		{
			if (m_isJailed)
				m_fMoveSpeed = 600.0f;
			else
				m_fMoveSpeed = m_pPlayer->GetMoveSpeed();

			if (m_vMoveDir.x > 0)
			{
				if (m_isJailed)
					m_eState = ENEMY_STATE::Jailed_R;
				else
					m_eState = ENEMY_STATE::Move_R;
			}
			else if (m_vMoveDir.x < 0)
			{

				if (m_isJailed)
					m_eState = ENEMY_STATE::Jailed_L;
				else
					m_eState = ENEMY_STATE::Move_L;
			}

			if (m_vMoveDir.y > 0)
			{

				if (m_isJailed)
					m_eState = ENEMY_STATE::Jailed_T;
				else
					m_eState = ENEMY_STATE::Move_T;
			}
			else if (m_vMoveDir.y < 0)
			{

				if (m_isJailed)
					m_eState = ENEMY_STATE::Jailed_B;
				else
					m_eState = ENEMY_STATE::Move_B;
			}
		}

		if (m_fElapsedTime >= m_fChangeDestDelay)
		{
			m_enableChangeDest = true;
			m_fElapsedTime = 0.0f;
		}

		Move();
	}
	Unit::Update();

	m_pHitCollider->SetPosition(m_ptPosition.x, m_ptPosition.y);
	m_pHitCollider->SetRadius(m_fHitRange);
	m_pHitCollider->SetDraw(false);
	m_pHitCollider->SetBorder(true);
	m_pHitCollider->Update();
}

void Enemy::Render()
{
	if (m_pPlayer->GetIsDead() == false)
	{
		Unit::Render();
		m_pHitCollider->Render();
	}
}



void Enemy::Move()
{

	float moveAmountX = m_vMoveDir.x * m_fMoveSpeed * g_pTimeManager->GetDeltaTime();
	float moveAmountY = m_vMoveDir.y * m_fMoveSpeed * g_pTimeManager->GetDeltaTime();
	POINT nextPt = GET_TILE_REALPOINT(m_ptNext.x, m_ptNext.y);
	float dist = D3DXVec2Length(&(D3DXVECTOR2(nextPt.x, nextPt.y) - D3DXVECTOR2(m_ptPosition.x, m_ptPosition.y)));
	if (dist > fabs(moveAmountX) + fabs(moveAmountY))
	{
		m_ptPosition.x += moveAmountX;
		m_ptPosition.y += moveAmountY;
	}
	else
	{
		m_ptPosition = GET_TILE_REALPOINT(m_ptNext.x, m_ptNext.y);
		m_ptCurr = GET_TILE_INDEXPOINT(m_ptPosition.x, m_ptPosition.y);
		if (m_enableChangeDest)
		{
			if (m_isTrackingPlayer)
			{
				if (m_pPlayer->GetIsAttacking())
				{
					POINT pt = m_pMap->GetVectorRoute()[rand() % m_pMap->GetVectorRoute().size()];
					SetRoute(pt);
				}
				else
				{
					POINT pt;
					pt = GET_TILE_INDEXPOINT(m_pPlayer->GetPosition()->x, m_pPlayer->GetPosition()->y);
					SetRoute(pt);
				}
			}
			else
			{
				POINT pt = m_pMap->GetVectorRoute()[rand() % m_pMap->GetVectorRoute().size()];
				SetRoute(pt);
			}
		}
		else
			SetNextPt();
	}
	
}

void Enemy::SetNextPt()
{
	if (m_vecRoute.size() <= 0)
	{
		if (m_isTrackingPlayer)
		{
			if (m_pPlayer->GetIsAttacking())
			{
				POINT pt = m_pMap->GetVectorRoute()[rand() % m_pMap->GetVectorRoute().size()];
				SetRoute(pt);
			}
			else
			{
				POINT pt;
				pt = GET_TILE_INDEXPOINT(m_pPlayer->GetPosition()->x, m_pPlayer->GetPosition()->y);
				SetRoute(pt);
			}
		}
		else
		{
			POINT pt = m_pMap->GetVectorRoute()[rand() % m_pMap->GetVectorRoute().size()];
			SetRoute(pt);
		}
	}
	else
	{
		m_ptNext = m_vecRoute.back();
		m_vecRoute.pop_back();
	}

	SetMoveDir();
}

void Enemy::SetRoute(POINT dest)
{
	if (m_isJailed)
	{
		m_enableChangeDest = false;
		m_ptCurr = GET_TILE_INDEXPOINT(m_ptPosition.x, m_ptPosition.y);
		m_ptDest = {(LONG)(NUM_TILE_X * 0.5f), (LONG)(NUM_TILE_Y * 0.5f)};
		m_pDijkstra->StartFindARoute(m_ptCurr, m_ptDest, m_vecRoute);
		SetNextPt();
	}
	else
	{
		m_enableChangeDest = false;
		m_ptCurr = GET_TILE_INDEXPOINT(m_ptPosition.x, m_ptPosition.y);
		m_ptDest = dest;
		m_pDijkstra->StartFindARoute(m_ptCurr, m_ptDest, m_vecRoute);
		SetNextPt();
	}
}
