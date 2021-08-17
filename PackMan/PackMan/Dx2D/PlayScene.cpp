#include "stdafx.h"
#include "PlayScene.h"


void PlayScene::Init()
{
	// 클래스 생성
	m_pMap = new Map;
	m_pMap->LoadMap();

	int nCount = 0;
	for (int i = 0; i < NUM_TILE_Y; i++)
	{
		for (int j = 0; j < NUM_TILE_X; j++)
		{
			if (((j >= 14 && i >= 10) && (j <= 18 && i <= 12)) || (j == 16 && i == 13))
			{
				continue;
			}
			else
			{
				if (m_pMap->GetTileInfo(j, i).eOType == OBJECT_TYPE::None)
				{
					if (nCount % 42 != 0)
					{
						Item* item = new Item;
						item->SetItemType(Item_Type::Normal_Item);
						item->Init();
						item->SetPosition(D3DXVECTOR2(j * TILE_SIZE + TILE_SIZE * 0.5f, i * TILE_SIZE + TILE_SIZE * 0.5f));
						item->SetScale(D3DXVECTOR2(8, 8));
						item->SetScore(10);
						m_vecScoreItems.push_back(item);
					}
					else
					{
						Item* item = new Item;
						item->SetItemType(Item_Type::Attack_Item);
						item->Init();
						item->SetPosition(D3DXVECTOR2(j * TILE_SIZE + TILE_SIZE * 0.5f, i * TILE_SIZE + TILE_SIZE * 0.5f));
						item->SetScale(D3DXVECTOR2(16, 16));
						item->SetScore(0);
						m_vecAttackItems.push_back(item);
					}
					nCount++;
				}
			}
		}
	}
	m_nlevel = 0;

	m_pPlayer = new Player;
	m_pPlayer->Init();
	m_pPlayer->SetMap(m_pMap);

	Circle* c = new Circle;
	m_pPlayer->SetHitCollider(c);

	c = new Circle;
	m_pPlayer->SetAggroCollider(c);
	g_pCamera->SetFocus(WINSIZEX * 0.5f, WINSIZEY * 0.5f);

	m_pDijkstra = new PlayDijkstra(m_pMap);
	for (int i = 0; i < DEFAULT_NUM_ENEMY + m_nlevel; i++)
	{
		Enemy* enemy = new Enemy;
		enemy->SetMap(m_pMap);
		enemy->SetDijkstra(m_pDijkstra);
		enemy->SetPlayer(m_pPlayer);
		enemy->Init();
		m_vecEnemy.push_back(enemy);
	}

	m_fRespawnSpeed = 8.0f;
	m_fRespawnTimer = 0.0f;
	m_numEnemyJailed = 0;
	

}

void PlayScene::Update()
{
	static int tileIndex[2];
	POINT point = GET_TILE_INDEXPOINT(g_ptMouse.x, g_ptMouse.y);
	tileIndex[0] = point.x;
	tileIndex[1] = point.y;
	ImGui::InputInt2("INDEX", tileIndex);

	if (g_pKeyManager->isOnceKeyDown(VK_ESCAPE))
		g_pLoadManager->ChangeScene(SCENE_KIND::Title);

	if (m_fRespawnTimer >= m_fRespawnSpeed)
	{
		m_fRespawnTimer = 0.0f;
		for (int i = m_vecEnemy.size() - 1; i >= 0; i--)
		{
			if (m_vecEnemy[i]->GetIsJailed())
			{
				m_vecEnemy[i]->SetIsJailed(false);
				break;
			}

		}
	}
	else
	{
		if(m_numEnemyJailed != 0)
			m_fRespawnTimer += g_pTimeManager->GetDeltaTime();
	}


	if (m_vecScoreItems.size() == 0)
	{
		m_isClear = true;
	}

	for (int i = m_vecScoreItems.size() - 1; i >= 0; i--)
	{
		m_vecScoreItems[i]->Update();
	}

	for (int i = m_vecAttackItems.size() - 1; i >= 0; i--)
	{
		m_vecAttackItems[i]->Update();
	}

	for (int i = m_vecEnemy.size() - 1; i >= 0; i--)
	{
		m_vecEnemy[i]->Update();

	}

	if (m_pPlayer)
		m_pPlayer->Update();

	Collision();

	if (m_isClear)
	{
		
	}

}

