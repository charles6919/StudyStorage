#include "stdafx.h"
#include "PlayScene.h"

void PlayScene::Init()
{
	g_pBulletManager->Init();
	m_pMap = new Map;

	m_pPlayer = new Player;
	Animation<PlayerState>* ani = new Animation<PlayerState>;

	CircleCollider2D* col = new CircleCollider2D;
	Circle* c = new Circle;
	c->SetDraw(false);
	c->SetBorder(true);
	col->Init();
	col->SetCircleCollider2D(c);
	m_pPlayer->SetHitCollider(col);

	col = new CircleCollider2D;
	c = new Circle;
	c->SetDraw(false);
	c->SetBorder(true);
	col->Init();
	col->SetCircleCollider2D(c);
	m_pPlayer->SetAggroCollider(col);

	ProgressBar* bar = new ProgressBar(L"ProgressBack", L"ProgressFront");
	m_pPlayer->SetHpBar(bar);
	m_pPlayer->Init();

	CreateSprites(ani, L"Player_HIdle", PlayerState::HIdle, 20, 1, 20, 20, 0);
	CreateSprites(ani, L"Player_HRun", PlayerState::HRun, 20, 1, 20, 20, 0);
	CreateSprites(ani, L"Player_HShot", PlayerState::HShot, 3, 1, 3, 10, 0);
	CreateSprites(ani, L"Player_HReload", PlayerState::HReload, 15, 1, 15, 15, 0);

	CreateSprites(ani, L"Player_RIdle", PlayerState::RIdle, 20, 1, 20, 20, 0);
	CreateSprites(ani, L"Player_RRun", PlayerState::RRun, 20, 1, 20, 20, 0);
	CreateSprites(ani, L"Player_RShot", PlayerState::RShot, 3, 1, 3, 20, 0);
	CreateSprites(ani, L"Player_RReload", PlayerState::RReload, 20, 1, 20, 20, 0);

	m_pPlayer->SetAnimation(ani);
	g_pCamera->SetTarget(&m_pPlayer->GetTransform2D()->GetPosition());


	for (int i = 0; i < 1; i++)
	{
		Enemy* enemy = new Enemy;
		D3DXVECTOR2 randPos;
		randPos.x = rand() % MAPSIZEX;
		randPos.y = rand() % MAPSIZEY;
		enemy->GetTransform2D()->SetPosition(randPos);
		m_vecEnemy.push_back(enemy);
	}

	m_pNormalEnemy = new stEnemy;
	m_pNormalEnemy->_pAni = new Animation<EnemyState>;
	CreateSprites(m_pNormalEnemy->_pAni, L"Enemy_Idle", EnemyState::Idle, 17, 1, 17, 17, 0);
	CreateSprites(m_pNormalEnemy->_pAni, L"Enemy_Run", EnemyState::Run, 17, 1, 17, 17, 0);

	col = new CircleCollider2D;
	c = new Circle;
	c->SetDraw(false);
	c->SetBorder(true);
	col->SetCircleCollider2D(c);
	m_pNormalEnemy->_pHitCollider = col;
	
	m_fElapsedTimer = 0.0f;
	m_fRespawnSpeed = 1.0f;

	m_fRespawnItemSpeed = 3.0f;
	m_fElapsedItemTimer = 0.0f;

}

void PlayScene::Update()
{
	g_pSoundManager->Play("PlayBgm");

	if (m_fElapsedTimer >= m_fRespawnSpeed)
	{
		Respawn();
		m_fElapsedTimer = 0.0f;
	}

	m_fElapsedTimer += g_pTimeManager->GetDeltaTime();

	if (m_fElapsedItemTimer >= m_fRespawnItemSpeed)
	{
		RespawnItem();
		m_fElapsedItemTimer = 0.0f;
	}

	m_fElapsedItemTimer += g_pTimeManager->GetDeltaTime();


	Collision();

	if (m_pPlayer)
		m_pPlayer->Update();

	g_pBulletManager->Update();

	for (int i = m_vecEnemy.size() - 1; i >= 0; i--)
	{
		if (m_vecEnemy[i]->GetIsDead() == false)
		{
			m_vecEnemy[i]->Update();
		}
	}

	for (int i = m_vecItem.size() - 1; i >= 0; i--)
	{
		m_vecItem[i]->Update();
	}

	g_pCamera->Update();

}

