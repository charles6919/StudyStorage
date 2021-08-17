#include "stdafx.h"
#include "BulletManager.h"
#include "Player.h"
#include "Boss.h"

BulletManager::BulletManager()
{
	for (int i = 0; i < (int)Bullet_Type::Max; i++)
	{
		m_stBullet[i] = NULL;
	}

	{
		g_pTextureManager->AddTexture(L"PlayerBullet", L"BulletPlayer.png");
		g_pTextureManager->AddTexture(L"BossBullet", L"BulletBoss.png");
	}

	for (int i = 0; i < (int)Bullet_Type::Max; i++)
	{
		m_stBullet[i] = new stBullet;
		Sprite* sprite = NULL;

		switch ((Bullet_Type)i)
		{
		case Bullet_Type::Player_Normal:
		{
			sprite = new Sprite(L"PlayerBullet");
			break;
		}
		case Bullet_Type::Enemy_Normal:
		{
			sprite = new Sprite(L"BossBullet");
			break;
		}
		case Bullet_Type::Enemy_Curve:
		{
			sprite = new Sprite(L"BossBullet");
			break;
		}
		}

		m_stBullet[i]->_pSprite = sprite;
	}
}

BulletManager::~BulletManager()
{
	SAFE_DELETE_ARRAY(*m_stBullet);
}

void BulletManager::Init()
{
	
	for (auto p : m_vecPlayerBullet)
		SAFE_DELETE(p);
	m_vecPlayerBullet.clear();

	for (auto p : m_vecEnemyBullet)
		SAFE_DELETE(p);
	m_vecEnemyBullet.clear();

}

void BulletManager::Update()
{
	for (int i = m_vecPlayerBullet.size() - 1; i >= 0; i--)
	{
		//무브
		D3DXVECTOR2 pos = m_vecPlayerBullet[i]->GetTransform2D()->GetPosition();
		pos.x += m_vecPlayerBullet[i]->GetMoveDir().x * m_vecPlayerBullet[i]->GetMoveSpeed() * g_pTimeManager->GetDeltaTime();
		pos.y += m_vecPlayerBullet[i]->GetMoveDir().y * m_vecPlayerBullet[i]->GetMoveSpeed() * g_pTimeManager->GetDeltaTime();
		m_vecPlayerBullet[i]->GetTransform2D()->SetPosition(pos);

		POINT pt = { m_vecPlayerBullet[i]->GetTransform2D()->GetPosition().x, m_vecPlayerBullet[i]->GetTransform2D()->GetPosition().y };
		if (PointInRect(*m_pBoss->GetHitCollider()->GetRectCollider2D(), pt))
		{
			m_pBoss->SetIsHit(true);
			SAFE_DELETE(m_vecPlayerBullet[i]);
			m_vecPlayerBullet.erase(m_vecPlayerBullet.begin() + i);
			continue;
		}

		if (m_vecPlayerBullet[i]->GetTransform2D()->GetPosition().x < 0.0f ||
			m_vecPlayerBullet[i]->GetTransform2D()->GetPosition().x > WINSIZEX ||
			m_vecPlayerBullet[i]->GetTransform2D()->GetPosition().y < 0.0f ||
			m_vecPlayerBullet[i]->GetTransform2D()->GetPosition().y > WINSIZEY)
		{
			SAFE_DELETE(m_vecPlayerBullet[i]);
			m_vecPlayerBullet.erase(m_vecPlayerBullet.begin() + i);
			continue;
		}

		

		//충돌 판정
	}

	for (int i = m_vecEnemyBullet.size() - 1; i >= 0; i--)
	{

		//무브
		switch (m_vecEnemyBullet[i]->GetBulletType())
		{
		case Bullet_Type::Enemy_Normal:
		{
			D3DXVECTOR2 pos = m_vecEnemyBullet[i]->GetTransform2D()->GetPosition();
			pos.x += m_vecEnemyBullet[i]->GetMoveDir().x * m_vecEnemyBullet[i]->GetMoveSpeed() * g_pTimeManager->GetDeltaTime();
			pos.y += m_vecEnemyBullet[i]->GetMoveDir().y * m_vecEnemyBullet[i]->GetMoveSpeed() * g_pTimeManager->GetDeltaTime();
			m_vecEnemyBullet[i]->GetTransform2D()->SetPosition(pos);
		}
			break;
		case Bullet_Type::Enemy_Curve:
			m_vecEnemyBullet[i]->SetElapsedTime(m_vecEnemyBullet[i]->GetElapsedTime() + g_pTimeManager->GetDeltaTime());
			m_vecEnemyBullet[i]->GetTransform2D()->SetPosition(BezierCurve(m_vecEnemyBullet[i]->GetStart(), m_vecEnemyBullet[i]->GetVia(), m_vecEnemyBullet[i]->GetTarget(),m_vecEnemyBullet[i]->GetElapsedTime()/m_vecEnemyBullet[i]->GetTime()));
			break;
		}
		

		if (m_vecEnemyBullet[i]->GetTransform2D()->GetPosition().x < 0.0f ||
			m_vecEnemyBullet[i]->GetTransform2D()->GetPosition().x > WINSIZEX ||
			m_vecEnemyBullet[i]->GetTransform2D()->GetPosition().y < 0.0f 
			)
		{
			SAFE_DELETE(m_vecEnemyBullet[i]);
			m_vecEnemyBullet.erase(m_vecEnemyBullet.begin() + i);
			continue;
		}

		//충돌 판정
		POINT pt = { m_vecEnemyBullet[i]->GetTransform2D()->GetPosition().x, m_vecEnemyBullet[i]->GetTransform2D()->GetPosition().y };
		if (PointInRect(*m_pPlayer->GetHitCollider()->GetRectCollider2D(), pt))
		{
			m_pPlayer->SetIsHit(true);
			SAFE_DELETE(m_vecEnemyBullet[i]);
			m_vecEnemyBullet.erase(m_vecEnemyBullet.begin() + i);
			continue;
		}

		
	}

}

