#include "stdafx.h"
#include "BulletManager.h"

BulletManager::BulletManager()
{
	m_pBullet = NULL;
}

BulletManager::~BulletManager()
{
}

void BulletManager::Init()
{
	m_pBullet = new stBullet;
	
	Sprite* sprite = new Sprite(L"Bullet");
	m_pBullet->_pSprite = sprite;

	CircleCollider2D* col = new CircleCollider2D;
	Circle* c = new Circle;
	c->SetDraw(false);
	c->SetBorder(true);
	col->SetCircleCollider2D(c);
	m_pBullet->_pHitCollider = col;

	col = new CircleCollider2D;
	c = new Circle;
	c->SetDraw(false);
	c->SetBorder(true);
	col->SetCircleCollider2D(c);
	m_pBullet->_pTrakingRange = col;
}

void BulletManager::Update()
{
	for (int i = m_vecBullet.size() - 1; i >= 0; i--)
	{
		if (m_vecBullet[i]->GetIsActive())
			m_vecBullet[i]->Update();
		else
		{
			SAFE_DELETE(m_vecBullet[i]);
			m_vecBullet.erase(m_vecBullet.begin() + i);
		}
	}
}

void BulletManager::Render()
{
	for (int i = 0; i < m_vecBullet.size(); i++)
	{
		if (m_vecBullet[i]->GetIsActive())
		{
			m_pBullet->_pSprite->SetPosition(m_vecBullet[i]->GetTransform2D()->GetPosition());
			m_pBullet->_pSprite->SetRotation(m_vecBullet[i]->GetTransform2D()->GetRotation());
			m_pBullet->_pSprite->SetConstantScale(m_vecBullet[i]->GetTransform2D()->GetScale());
			m_pBullet->_pHitCollider->GetTransform2D().SetPosition(m_vecBullet[i]->GetTransform2D()->GetPosition());
			m_pBullet->_pHitCollider->GetTransform2D().SetRotation(m_vecBullet[i]->GetTransform2D()->GetRotation());
			m_pBullet->_pHitCollider->GetTransform2D().SetScale(m_vecBullet[i]->GetTransform2D()->GetScale() * 0.75f);
			m_pBullet->_pTrakingRange->GetTransform2D().SetPosition(m_vecBullet[i]->GetTransform2D()->GetPosition());
			m_pBullet->_pTrakingRange->GetTransform2D().SetRotation(m_vecBullet[i]->GetTransform2D()->GetRotation());
			m_pBullet->_pTrakingRange->GetTransform2D().SetScale(600.0f, 600.0f);
			m_pBullet->_pSprite->Update();
			m_pBullet->_pHitCollider->Update();
			m_pBullet->_pTrakingRange->Update();
			m_pBullet->_pSprite->Render();
			m_pBullet->_pHitCollider->Render();
			m_pBullet->_pTrakingRange->Render();
		}
		
	}
}

void BulletManager::Release()
{
	for (int i = 0; i > m_vecBullet.size(); i++)
	{
		SAFE_DELETE(m_vecBullet[i]);
	}
	m_vecBullet.clear();
}