void PlayScene::Render()
{
	if(m_pMap)
		m_pMap->Render();

	for (int i = m_vecItem.size() - 1; i >= 0; i--)
	{
		m_vecItem[i]->Render();
	}

	for (int i = m_vecEnemy.size() - 1; i >= 0; i--)
	{
		if (m_vecEnemy[i]->GetIsDead() == false)
		{
			Transform2D t = *m_vecEnemy[i]->GetTransform2D();
			m_pNormalEnemy->_pAni->SetConstantSizeScale(t.GetScale());
			m_pNormalEnemy->_pAni->SetRotation(t.GetRotation());
			m_pNormalEnemy->_pAni->SetPosition(t.GetPosition());
			m_pNormalEnemy->_pAni->SetStartFrame(m_vecEnemy[i]->GetState(), m_vecEnemy[i]->GetCurrFrameIndex());
			m_pNormalEnemy->_pAni->Play(m_vecEnemy[i]->GetState());
			t.SetScale(t.GetScale() * 0.5f);
			m_pNormalEnemy->_pHitCollider->SetTransform2D(t);
	
			m_pNormalEnemy->_pAni->Update();
			m_pNormalEnemy->_pAni->Render();
			m_vecEnemy[i]->SetCurrFrameIndex(m_pNormalEnemy->_pAni->GetClip(m_vecEnemy[i]->GetState())->GetCurrFrameIndex());
			m_pNormalEnemy->_pHitCollider->Update();
			m_pNormalEnemy->_pHitCollider->Render();
		}
	}

	if (m_pPlayer)
		m_pPlayer->Render();

	g_pBulletManager->Render();

}

void PlayScene::Release()
{
	for (int i = 0; i < m_vecItem.size(); i++)
	{
		SAFE_DELETE(m_vecItem[i]);
	}
	m_vecItem.clear();

	SAFE_DELETE(m_pNormalEnemy);
	
	for (int i = 0; i < m_vecEnemy.size(); i++)
	{
		SAFE_DELETE(m_vecEnemy[i]);
	}
	m_vecEnemy.clear();

	g_pBulletManager->Release();
	
	SAFE_DELETE(m_pPlayer);
}

void PlayScene::Collision()
{
	//Player.HitCollider VS Enemy.HitCollider
	{
		for (int i = m_vecEnemy.size() - 1; i >= 0; i--)
		{
			if (m_vecEnemy[i]->GetIsDead() == false && CircleCollision(m_pPlayer->GetHitCollider()->GetTransform2D().GetPosition(), m_pPlayer->GetHitCollider()->GetCircleCollider2D()->GetRadius(),
				m_vecEnemy[i]->GetTransform2D()->GetPosition(), m_vecEnemy[i]->GetTransform2D()->GetScale().x * 0.5f))
			{
				g_pSoundManager->Play("HumanHit");
				m_vecEnemy[i]->Init();
				m_vecEnemy[i]->SetIsDead(true);
				m_pPlayer->TakeDamage(10);
			}
		}
	}


	//Bullet.HitCollider VS enemy.HitCollider
	{
		for (int i = g_pBulletManager->GetBulletVecIndex() - 1; i >= 0; i--)
		{
			for (int j = m_vecEnemy.size() - 1; j >= 0; j--)
			{
				if (m_vecEnemy[j]->GetIsDead() == false && CircleCollision(g_pBulletManager->GetBullet(i)->GetTransform2D()->GetPosition(), g_pBulletManager->GetBullet(i)->GetTransform2D()->GetScale().x*0.75f,
					m_vecEnemy[j]->GetTransform2D()->GetPosition(), m_vecEnemy[j]->GetTransform2D()->GetScale().x * 0.5f))
				{
					g_pSoundManager->Play("ZombieHit");
					m_vecEnemy[j]->TakeDmg(g_pBulletManager->GetBullet(i)->GetDamage());
					g_pBulletManager->DeleteBullet(i);
					break;
				}
			}
		}
	}

	//Bullet.TrackingRange VS enemy.HitCollider
	{
		for (int i = g_pBulletManager->GetBulletVecIndex() - 1; i >= 0; i--)
		{
			if (g_pBulletManager->GetBullet(i)->GetBulletType() == BulletType::TRACKING)
			{
				float length = 0.0f;
				float minLength = 999999.99f;
				int targetIndex = -1;
				for (int j = m_vecEnemy.size() - 1; j >= 0; j--)
				{
					if (m_vecEnemy[j]->GetIsDead() == false && g_pBulletManager->GetBullet(i)->GetIsTracking() == false && CircleCollision(g_pBulletManager->GetBullet(i)->GetTransform2D()->GetPosition(), 300.0f,
						m_vecEnemy[j]->GetTransform2D()->GetPosition(), m_vecEnemy[j]->GetTransform2D()->GetScale().x * 0.5f))
					{
						D3DXVECTOR2 v = g_pBulletManager->GetBullet(i)->GetTransform2D()->GetPosition() - m_vecEnemy[j]->GetTransform2D()->GetPosition();
						length = sqrtf(v.x * v.x + v.y * v.y);
						if (length < minLength)
						{
							minLength = length;
							targetIndex = j;
						}
					}
				}

				if (targetIndex != -1 && g_pBulletManager->GetBullet(i)->GetIsTracking() == false)
				{
					g_pBulletManager->GetBullet(i)->SetIsTracking(true);
					g_pBulletManager->GetBullet(i)->SetStartPos(g_pBulletManager->GetBullet(i)->GetTransform2D()->GetPosition());
					g_pBulletManager->GetBullet(i)->SetTargetPos(&m_vecEnemy[targetIndex]->GetTransform2D()->GetPosition());
				}
			}
		}
	}

	//Player.AggroCollider VS Enemy.HitCollider
	{
		for (int i = m_vecEnemy.size() - 1; i >= 0; i--)
		{
			if (m_vecEnemy[i]->GetIsDead() == false && CircleCollision(m_pPlayer->GetAggroCollider()->GetTransform2D().GetPosition(), m_pPlayer->GetAggroCollider()->GetCircleCollider2D()->GetRadius(),
				m_vecEnemy[i]->GetTransform2D()->GetPosition(), m_vecEnemy[i]->GetTransform2D()->GetScale().x * 0.5f))
			{
				m_vecEnemy[i]->SetIsTracking(true);
				m_vecEnemy[i]->SetTarget(m_pPlayer->GetTransform2D()->GetPosition());
			}
			else
			{
				m_vecEnemy[i]->SetIsTracking(false);
			}
		}
	}

	//Enemy.HitCollider VS Enemy.TargetPos
	{
		for (int i = m_vecEnemy.size() - 1; i >= 0; i--)
		{
			if (m_vecEnemy[i]->GetIsDead() == false && PointInCircle(m_vecEnemy[i]->GetTransform2D()->GetPosition(), m_vecEnemy[i]->GetTransform2D()->GetScale().x * 0.5f, m_vecEnemy[i]->GetTargetPos()))
			{
				m_vecEnemy[i]->SetPatternTimer(m_vecEnemy[i]->GetPatternDuration());
			}
		}
	}

	//Player.HitCollider VS Item.HitCollider
	{
		for (int i = m_vecItem.size() - 1; i >= 0; i--)
		{
			if (CircleCollision(*m_pPlayer->GetHitCollider()->GetCircleCollider2D(), *m_vecItem[i]->GetHitCollider()->GetCircleCollider2D()))
			{
				switch (m_vecItem[i]->GetType())
				{
				case ItemType::AmmoPack:
					m_pPlayer->AddAmmo(30);
					break;
				case ItemType::HealPack:
					m_pPlayer->AddHp(15);
					break;
				case ItemType::SteamPack:
					m_pPlayer->IncreaseMoveSpeed(30.0f);
					m_pPlayer->IncreaseRotSpeed(0.3f);
					break;
				}

				SAFE_DELETE(m_vecItem[i]);
				m_vecItem.erase(m_vecItem.begin() + i);

			}
		}
	}
}