void PlayScene::Render()
{
	if (m_pMap)
		m_pMap->Render();

	for (int i = m_vecScoreItems.size() - 1; i >= 0; i--)
	{
		m_vecScoreItems[i]->Render();
	}

	for (int i = m_vecAttackItems.size() - 1; i >= 0; i--)
	{
		m_vecAttackItems[i]->Render();
	}

	for (int i = m_vecEnemy.size() - 1; i >= 0; i--)
	{
		m_vecEnemy[i]->Render();
	}

	if (m_pPlayer)
		m_pPlayer->Render();
}

void PlayScene::Release()
{
	SAFE_DELETE(m_pMap);

	for (int i = m_vecScoreItems.size() - 1; i >= 0; i--)
	{
		SAFE_DELETE(m_vecScoreItems[i]);
	}
	m_vecScoreItems.clear();

	for (int i = m_vecAttackItems.size() - 1; i >= 0; i--)
	{
		SAFE_DELETE(m_vecAttackItems[i]);
	}
	m_vecAttackItems.clear();

	for (int i = m_vecEnemy.size() - 1; i >= 0; i--)
	{
		SAFE_DELETE(m_vecEnemy[i]);
	}
	m_vecEnemy.clear();

	SAFE_DELETE(m_pPlayer);
}

void PlayScene::StageInit()
{
}

void PlayScene::Collision()
{
	for (int i = m_vecScoreItems.size() - 1; i >= 0; i--)
	{
		if (PointInCircle(*m_pPlayer->GetHitCollider(), m_vecScoreItems[i]->GetPosition()))
		{
			m_pPlayer->TakeScore(m_vecScoreItems[i]->GetScore());
			SAFE_DELETE(m_vecScoreItems[i]);
			m_vecScoreItems.erase(m_vecScoreItems.begin() + i);
		}
	}

	for (int i = m_vecAttackItems.size() - 1; i >= 0; i--)
	{
		if (PointInCircle(*m_pPlayer->GetHitCollider(), m_vecAttackItems[i]->GetPosition()))
		{
			m_pPlayer->TakeScore(m_vecAttackItems[i]->GetScore());
			m_pPlayer->SetIsAttacking(true);
			m_pPlayer->SetElapsedTime(0.0f);
			SAFE_DELETE(m_vecAttackItems[i]);
			m_vecAttackItems.erase(m_vecAttackItems.begin() + i);
		}
	}

	for (int i = m_vecEnemy.size() - 1; i >= 0; i--)
	{
		if (CircleCollision(*m_vecEnemy[i]->GetHitCollider(), *m_pPlayer->GetAggroCollider()))
		{
			m_vecEnemy[i]->SetIsTracking(true);
		}
		else
		{
			m_vecEnemy[i]->SetIsTracking(false);
		}
	}
	
	for (int i = m_vecEnemy.size() - 1; i >= 0; i--)
	{
		if (CircleCollision(*m_vecEnemy[i]->GetHitCollider(), *m_pPlayer->GetHitCollider()) && m_vecEnemy[i]->GetIsJailed() == false)
		{
			if (m_pPlayer->GetIsAttacking())
			{
				m_vecEnemy[i]->SetIsJailed(true);
				m_numEnemyJailed++;
			}
			else
			{
				m_pPlayer->Dead();
				for (int i = 0; i < m_vecEnemy.size(); i++)
				{
					m_vecEnemy[i]->StageInit();
				}
			}
		}
	}

}
