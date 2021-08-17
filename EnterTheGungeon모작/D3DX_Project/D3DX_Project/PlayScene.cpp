#include "pch.h"
#include "PlayScene.h"

void PlayScene::UpdateTargetPos()
{
	D3DXVECTOR2 v;
	v.x = (m_pPlayer->GetPosition()->x + g_ptMouse.x + g_pCamera->GetPosition().x) * 0.5f;
	v.y = (m_pPlayer->GetPosition()->y + g_ptMouse.y + g_pCamera->GetPosition().y) * 0.5f;

	m_vCameraTarget = v;
}

void PlayScene::CollisionUpdate()
{
	for (int i = g_pBulletManager->GetBulletVector().size() - 1; i >= 0; i--)
	{
		Bullet* bullet = g_pBulletManager->GetBulletVector()[i];
		POINT pt = GET_TILE_POINT(bullet->m_stInfo.colTransform.position.x, bullet->m_stInfo.colTransform.position.y);
		
		if (bullet->m_stInfo.type == BulletType::Player)
		{
			if (m_pBoss)
			{
				//플레이어 탄 vs 보스
				if (CircleCollision(bullet->m_stInfo.colTransform.position, bullet->m_stInfo.colTransform.scale.x * 0.5f, m_pBoss->GetHitCollider().transform2D.position, m_pBoss->GetHitCollider().transform2D.scale.x * 0.5f))
				{
					m_pBoss->TakeDamage(bullet->m_stInfo.damage);

					Effect* effect = new Effect;
					effect->Init();
					effect->m_fDurationTime = 0.33f;
					effect->m_eType = EffectType::DestroyBullet;
					D3DXVECTOR2 v =bullet->m_stInfo.transform.position;
					effect->m_transform2D.position.x = v.x;
					effect->m_transform2D.position.y = v.y;
					effect->m_transform2D.scale = { 50, 50 };
					g_pEffectManager->GetVecEffect()->push_back(effect);

					SAFE_DELETE(g_pBulletManager->GetBulletVector()[i]);
					g_pBulletManager->GetBulletVector().erase(g_pBulletManager->GetBulletVector().begin() + i);
					continue;
				}
			}

			for (int j = m_vecEnemy.size() - 1; j >= 0; j--)
			{
				if (m_vecEnemy[j]->GetIsAlive() && CircleCollision(bullet->m_stInfo.colTransform.position, bullet->m_stInfo.colTransform.scale.x * 0.5f, m_vecEnemy[j]->GetHitCollider().transform2D.position, m_vecEnemy[j]->GetHitCollider().transform2D.scale.x * 0.5f))
				{
					//플레이어 탄 VS 적
					m_vecEnemy[j]->Hit(bullet->m_stInfo.damage);

					Effect* effect = new Effect;
					effect->Init();
					effect->m_fDurationTime = 0.33f;
					effect->m_eType = EffectType::DestroyBullet;
					D3DXVECTOR2 v = bullet->m_stInfo.transform.position;
					effect->m_transform2D.position.x = v.x;
					effect->m_transform2D.position.y = v.y;
					effect->m_transform2D.scale = { 50, 50 };
					g_pEffectManager->GetVecEffect()->push_back(effect);

					SAFE_DELETE(g_pBulletManager->GetBulletVector()[i]);
					g_pBulletManager->GetBulletVector().erase(g_pBulletManager->GetBulletVector().begin() + i);
					continue;
				}
			}
		}
			

		
		if (bullet->m_stInfo.type == BulletType::Enemy)
		{
			//적탄 vs 플레이어
			if (CircleCollision(bullet->m_stInfo.colTransform.position, bullet->m_stInfo.colTransform.scale.x * 0.5f, m_pPlayer->GetHitCollider().transform2D.position, m_pPlayer->GetHitCollider().transform2D.scale.x * 0.5f))
			{
				if (m_pPlayer->GetEnableToHit())
				{
					m_pPlayer->Hit();

					Effect* effect = new Effect;
					effect->Init();
					effect->m_fDurationTime = 0.33f;
					effect->m_eType = EffectType::DestroyBullet;
					D3DXVECTOR2 v = bullet->m_stInfo.transform.position;
					effect->m_transform2D.position.x = v.x;
					effect->m_transform2D.position.y = v.y;
					effect->m_transform2D.scale = { 50, 50 };
					g_pEffectManager->GetVecEffect()->push_back(effect);

					SAFE_DELETE(g_pBulletManager->GetBulletVector()[i]);
					g_pBulletManager->GetBulletVector().erase(g_pBulletManager->GetBulletVector().begin() + i);
				}
				continue;
			}

			if (m_pPlayer->GetIsAttack())
			{
				if (CircleCollision(bullet->m_stInfo.colTransform.position, bullet->m_stInfo.colTransform.scale.x * 0.5f, m_pPlayer->GetAttackCollider().transform2D.position, m_pPlayer->GetAttackCollider().transform2D.scale.x * 0.5f))
				{
					Effect* effect = new Effect;
					effect->Init();
					effect->m_fDurationTime = 0.33f;
					effect->m_eType = EffectType::DestroyBullet;
					D3DXVECTOR2 v = bullet->m_stInfo.transform.position;
					effect->m_transform2D.position.x = v.x;
					effect->m_transform2D.position.y = v.y;
					effect->m_transform2D.scale = { 50, 50 };
					g_pEffectManager->GetVecEffect()->push_back(effect);

					SAFE_DELETE(g_pBulletManager->GetBulletVector()[i]);
					g_pBulletManager->GetBulletVector().erase(g_pBulletManager->GetBulletVector().begin() + i);
					continue;
				}
			}
			
		}

		if (m_stTile[pt.y][pt.x].eTType != TERRAIN_TYPE::Walkable ||
			m_stTile[pt.y][pt.x].eOType != OBJECT_TYPE::None)
		{

			Effect* effect = new Effect;
			effect->Init();
			effect->m_fDurationTime = 0.33f;
			effect->m_eType = EffectType::DestroyBullet;
			D3DXVECTOR2 v = bullet->m_stInfo.transform.position;
			effect->m_transform2D.position.x = v.x;
			effect->m_transform2D.position.y = v.y;
			effect->m_transform2D.scale = { 50, 50 };
			g_pEffectManager->GetVecEffect()->push_back(effect);

			SAFE_DELETE(g_pBulletManager->GetBulletVector()[i]);
			g_pBulletManager->GetBulletVector().erase(g_pBulletManager->GetBulletVector().begin() + i);
			continue;
		}
	}

	if (m_pPlayer->GetIsAttack())
	{
		if (m_pBoss)
		{
			if (CircleCollision(m_pPlayer->GetAttackCollider().transform2D.position, m_pPlayer->GetAttackCollider().transform2D.scale.x * 0.5f, m_pBoss->GetHitCollider().transform2D.position, m_pBoss->GetHitCollider().transform2D.scale.x * 0.5f))
			{
				m_pBoss->TakeDamage(14);
			}
		}

		for (int i = m_vecEnemy.size() - 1; i >= 0; i--)
		{
			if (CircleCollision(m_pPlayer->GetAttackCollider().transform2D.position, m_pPlayer->GetAttackCollider().transform2D.scale.x * 0.5f, m_vecEnemy[i]->GetHitCollider().transform2D.position, m_vecEnemy[i]->GetHitCollider().transform2D.scale.x * 0.5f))
			{
				m_vecEnemy[i]->Hit(14);
			}
		}


	}
}

