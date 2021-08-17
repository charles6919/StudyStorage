#include "pch.h"
#include "Boss.h"



Boss::Boss()
{
	m_pCAnimation = new Animation<BossState>;
	m_pChairAnimation = new Animation<BossChairState>;

	CreateClip(m_pCAnimation, L"BossBody", BossState::Idle, 4, 6, 4, 20, 0 * 4);
	CreateClip(m_pCAnimation, L"BossBody", BossState::Dead, 4, 6, 4, 20, 5 * 4);

	CreateClip(m_pChairAnimation, L"BossChair", BossChairState::Idle, 3, 7, 1, 1, 0 * 3);
	CreateClip(m_pChairAnimation, L"BossChair", BossChairState::Spin, 3, 7, 3, 20, 5 * 3);
	m_hitCollider.CreateCircle();
}

Boss::~Boss()
{
	m_hitCollider.Release();
	SAFE_DELETE(m_pChairAnimation);
}

void Boss::Init()
{
	m_transform2D.position = {NUM_TILE_X * TILE_SIZE * 0.5f, NUM_TILE_Y * TILE_SIZE * 0.5f};
	m_transform2D.scale = { 250, 250 };
	m_vMoveDir = { 0,0 };

	m_hitCollider.transform2D = m_transform2D;
	m_hitCollider.transform2D.scale = {100,100};
	m_eCurrPattern = Pattern::Tracking;
	m_eCState = BossState::Idle;
	m_eChairState = BossChairState::Idle;

	m_fElapsedPatternTimer = 0.0f;
	m_fPatternDuration = 1.0f;

	m_fElapsedShotTimer = 0.0f;
	m_fShotTime			= 1.0f;
	m_fMoveSpeed = 100.0f;

	m_fFloatingTimer = 0.0f;
	m_fFloatDirY = 1.0f;
	m_nHp = m_nMaxHp = 250;
	m_isAlive = true;
}

void Boss::ChangePattern()
{
	int rnd = rand() % ((int)(Pattern::Max)-1) + 1;
	m_eCurrPattern = (Pattern)rnd;
}

void Boss::Update()
{
	if (m_nHp <= 0)
		m_isAlive = false;

	D3DXVECTOR2 dir = *m_pTarget - m_transform2D.position;
	D3DXVec2Normalize(&m_vMoveDir, &dir);

	if (m_eCurrPattern == Pattern::Tracking)
	{
		m_fElapsedPatternTimer += g_pTimeManager->GetDeltaTime();
		if (m_fElapsedPatternTimer >= m_fPatternDuration)
		{
			ChangePattern();
			m_fElapsedPatternTimer = 0.0f;
			m_fPatternDuration = rand() % 3 + 1.0f;
		}
	}
	UpdatePattern();

	if (m_isSpining)
		m_eChairState = BossChairState::Spin;
	else
		m_eChairState = BossChairState::Idle;

	if (m_isAlive)
		m_eCState = BossState::Idle;
	else
	{
		m_eCState = BossState::Dead;
		m_eChairState = BossChairState::Idle;
	}
	
	Unit::Update();

	if (m_pChairAnimation)
	{
		m_pChairAnimation->SetPosition(m_transform2D.position);
		m_pChairAnimation->SetConstantSizeScale(m_transform2D.scale);
		m_pChairAnimation->Play(m_eChairState);
		m_pChairAnimation->Update();
	}

	m_hitCollider.transform2D.position = m_transform2D.position;
	m_hitCollider.Update();
		
}

void Boss::Render()
{

	if (m_pChairAnimation)
		m_pChairAnimation->Render();

	if(!m_isSpining)
		Unit::Render();

	m_hitCollider.Render();
}

void Boss::Move()
{
	m_transform2D.position.x += m_vMoveDir.x * m_fMoveSpeed * g_pTimeManager->GetDeltaTime();
	m_transform2D.position.y += m_vMoveDir.y * m_fMoveSpeed * g_pTimeManager->GetDeltaTime();
}

