#include "pch.h"
#include "Interface.h"

Interface::Interface()
	:
	m_pFullHpSprite	 (NULL),
	m_pHalfHpSprite	 (NULL),
	m_pEmptyHpSprite (NULL),
	m_pBlankSprite	 (NULL),
	m_pArmorSprite	 (NULL),
	m_pCoinSprite	 (NULL)
{
	m_pFullHpSprite = new Sprite(L"Full_Heart");
	m_pHalfHpSprite = new Sprite(L"Half_Heart");
	m_pEmptyHpSprite = new Sprite(L"Empty_Heart");
	m_pBlankSprite = new Sprite(L"Blank");
	m_pArmorSprite = new Sprite(L"Armor");
	m_pCoinSprite = new Sprite(L"Coin");

}

Interface::~Interface()
{
	SAFE_DELETE(m_pFullHpSprite);
	SAFE_DELETE(m_pHalfHpSprite);
	SAFE_DELETE(m_pEmptyHpSprite);
	SAFE_DELETE(m_pBlankSprite);
	SAFE_DELETE(m_pArmorSprite);
	SAFE_DELETE(m_pCoinSprite);
}

void Interface::Init()
{
	m_isRenderInterface = true;
	m_nPlayerHp = 0;
	m_nPlayerMaxHp = 0;
	m_nPlayerBlank = 0;
	m_nPlayerArmor = 0;
	m_nPlayerCoin = 0;
}

void Interface::Update()
{
}

void Interface::Render()
{
	int hp_f = m_nPlayerHp / 2;
	int hp_h = m_nPlayerHp % 2;
	int hp_e = (m_nPlayerMaxHp - m_nPlayerHp) / 2;
	D3DXVECTOR2 v = { g_pCamera->GetPosition().x + 10.0f , g_pCamera->GetPosition().y + WINSIZEY - 10.0f - 50.0f};

	for (int i = 0; i < hp_f; i++)
	{
		m_pFullHpSprite->SetConstantScale(24, 24);
		m_pFullHpSprite->SetLBPosition( v.x,  v.y);
		m_pFullHpSprite->UpdateNRender();
		v.x = m_pFullHpSprite->GetPosition().x + 24.0f * 0.5f;
	}

	for (int i = 0; i < hp_h; i++)
	{
		m_pHalfHpSprite->SetConstantScale(24, 24);
		m_pHalfHpSprite->SetLBPosition(v.x , v.y);
		m_pHalfHpSprite->UpdateNRender();
		v.x = m_pHalfHpSprite->GetPosition().x + 24.0f * 0.5f;
	}

	for (int i = 0; i < hp_e; i++)
	{
		m_pEmptyHpSprite->SetConstantScale(24, 24);
		m_pEmptyHpSprite->SetLBPosition(v.x , v.y);
		m_pEmptyHpSprite->UpdateNRender();
		v.x = m_pEmptyHpSprite->GetPosition().x + 24.0f * 0.5f;
	}

	for (int i = 0; i < m_nPlayerArmor; i++)
	{
		m_pArmorSprite->SetConstantScale(24, 24);
		m_pArmorSprite->SetLBPosition(v.x, v.y);
		m_pArmorSprite->UpdateNRender();
		v.x = m_pArmorSprite->GetPosition().x + 24.0f * 0.5f;
	}

	v = { g_pCamera->GetPosition().x + 10.0f , g_pCamera->GetPosition().y + WINSIZEY - 10.0f - 80.0f };
	for (int i = 0; i < m_nPlayerBlank; i++)
	{
		m_pBlankSprite->SetConstantScale(24, 24);
		m_pBlankSprite->SetLBPosition(v.x, v.y);
		m_pBlankSprite->UpdateNRender();
		v.x = m_pBlankSprite->GetPosition().x + 24.0f * 0.5f;
	}
}

void Interface::SetPlayerValues(int hp, int maxHp, int blank, int armor, int coin)
{
	m_nPlayerHp = hp;
	m_nPlayerMaxHp = maxHp;
	m_nPlayerBlank = blank;
	m_nPlayerArmor = armor;
	m_nPlayerCoin = coin;
}