PlayScene::PlayScene()
	:
	m_pPlayer(NULL),
	m_pBoss(NULL),
	m_pBossHpProgressBar(NULL),
	m_pInterface(NULL)
{
}

PlayScene::~PlayScene()
{
	SAFE_DELETE(m_pPlayer);	
}

void PlayScene::Init()
{
	g_pCamera->SetMapSize(TILE_SIZE * NUM_TILE_X, TILE_SIZE * NUM_TILE_Y);
	g_pBulletManager->Init();
	g_pEffectManager->Init();
	m_pPlayer = new Player;
	m_pPlayer->Init();
	m_pPlayer->SetPosition(100, 100);
	m_pPlayer->Update();

	for (int y = 0; y < NUM_TILE_Y; y++)
	{
		for (int x = 0; x < NUM_TILE_X; x++)
		{
			if (y == 0 || y == NUM_TILE_Y -1 || x == 0 || x == NUM_TILE_X -1)
			{
				m_stTile[y][x].eTType = TERRAIN_TYPE::Wall;
				m_stTile[y][x].nTIndex = 40;
				m_stTile[y][x].eOType = OBJECT_TYPE::None;
				m_stTile[y][x].nOIndex = 0;
				m_stTile[y][x].eUType = UNIT_TYPE::None;
				m_stTile[y][x].nUIndex = 0;
			}
			else
			{
				m_stTile[y][x].eTType = TERRAIN_TYPE::Walkable;
				m_stTile[y][x].nTIndex = 48;
				m_stTile[y][x].eOType = OBJECT_TYPE::None;
				m_stTile[y][x].nOIndex = 0;
				m_stTile[y][x].eUType = UNIT_TYPE::None;
				m_stTile[y][x].nUIndex = 0;
			}
		}
	}	
	
	for (int i = NUM_TILE_V - 1; i >= 0; i--)
	{
		for (int j = 0; j < NUM_TILE_U; j++)
		{
			Sprite* pSprite = new Sprite(L"TileTerrain", NUM_TILE_U, NUM_TILE_V, i * NUM_TILE_U + j);
			m_vecTerrain.push_back(pSprite);
		}
	}

	for (int i = NUM_TILE_V - 1; i >= 0; i--)
	{
		for (int j = 0; j < NUM_TILE_U; j++)
		{
			Sprite* pSprite = new Sprite(L"Walls", NUM_TILE_U, NUM_TILE_V, i * NUM_TILE_U + j);
			m_vecWall.push_back(pSprite);
		}
	}

	for (int i = NUM_TILE_V - 1; i >= 0; i--)
	{
		for (int j = 0; j < NUM_TILE_U; j++)
		{
			Sprite* pSprite = new Sprite(L"Ceiling", NUM_TILE_U, NUM_TILE_V, i * NUM_TILE_U + j);
			m_vecCeiling.push_back(pSprite);
		}
	}

	for (int y = 0; y < NUM_TILE_Y; y++)
	{
		for (int x = 0; x < NUM_TILE_X; x++)
		{
			wstring wStr = L"TILE_INFO(" + to_wstring(y) + L" , " + to_wstring(x) + L" )";
			m_stTile[y][x] = g_pFileManager->LoadTileInfo(L"MAP001-1", wStr, L"TileInfo");
		}
	}
	m_pPlayer->SetTileInfo(m_stTile);

	for (int i = 0; i < 30; i++)
	{
		Enemy* enemy = new Enemy;
		enemy->Init();
		enemy->SetPosition(INFINITY, INFINITY);
		enemy->SetTargetPos(m_pPlayer->GetPosition());
		enemy->SetIsAlive(false);
		m_vecEnemy.push_back(enemy);
	}
	


	m_pInterface = new Interface();
	m_pInterface->Init();

	for (int y = 0; y < NUM_TILE_Y; y++)
	{
		for (int x = 0; x < NUM_TILE_X; x++)
		{
			if (m_stTile[y][x].eTType == TERRAIN_TYPE::Walkable)
				m_vecWalkableTile.push_back(POINT{ x,y });
		}
	}

	m_nWave = 1;

	m_fElapsedSummonTimer = 0.0f;
	m_fSummonDelay = 0.5f;
	m_nSummon = 0;

	m_fElapsedWaveTimer = 0.0f;
	m_fWaveDuration = 20.0f;
	g_fTimeSpeed = 0.0f;

	m_fElapsedBossDeadTimer = 0.0f;
	m_fBossDeadDuration = 5.0f;

	m_fElapsedBossDeadExplosionTimer = 0.0f;
	m_fBossDeadExplosionSpeed = 0.25f;
}