void PlayScene::Respawn()
{
	int index = -1;
	for (int i = m_vecEnemy.size() - 1; i >= 0; i--)
	{
		if (m_vecEnemy[i]->GetIsDead())
		{
			index = i;
			break;
		}
	}

	if (index == -1)
	{
		Enemy* p = new Enemy;
		D3DXVECTOR2 randPos;
		randPos.x = rand() % MAPSIZEX;
		randPos.y = rand() % MAPSIZEY;
		p->GetTransform2D()->SetPosition(randPos);
		m_vecEnemy.push_back(p);
	}
	else
	{
		m_vecEnemy[index]->Init();
		D3DXVECTOR2 randPos;
		randPos.x = rand() % MAPSIZEX;
		randPos.y = rand() % MAPSIZEY;
		m_vecEnemy[index]->GetTransform2D()->SetPosition(randPos);
	}



}

void PlayScene::RespawnItem()
{
	ItemType type;
	type = (ItemType)(rand() % (int)ItemType::Max);

	Item* item = new Item;
	item->Init();
	CircleCollider2D* col = new CircleCollider2D;
	Circle* c = new Circle;
	c->SetDraw(false);
	c->SetBorder(true);
	Sprite* sprite = NULL;

	switch (type)
	{
	case ItemType::AmmoPack:
		sprite = new Sprite(L"AmmoPack");
		break;
	case ItemType::HealPack:
		sprite = new Sprite(L"HealPack");
		break;
	case ItemType::SteamPack:
		sprite = new Sprite(L"SteamPack");
		break;
	}
	col->SetCircleCollider2D(c);

	item->SetType(type);
	item->SetSprite(sprite);
	item->SetHitCollider(col);

	D3DXVECTOR2 randPos;
	randPos.x = rand() % MAPSIZEX;
	randPos.y = rand() % MAPSIZEY;
	item->GetTransform2D()->SetPosition(randPos);
	item->GetTransform2D()->SetScale(ITEM_DEFAULTV);

	m_vecItem.push_back(item);
}