void BulletManager::Render()
{
	for (int i = m_vecPlayerBullet.size() - 1; i >= 0; i--)
	{
		switch (m_vecPlayerBullet[i]->GetBulletType())
		{
		case Bullet_Type::Player_Normal:
			m_stBullet[(int)Bullet_Type::Player_Normal]->_pSprite->SetPosition(m_vecPlayerBullet[i]->GetTransform2D()->GetPosition());
			m_stBullet[(int)Bullet_Type::Player_Normal]->_pSprite->SetConstantScale(m_vecPlayerBullet[i]->GetTransform2D()->GetScale());
			m_stBullet[(int)Bullet_Type::Player_Normal]->_pSprite->Update();
			m_stBullet[(int)Bullet_Type::Player_Normal]->_pSprite->Render();
			break;
		}
	}

	for (int i = m_vecEnemyBullet.size() - 1; i >= 0; i--)
	{
		switch (m_vecEnemyBullet[i]->GetBulletType())
		{
		case Bullet_Type::Enemy_Normal:
			m_stBullet[(int)Bullet_Type::Enemy_Normal]->_pSprite->SetPosition(m_vecEnemyBullet[i]->GetTransform2D()->GetPosition());
			m_stBullet[(int)Bullet_Type::Enemy_Normal]->_pSprite->SetConstantScale(m_vecEnemyBullet[i]->GetTransform2D()->GetScale());
			m_stBullet[(int)Bullet_Type::Enemy_Normal]->_pSprite->Update();
			m_stBullet[(int)Bullet_Type::Enemy_Normal]->_pSprite->Render();
			break;
		case Bullet_Type::Enemy_Curve:
			m_stBullet[(int)Bullet_Type::Enemy_Curve]->_pSprite->SetPosition(m_vecEnemyBullet[i]->GetTransform2D()->GetPosition());
			m_stBullet[(int)Bullet_Type::Enemy_Curve]->_pSprite->SetConstantScale(m_vecEnemyBullet[i]->GetTransform2D()->GetScale());
			m_stBullet[(int)Bullet_Type::Enemy_Curve]->_pSprite->Update();
			m_stBullet[(int)Bullet_Type::Enemy_Curve]->_pSprite->Render();
			break;
		}
	}
}