void PlayScene::Update()
{
	if (g_fTimeSpeed == 0.0f)
	{
		if (g_pKeyManager->IsOnceKeyDown(VK_ESCAPE))
			g_fTimeSpeed = 1.0f;
	}
	

	if (m_pPlayer)
		m_pPlayer->Update();
		
	if (m_pBoss)
	{
		m_pBoss->Update();
		m_pBossHpProgressBar->SetPos(HALFSIZEX - 300 + g_pCamera->GetPosition().x, 40 + g_pCamera->GetPosition().y);
		m_pBossHpProgressBar->SetProgress(m_pBoss->GetMaxHp(), m_pBoss->GetCurrHp(), true);
		m_pBossHpProgressBar->Update();

		if (!m_pBoss->GetIsAlive())
		{
			g_pCamera->SetTarget(m_pBoss->GetPosition());
			if (m_fElapsedBossDeadTimer >= m_fBossDeadDuration)
			{
				m_fElapsedBossDeadTimer = 0.0f;
				m_fElapsedBossDeadExplosionTimer = 0.0f;
				SAFE_DELETE(m_pBoss);
				SAFE_DELETE(m_pBossHpProgressBar);
			}
			else
			{
				m_fElapsedBossDeadTimer += g_pTimeManager->GetDeltaTime();
				
				if (m_fElapsedBossDeadExplosionTimer >= m_fBossDeadExplosionSpeed)
				{
					m_fElapsedBossDeadExplosionTimer = 0.0f;
					Effect* effect = new Effect;
					effect->Init();
					effect->m_fDurationTime = 1.0f;
					effect->m_eType = EffectType::Explosion;
					int rndX = (m_pBoss->GetHitCollider().transform2D.position.x - m_pBoss->GetHitCollider().transform2D.scale.x * 0.5f) + (rand() % 150);
					int rndY = (m_pBoss->GetHitCollider().transform2D.position.y - m_pBoss->GetHitCollider().transform2D.scale.y * 0.5f) + (rand() % 150);
					D3DXVECTOR2 v = {(float)rndX, (float)rndY};
					effect->m_transform2D.position.x = v.x;
					effect->m_transform2D.position.y = v.y;
					effect->m_transform2D.scale = { 64, 64 };
					g_pEffectManager->GetVecEffect()->push_back(effect);
				}
				else
					m_fElapsedBossDeadExplosionTimer += g_pTimeManager->GetDeltaTime();
			}
		}

	}

	for (int i = m_vecEnemy.size() - 1; i >= 0; i--)
	{
		m_vecEnemy[i]->Update();
		if (!m_vecEnemy[i]->GetIsAlive())
		{
			m_vecEnemy[i]->m_fElapsedDeadTimer += g_pTimeManager->GetDeltaTime();
			if (m_vecEnemy[i]->m_fElapsedDeadTimer >= m_vecEnemy[i]->m_fDeadTime)
			{
				m_vecEnemy[i]->SetPosition(INFINITY, INFINITY);
				m_vecEnemy[i]->Update();
			}
		}
	}

	g_pBulletManager->Update();
	if (!m_pBoss || m_pBoss->GetIsAlive())
	{
		UpdateTargetPos();
		g_pCamera->SetTarget(&m_vCameraTarget);
		
	}
	
	g_pCamera->Update();

	//Collision
	CollisionUpdate();

	//Interface
	m_pInterface->SetPlayerValues(m_pPlayer->GetCurrHp(), m_pPlayer->GetMaxHp(), m_pPlayer->GetNumBlank(), m_pPlayer->GetNumArmor(), 0);

	Wave_Update();
}

