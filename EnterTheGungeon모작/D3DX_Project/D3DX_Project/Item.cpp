#include "pch.h"
#include "Item.h"

Item::Item()
	:
	m_pAnimation(NULL),
	m_pSprite(NULL)
{
	m_stCircleCollider.CreateCircle();
}

Item::~Item()
{
	m_stCircleCollider.Release();
	SAFE_DELETE(m_pSprite);
	SAFE_DELETE(m_pAnimation);
}

void Item::Init()
{
	m_eState = ItemState::Idle;
	m_stItemInfo.itemCode = ItemCode::NONE;
	m_stItemInfo.name = L"";
	m_stItemInfo.type = ItemType::Life;
}

void Item::Update()
{
	if (m_pAnimation)
	{
		m_pAnimation->Play(m_eState);
		m_pAnimation->SetConstantSizeScale(m_transform2D.scale);
		m_pAnimation->SetPosition(m_transform2D.position);
		m_pAnimation->SetRotation(m_transform2D.rotation);
		m_pAnimation->Update();
	}

	if (m_stCircleCollider.pCircle)
	{
		m_stCircleCollider.Update();
	}
}

void Item::PassiveUpdate()
{
	if (m_stItemInfo.type == ItemType::PassiveItem)
	{
		switch (m_stItemInfo.itemCode)
		{
			
		}
	}
}

void Item::Render()
{
	if (m_pAnimation)
		m_pAnimation->Render();

	if (m_stCircleCollider.pCircle)
		m_stCircleCollider.Render();
	
}

void Item::ItmeInfo_Init(ItemCode code)
{
	m_stItemInfo.itemCode = code;

	switch (m_stItemInfo.itemCode)
	{
		case ItemCode::NONE:
			m_stItemInfo.name = L"None";
			m_stItemInfo.type = ItemType::None;
			break;
		case ItemCode::HEART:
			m_stItemInfo.name = L"Heart";
			m_stItemInfo.type = ItemType::Life;
			break;
		case ItemCode::HEART_HALF:
			m_stItemInfo.name = L"Heart Half";
			m_stItemInfo.type = ItemType::Life;
			break;
		case ItemCode::ARMOR:
			m_stItemInfo.name = L"Armor";
			m_stItemInfo.type = ItemType::Armor;
			break;
		case ItemCode::AMMO_BOX:
			m_stItemInfo.name = L"Ammo Box";
			m_stItemInfo.type = ItemType::Ammo;
			break;
		case ItemCode::BLANK:
			m_stItemInfo.name = L"Blank";
			m_stItemInfo.type = ItemType::Blank;
			break;
		case ItemCode::BULLET_BOOTS:
			m_stItemInfo.name = L"Bullet Boots";
			m_stItemInfo.type = ItemType::PassiveItem;
			break;
		case ItemCode::CRUTCHES:
			m_stItemInfo.name = L"Crutches";
			m_stItemInfo.type = ItemType::PassiveItem;
			break;
		case ItemCode::BACKUPGUN:
			m_stItemInfo.name = L"Backup Gun";
			m_stItemInfo.type = ItemType::PassiveItem;
			break;
		case ItemCode::SCOPE:
			m_stItemInfo.name = L"Scope";
			m_stItemInfo.type = ItemType::PassiveItem;
			break;
		case ItemCode::NATURAL_GUN_MAGNETICSTONE:
			m_stItemInfo.name = L"Natural Gun Magnetic Stone";
			m_stItemInfo.type = ItemType::ActiveItem;
			break;
		case ItemCode::A_PIECE_OF_CHEESE:
			m_stItemInfo.name = L"A Piece of Cheese";
			m_stItemInfo.type = ItemType::ActiveItem;
			break;
	}
}
