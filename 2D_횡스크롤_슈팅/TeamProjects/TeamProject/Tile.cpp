#include "stdafx.h"
#include "Tile.h"

Tile::Tile()
{
	m_pTransform	= NULL;
	m_pRigidBody	= NULL;
	m_pRtCollider	= NULL;
	m_pSprite		= NULL;
}

Tile::~Tile()
{
	SAFE_DELETE(m_pTransform	);
	SAFE_DELETE(m_pRigidBody	);
	SAFE_DELETE(m_pRtCollider	);
	SAFE_DELETE(m_pSprite		);
}

void Tile::Init()
{
	m_pTransform->Init();
	m_pRigidBody->SetTransform2D(m_pTransform);
	m_pRigidBody->Init();
	m_pRtCollider->Init();
	m_pSprite->Init();
}

void Tile::Update()
{
}

void Tile::Render()
{
}
