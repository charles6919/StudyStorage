#pragma once
#include "GameObject2D.h"

#define ITEM_DEFAULTX 50
#define ITEM_DEFAULTY 50
#define ITEM_DEFAULTV (D3DXVECTOR2(ITEM_DEFAULTX,ITEM_DEFAULTY))

enum class ItemType
{
	AmmoPack,
	HealPack,
	SteamPack,
	Max
};

class Item :
	public GameObject2D
{
private:
	ItemType			m_eType;
	Sprite*				m_pSprite;
	CircleCollider2D*	m_pHitCollider;

public:
	Item();
	~Item();

	void Init();
	void Update();
	void Render();


	void SetType(ItemType type) { m_eType = type; }
	void SetSprite(Sprite* p) { m_pSprite = p; }
	void SetHitCollider(CircleCollider2D* col) { m_pHitCollider = col; }

	ItemType GetType() { return m_eType; }
	CircleCollider2D* GetHitCollider() { return m_pHitCollider; }
};