void Boss::UpdatePattern()
{
	if (m_isAlive)
	{
		switch (m_eCurrPattern)
		{
		case Pattern::Tracking:
			m_isSpining = false;
			Move();
			Floating();
			break;
		case Pattern::Shot_1:
			Move();
			Floating();
			m_fShotTime = 0.5f;
			m_nSettingCount = 4;
			m_fElapsedShotTimer += g_pTimeManager->GetDeltaTime();
			if (m_fElapsedShotTimer >= m_fShotTime)
			{
				m_fElapsedShotTimer = 0.0f;
				m_nCountShot++;
				for (int i = 0; i < 4; i++)
				{
					D3DXVECTOR2 pos = { m_pTarget->x - 100 + (50 * i), m_pTarget->y - 100 + (50 * i) };
					Bullet* bullet = new Bullet;
					bullet->Init();
					bullet->m_stInfo.transform.position = m_transform2D.position;
					bullet->m_stInfo.transform.scale = { 75,75 };
					bullet->m_stInfo.colTransform.position = m_transform2D.position;
					bullet->m_stInfo.colTransform.scale = { 30,30 };
					bullet->m_stInfo.damage = 1;
					bullet->m_stInfo.shape = BulletShape::Default;
					bullet->m_stInfo.type = BulletType::Enemy;
					bullet->m_stInfo.moveSpeed = 300.0f;
					bullet->m_stInfo.moveDir.x = cosf(GetAngleAsRadian(m_transform2D.position, pos));
					bullet->m_stInfo.moveDir.y = sinf(GetAngleAsRadian(m_transform2D.position, pos));
					Shot(bullet);
				}

				if (m_nCountShot >= m_nSettingCount)
				{
					m_nCountShot = 0;
					m_eCurrPattern = Pattern::Tracking;
				}
			}
			break;
		case Pattern::Shot_2:

			m_fShotTime = 0.5f;
			m_nSettingCount = 2;
			m_fElapsedShotTimer += g_pTimeManager->GetDeltaTime();
			if (m_fElapsedShotTimer >= m_fShotTime)
			{
				m_nCountShot++;
				m_fElapsedShotTimer = 0.0f;
				for (int i = 0; i < 36; i++)
				{
					Bullet* bullet = new Bullet;
					bullet->Init();
					bullet->m_stInfo.transform.position = m_transform2D.position;
					bullet->m_stInfo.transform.scale = { 50,50 };
					bullet->m_stInfo.colTransform.position = m_transform2D.position;
					bullet->m_stInfo.colTransform.scale = { 25,25 };
					bullet->m_stInfo.damage = 1;
					bullet->m_stInfo.shape = BulletShape::Default;
					bullet->m_stInfo.type = BulletType::Enemy;
					bullet->m_stInfo.moveSpeed = 200.0f;
					float angle = D3DX_PI * (i / 18.0f) + D3DX_PI * 0.25f * m_nCountShot;
					bullet->m_stInfo.moveDir.x = cosf(angle);
					bullet->m_stInfo.moveDir.y = sinf(angle);
					Shot(bullet);
				}
			}

			if (m_nCountShot >= m_nSettingCount)
			{
				m_nCountShot = 0;
				m_eCurrPattern = Pattern::Tracking;
			}
			break;
		case Pattern::Shot_3:

			m_fShotTime = 0.5f;
			m_nSettingCount = 12;
			m_fElapsedShotTimer += g_pTimeManager->GetDeltaTime();
			if (m_fElapsedShotTimer >= m_fShotTime)
			{
				m_isSpining = true;
				m_nCountShot++;
				m_fElapsedShotTimer = 0.0f;
				for (int i = 0; i < 8; i++)
				{
					Bullet* bullet = new Bullet;
					bullet->Init();
					bullet->m_stInfo.transform.position = m_transform2D.position;
					bullet->m_stInfo.transform.scale = { 50,50 };
					bullet->m_stInfo.colTransform.position = m_transform2D.position;
					bullet->m_stInfo.colTransform.scale = { 25,25 };
					bullet->m_stInfo.damage = 1;
					bullet->m_stInfo.shape = BulletShape::Default;
					bullet->m_stInfo.type = BulletType::Enemy;
					bullet->m_stInfo.moveSpeed = 150.0f;
					float angle = D3DX_PI * (i / 4.0f) + (D3DX_PI / 9) * (float)m_nCountShot;
					bullet->m_stInfo.moveDir.x = cosf(angle);
					bullet->m_stInfo.moveDir.y = sinf(angle);
					Shot(bullet);
				}
			}

			if (m_nCountShot >= m_nSettingCount)
			{
				m_nCountShot = 0.0f;
				m_eCurrPattern = Pattern::Tracking;
				for (int i = 0; i < 36; i++)
				{
					Bullet* bullet = new Bullet;
					bullet->Init();
					bullet->m_stInfo.transform.position = m_transform2D.position;
					bullet->m_stInfo.transform.scale = { 50,50 };
					bullet->m_stInfo.colTransform.position = m_transform2D.position;
					bullet->m_stInfo.colTransform.scale = { 25,25 };
					bullet->m_stInfo.damage = 1;
					bullet->m_stInfo.shape = BulletShape::Default;
					bullet->m_stInfo.type = BulletType::Enemy;
					bullet->m_stInfo.moveSpeed = 200.0f;
					float angle = D3DX_PI * (i / 18.0f) + D3DX_PI * 0.25f * m_nCountShot;
					bullet->m_stInfo.moveDir.x = cosf(angle);
					bullet->m_stInfo.moveDir.y = sinf(angle);
					Shot(bullet);
				}
			}
			break;
		}
	}
}

void Boss::Shot(Bullet* bullet)
{
	g_pBulletManager->GetBulletVector().push_back(bullet);
}

void Boss::SetTargetPos(D3DXVECTOR2* pos)
{
	if (pos)
		m_pTarget = pos;
}

void Boss::Floating()
{
	if (m_fFloatingTimer >= 1.5f)
	{
		m_fFloatingTimer = 0.0f;
		m_fFloatDirY *= -1.0f;
	}
	else
		m_fFloatingTimer += g_pTimeManager->GetDeltaTime();
	m_transform2D.position.y += m_fFloatDirY * FLOAT_SPEED * g_pTimeManager->GetDeltaTime();

}