void PlayScene::Render()
{
	for (int y = 0; y < NUM_TILE_Y; y++)
	{
		for (int x = 0; x < NUM_TILE_X; x++)
		{
			switch (m_stTile[y][x].eTType)
			{
			case TERRAIN_TYPE::Walkable:
				m_vecTerrain[m_stTile[y][x].nTIndex]->SetConstantScale(D3DXVECTOR2(TILE_SIZE, TILE_SIZE));
				m_vecTerrain[m_stTile[y][x].nTIndex]->SetLBPosition(D3DXVECTOR2(x * TILE_SIZE, y * TILE_SIZE));
				m_vecTerrain[m_stTile[y][x].nTIndex]->UpdateNRender();
				break;

			case TERRAIN_TYPE::Wall:
				m_vecWall[m_stTile[y][x].nTIndex]->SetConstantScale(D3DXVECTOR2(TILE_SIZE, TILE_SIZE));
				m_vecWall[m_stTile[y][x].nTIndex]->SetLBPosition(D3DXVECTOR2(x * TILE_SIZE, y * TILE_SIZE));
				m_vecWall[m_stTile[y][x].nTIndex]->UpdateNRender();
				break;

			case TERRAIN_TYPE::Ceiling:
				m_vecCeiling[m_stTile[y][x].nTIndex]->SetConstantScale(D3DXVECTOR2(TILE_SIZE, TILE_SIZE));
				m_vecCeiling[m_stTile[y][x].nTIndex]->SetLBPosition(D3DXVECTOR2(x * TILE_SIZE, y * TILE_SIZE));
				m_vecCeiling[m_stTile[y][x].nTIndex]->UpdateNRender();
				break;
			}



			//m_vecObject[m_stTiles[y][x].nOIndex]->SetConstantScale(D3DXVECTOR2(TILE_SIZE, TILE_SIZE));
			//m_vecObject[m_stTiles[y][x].nOIndex]->SetLBPosition(D3DXVECTOR2(x * TILE_SIZE, y * TILE_SIZE));
			//m_vecObject[m_stTiles[y][x].nOIndex]->UpdateNRender();
			//
			//m_vecUnit[m_stTiles[y][x].nUIndex]->SetConstantScale(D3DXVECTOR2(TILE_SIZE, TILE_SIZE));
			//m_vecUnit[m_stTiles[y][x].nUIndex]->SetLBPosition(D3DXVECTOR2(x * TILE_SIZE, y * TILE_SIZE));
			//m_vecUnit[m_stTiles[y][x].nUIndex]->UpdateNRender();
		}
	}

	g_pBulletManager->Render();

	for (int i = m_vecEnemy.size() - 1; i >= 0; i--)
	{
		m_vecEnemy[i]->Render();
	}

	if (m_pBoss)
		m_pBoss->Render();

	if (m_pPlayer)
		m_pPlayer->Render();

	g_pEffectManager->UpdateNRender();

	if (m_pBossHpProgressBar && m_pBoss)
		m_pBossHpProgressBar->Render();

	if (m_pInterface)
	{
		if (m_pInterface->GetIsRenderInterface())
		{
			m_pInterface->Render();
		}
	}
}

