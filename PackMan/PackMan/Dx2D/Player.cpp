#include "stdafx.h"
#include "Player.h"
#include "Map.h"

Player::Player()
{
	Clip* clip = new Clip;
	for (int i = 0; i < 4; i++)
	{
		Sprite* sprite = new Sprite(L"Player",4, 1, i);
		clip->AddFrame(sprite, 1 / 20.0f);
	}
	m_pAnimation->AddClip(PLAYER_STATE::Move, clip);


	clip = new Clip;
	for (int i = 0; i < 11; i++)
	{
		Sprite* sprite = new Sprite(L"Player_Dead", 11, 1, i);
		clip->AddFrame(sprite, 1 / 11.0f);
	}
	m_pAnimation->AddClip(PLAYER_STATE::Dead, clip);
	
}

Player::~Player()
{

}

void Player::Init()
{
	Unit::Init();
	m_vScale = { 50, 50 };
	m_ptPosition = { GET_TILE_REALPOINT(1,1)};
	m_fMoveSpeed = 0.0f;
	m_fHitColliderRange = 14;
	m_fAggroRange = 200;
	m_isAttacking = false;
	m_fAttackDuration = 5.0f;
	m_vMoveDir = { 1,0 };
	m_eCharacterDir = CharacterDir::Right;
	m_nLife = 2;
	m_nScore = 0;
	m_fDeadDelay = 1.0f;
	m_fElapsedDeadTime = 0.0f;
	SettingPOINT();
}

void Player::StageInit()
{
	m_eState = PLAYER_STATE::Move;
	m_ptPosition = { GET_TILE_REALPOINT(1,1) };
	m_fMoveSpeed = 0.0f;
	m_isAttacking = false;
	m_isDead = false;
	SettingPOINT();
}

void Player::SetCurrentPt()
{
	m_ptCurr = GET_TILE_INDEXPOINT(m_ptPosition.x , m_ptPosition.y);
}

void Player::SetNextPt()
{
	switch (m_eCharacterDir)
	{
	case CharacterDir::Right:
		m_ptNext = { m_ptCurr.x + 1, m_ptCurr.y };
		break;
	case CharacterDir::Top:
		m_ptNext = { m_ptCurr.x , m_ptCurr.y + 1};
		break;
	case CharacterDir::Left:
		m_ptNext = { m_ptCurr.x - 1, m_ptCurr.y };
		break;
	case CharacterDir::Bottom:
		m_ptNext = { m_ptCurr.x , m_ptCurr.y - 1};
		break;
	}
}

void Player::SettingPOINT()
{
	SetCurrentPt();
	SetNextPt();
}

void Player::Keyboard()
{


	if (g_pKeyManager->isOnceKeyDown(VK_UP))
	{
		

		if (m_eCharacterDir == CharacterDir::Bottom)
			m_isTurnBack = true;
		m_vReservationDir = { 0,1 };
		m_fMoveSpeed = PLAYER_MOVESPEED;
	}
	else if (g_pKeyManager->isOnceKeyDown(VK_DOWN))
	{
		if (m_eCharacterDir == CharacterDir::Top)
			m_isTurnBack = true;
		m_vReservationDir = { 0,-1 };
		m_fMoveSpeed = PLAYER_MOVESPEED;
	}
	else if (g_pKeyManager->isOnceKeyDown(VK_RIGHT))
	{
		if (m_eCharacterDir == CharacterDir::Left)
			m_isTurnBack = true;
		m_vReservationDir = { 1,0 };
		m_fMoveSpeed = PLAYER_MOVESPEED;
	}
	else if (g_pKeyManager->isOnceKeyDown(VK_LEFT))
	{
		if (m_eCharacterDir == CharacterDir::Right)
			m_isTurnBack = true;
		m_vReservationDir = { -1,0 };
		m_fMoveSpeed = PLAYER_MOVESPEED;
	}
}

void Player::UpdateRotation()
{
	if (m_vReservationDir != m_vMoveDir && !m_isTurnBack)
	{
		tagTileInfo tile = m_pMap->GetTileInfo(m_ptCurr.x + (LONG)m_vReservationDir.x, m_ptCurr.y + (LONG)m_vReservationDir.y);
		if (tile.eTType != TERRAIN_TYPE::Unwalkable && tile.eOType == OBJECT_TYPE::None)
		{
			m_vMoveDir = m_vReservationDir;
		}

		if (m_vMoveDir.x == 0.0f)
		{
			if (m_vMoveDir.y > 0)
			{
				m_eCharacterDir = CharacterDir::Top;
				m_vRotation.z = D3DX_PI * 0.5f;
				SettingPOINT();
			}
			else
			{
				m_eCharacterDir = CharacterDir::Bottom;
				m_vRotation.z = D3DX_PI * 1.5f;
				SettingPOINT();
			}
		}
		else
		{
			if (m_vMoveDir.x > 0.0f)
			{
				m_eCharacterDir = CharacterDir::Right;
				m_vRotation.z = 0.0f;
				SettingPOINT();
			}
			else
			{
				m_eCharacterDir = CharacterDir::Left;
				m_vRotation.z = D3DX_PI * 1.0f;
				SettingPOINT();
			}
		}
		
	}
}

