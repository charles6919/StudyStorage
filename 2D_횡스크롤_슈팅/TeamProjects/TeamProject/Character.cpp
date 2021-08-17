#include "stdafx.h"
#include "Character.h"

Character::Character()
{
}

Character::~Character()
{

}

void Character::Init()
{
	GameObject2D::Init();

	m_nHp			= 1.0f;
	m_isDead		= false;
	m_eDir			= CharacterDir::RIGHT;

	m_fMoveSpeed	= 100.0f;
	m_vDir			= {1, 0};

}

void Character::Update()
{
	StaticDir();
	GameObject2D::Update();
}

void Character::Render()
{
	GameObject2D::Render();
}

void Character::StaticDir()
{
	switch (m_eDir)
	{
	case CharacterDir::RIGHT:
		m_vDir = { 1 , 0 };
		break;
	case CharacterDir::RIGHT_TOP:
		m_vDir = { 1 , 1 };
		break;
	case CharacterDir::TOP:
		m_vDir = { 0 , 1 };
		break;
	case CharacterDir::LEFT_TOP:
		m_vDir = { -1 , 1 };
		break;
	case CharacterDir::LEFT:
		m_vDir = { -1 , 0 };
		break;
	case CharacterDir::LEFT_BOTTOM:
		m_vDir = { -1 , -1 };
		break;
	case CharacterDir::BOTTOM:
		m_vDir = { 0 , -1 };
		break;
	case CharacterDir::RIGHT_BOTTOM:
		m_vDir = { 1, -1 };
		break;
	default:
		break;
	}

	D3DXVec2Normalize(&m_vDir, &m_vDir);

}

void Character::Move()
{
	D3DXVECTOR2 move = this->GetTransform2D()->GetPosition();
	move.x += m_vDir.x * m_fMoveSpeed * g_pTimeManager->GetDeltaTime();
	move.y += m_vDir.y * m_fMoveSpeed * g_pTimeManager->GetDeltaTime();
	this->GetTransform2D()->SetPosition(move);
}