void PlayScene::Release()
{
	g_pBulletManager->Release();
}

void PlayScene::Summon_Effect(POINT pt)
{
	Effect* effect = new Effect;
	effect->Init();
	effect->m_fDurationTime = 1.0f;
	effect->m_eType = EffectType::Summon;
	D3DXVECTOR2 v = GET_TILE_POSITION(pt);
	effect->m_transform2D.position.x = v.x;
	effect->m_transform2D.position.y = v.y;
	effect->m_transform2D.scale = { 200, 200 };
	g_pEffectManager->GetVecEffect()->push_back(effect);

	SummonInfo info;
	info.position = GET_TILE_POSITION(pt);
	info.m_fElapsedTime = 0.0f;
	m_vecSummonInfo.push_back(info);
}



void PlayScene::Summon_Boss()
{
	m_pBoss = new Boss;
	m_pBoss->Init();
	m_pBoss->SetTargetPos(m_pPlayer->GetPosition());
	m_pBoss->Update();

	m_pBossHpProgressBar = new ProgressBar(L"BossHpProgressBarBack", L"BossHpProgressBarFront", 3);
	m_pBossHpProgressBar->SetSize(600, 40);
	m_pBossHpProgressBar->SetPos(HALFSIZEX - 300 + g_pCamera->GetPosition().x, 40 + g_pCamera->GetPosition().y);
	m_pBossHpProgressBar->SetPaddingXY(57, 0);
	if (m_pBoss)
		m_pBossHpProgressBar->SetProgress(m_pBoss->GetMaxHp(), m_pBoss->GetCurrHp(), true);
	m_pBossHpProgressBar->Update();
}

void PlayScene::Wave_Update()
{

	if (m_nSummon < m_nWave + 3.0f)
	{
		if (m_fElapsedSummonTimer >= m_fSummonDelay)
		{
			m_fElapsedSummonTimer = 0.0f;
			int rnd = rand() % m_vecWalkableTile.size();
			Summon_Effect(m_vecWalkableTile[rnd]);

		}
		else
			m_fElapsedSummonTimer += g_pTimeManager->GetDeltaTime();

		for (int i = m_vecSummonInfo.size() - 1; i >= 0; i--)
		{
			if (m_vecSummonInfo[i].m_fElapsedTime >= 1.0f)
			{
				for (int j = 0; j < m_vecEnemy.size(); j++)
				{
					if (!m_vecEnemy[j]->GetIsAlive())
					{
						m_vecEnemy[j]->Init();
						m_vecEnemy[j]->SetPosition(m_vecSummonInfo[i].position);
						m_vecEnemy[j]->SetIsAlive(true);
						m_vecEnemy[j]->Update();
						m_nSummon++;
						m_vecSummonInfo.erase(m_vecSummonInfo.begin() + i);
						break;
					}
				}
				
			}
			else
				m_vecSummonInfo[i].m_fElapsedTime += g_pTimeManager->GetDeltaTime();
		}
	}


	if (m_nWave < 2)
	{
		if (m_fElapsedWaveTimer >= m_fWaveDuration)
		{
			if (m_nWave == 1)
			{
				if (!m_pBoss)
				{
					Summon_Boss();
					m_nWave++;
				}
			}
			else
			{
				m_nWave++;
				m_nSummon = 0;
				m_fElapsedWaveTimer = 0.0f;
			}

		}
		else
			m_fElapsedWaveTimer += g_pTimeManager->GetDeltaTime();
	}
}

