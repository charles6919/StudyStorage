#include "stdafx.h"
#include "Item.h"

Item::Item()
{
	m_pSprite = NULL;
}

Item::~Item()
{
	SAFE_DELETE(m_pSprite);
}

void Item::Init()
{
	switch (m_eType)
	{
	case Item_Type::Normal_Item:
		m_pSprite = new Sprite(L"Normal_Item");
		break;
	case Item_Type::Attack_Item:
		m_pSprite = new Sprite(L"Attack_Item");
		break;
	case Item_Type::Fruite:
		break;
	default:
		break;
	}
}

void Item::Update()
{
	m_pSprite->SetPosition(m_vPosition);
	m_pSprite->SetRotation(m_vRotation);
	m_pSprite->SetConstantScale(m_vScale);
	m_pSprite->Update();
}

void Item::Render()
{
	m_pSprite->Render();
}
