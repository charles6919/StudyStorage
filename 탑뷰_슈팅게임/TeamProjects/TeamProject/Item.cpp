#include "stdafx.h"
#include "Item.h"

Item::Item()
{
	m_pSprite		= NULL;
	m_pHitCollider	= NULL;
}

Item::~Item()
{
	SAFE_DELETE(m_pHitCollider);
	SAFE_DELETE(m_pSprite);
}

void Item::Init()
{
	GameObject2D::Init();
	m_eType = ItemType::AmmoPack;
}

void Item::Update()
{
	m_pSprite->SetConstantScale(m_pTransform2D->GetScale());
	m_pSprite->SetRotation(m_pTransform2D->GetRotation());
	m_pSprite->SetPosition(m_pTransform2D->GetPosition());

	m_pHitCollider->GetTransform2D().SetScale(m_pTransform2D->GetScale() * 0.75f);
	m_pHitCollider->GetTransform2D().SetRotation(m_pTransform2D->GetRotation());
	m_pHitCollider->GetTransform2D().SetPosition(m_pTransform2D->GetPosition());

	m_pHitCollider->GetCircleCollider2D()->SetRadius(m_pHitCollider->GetTransform2D().GetScale().x);
	m_pHitCollider->GetCircleCollider2D()->SetRotation(m_pHitCollider->GetTransform2D().GetRotation());
	m_pHitCollider->GetCircleCollider2D()->SetPosition(m_pHitCollider->GetTransform2D().GetPosition());

	if (m_pSprite)
		m_pSprite->Update();

	if (m_pHitCollider)
		m_pHitCollider->Update();

}

void Item::Render()
{
	if (m_pSprite)
		m_pSprite->Render();

	if (m_pHitCollider)
		m_pHitCollider->Render();
}