void Player::TurnBack()
{
	switch (m_eCharacterDir)
	{
	case CharacterDir::Right:
		m_eCharacterDir = CharacterDir::Left;
		m_vMoveDir = {-1,0};
		m_vRotation.z = D3DX_PI * 1.0f;
		break;
	case CharacterDir::Top:
		m_eCharacterDir = CharacterDir::Bottom;
		m_vMoveDir = { 0,-1 };
		m_vRotation.z = D3DX_PI * 1.5f;
		break;
	case CharacterDir::Left:
		m_eCharacterDir = CharacterDir::Right;
		m_vMoveDir = { 1,0 };
		m_vRotation.z = 0.0f;
		break;
	case CharacterDir::Bottom:
		m_eCharacterDir = CharacterDir::Top;
		m_vMoveDir = { 0,1 };
		m_vRotation.z = D3DX_PI * 0.5f;
		break;
	}
	m_isTurnBack = false;
	SettingPOINT();
}

void Player::Update()
{
	if (m_isDead)
	{
		m_vRotation.z = 0.0f;
		m_eState = PLAYER_STATE::Dead;

		if (m_fElapsedDeadTime >= m_fDeadDelay)
		{
			m_fElapsedDeadTime = 0.0f;
			StageInit();
		}
		else
		{
			m_fElapsedDeadTime += g_pTimeManager->GetDeltaTime();
		}

	}
	else
	{
		Keyboard();

		POINT pt = GET_TILE_REALPOINT(m_ptCurr.x, m_ptCurr.y);
		if (m_ptPosition.x == pt.x && m_ptPosition.y == pt.y)//플레이어가 현재 타일의 중점에 왔을때만 회전 가능하도록
		{
			m_enableToRotate = true;
		}
		else
			m_enableToRotate = false;

		if (m_enableToRotate)
			UpdateRotation();

		if (m_isTurnBack)
			TurnBack();

		Move();
	}

		Unit::Update();

		if (m_nLife <= 0)
			m_isGameOver = true;

		if (m_isAttacking)
		{
			if (m_fElapsedTime >= m_fAttackDuration)
			{
				m_isAttacking = false;
				m_fElapsedTime = 0.0f;
			}
			else
			{
				m_fElapsedTime += g_pTimeManager->GetDeltaTime();
			}

		}
	

	static float pos[2];
	pos[0] = m_ptPosition.x;
	pos[1] = m_ptPosition.y;

	ImGui::InputFloat2("PlayerPos", pos);

	ImGui::Checkbox("Attacking", &m_isAttacking);

	m_pHitCollider->SetPosition(m_ptPosition.x, m_ptPosition.y);
	m_pHitCollider->SetRadius(m_fHitColliderRange);
	m_pHitCollider->SetDraw(false);
	m_pHitCollider->SetBorder(true);
	m_pHitCollider->Update();

	m_pAggroCollider->SetPosition(m_ptPosition.x, m_ptPosition.y);
	m_pAggroCollider->SetRadius(m_fAggroRange);
	m_pAggroCollider->SetDraw(false);
	m_pAggroCollider->SetBorder(true);
	m_pAggroCollider->Update();
}

void Player::Render()
{
	Unit::Render();

	m_pHitCollider->Render();
	m_pAggroCollider->Render();
}

bool Player::CheckEnableMove()
{
	tagTileInfo tile = m_pMap->GetTileInfo(m_ptCurr.x + (LONG)m_vMoveDir.x, m_ptCurr.y + (LONG)m_vMoveDir.y);
	if (tile.eTType == TERRAIN_TYPE::Unwalkable || tile.eOType != OBJECT_TYPE::None)
	{
		return false;
	}
	else
		return true;
}

void Player::Move()
{
	if (CheckEnableMove())
	{
		float moveAmountX = m_vMoveDir.x * m_fMoveSpeed * g_pTimeManager->GetDeltaTime();
		float moveAmountY = m_vMoveDir.y * m_fMoveSpeed * g_pTimeManager->GetDeltaTime();
		POINT nextPt = GET_TILE_REALPOINT(m_ptNext.x, m_ptNext.y);
		float dist = D3DXVec2Length(&(D3DXVECTOR2(nextPt.x , nextPt.y) - D3DXVECTOR2(m_ptPosition.x, m_ptPosition.y)));
		if ( dist > fabs(moveAmountX) + fabs(moveAmountY))
		{
			m_ptPosition.x += moveAmountX;
			m_ptPosition.y += moveAmountY;
		}
		else
		{
			m_ptPosition = GET_TILE_REALPOINT(m_ptNext.x , m_ptNext.y);
			SettingPOINT();
		}
	}
}

void Player::Dead()
{
	m_isDead = true;
	m_nLife--;
}
	

