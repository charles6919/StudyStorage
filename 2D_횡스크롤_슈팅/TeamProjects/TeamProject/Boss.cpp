#include "stdafx.h"
#include "Boss.h"
#include "Player.h"

Boss::Boss()
{
	m_pAniCharacter = NULL;
	m_pHitCollider	= NULL;
	m_pHpBar		= NULL;
	m_pPlayer		= NULL;

	{
		g_pTextureManager->AddTexture(L"Boss",L"MetalSlug2_Boss_Idle.png");
		g_pTextureManager->AddTexture(L"Boss_Die", L"MetalSlug2_Boss_Die.png");
	}
}

Boss::~Boss()
{
	SAFE_DELETE(m_pAniCharacter );
	SAFE_DELETE(m_pHitCollider	);
	SAFE_DELETE(m_pHpBar		);
}

void Boss::Init()
{
	Character::Init();

	m_pTransform2D->SetPosition(WINSIZEX * 0.5f, WINSIZEY + 500.0f);
	m_pTransform2D->SetScale(880, 380);

	m_eBossState				= Boss_State::Flying;
	m_eAttackPattern			= AttackPattern::Start;
	m_eShotPattern				= ShotPattern::ShotTarget;

	for (int i = 0; i < 3; i++)
	{
		m_vBulletSpot[i] = m_pTransform2D->GetPosition();
	}
	
	for (int i = 0; i < 2; i++)
	{
		m_vLaserSpot[i] = m_pTransform2D->GetPosition();
	}

	m_vVia						= { 0,0 };
	m_vTarget					= { 0,0 };
	m_nHp = 100;
	m_vDir = { 1,0 };
	m_fMoveSpeed = 100.0f;

	m_fShotTimer				= 0.0f;
	m_fShotDelay				= 0.0f;

	m_fFlyPatternTimer			= 0.0f;
	m_fFlyPatternDuration		= 0.0f;

	m_fShotPatternTimer			= 0.0f;
	m_fShotPatternDuration		= 0.0f;

	m_isFlyUp					= false;
	m_isHit						= false;
	m_fFloatTimer				= 0.0f;
	m_fFloatSpeed				= 100.0f;

	m_isTwinkleOn				= false;
	m_fTwinkleChangeDuration	= 0.05f;
	m_fTwinkleChangeTimer		= m_fTwinkleChangeDuration;
	m_fTwinkleTimer				= 0.0f;
	m_fTwinkleDuration			= 0.5f;
	m_isGameClear				= false;

	m_vColor = { 1,1,1,1 };

	m_pHpBar->SetSize(300, 30);
	m_pHpBar->Init();

	m_pAniCharacter->SetColorAllClip(m_vColor);
}

void Boss::Update()
{
	if (m_isDead)
	{
		m_eBossState = Boss_State::Die;

		if (m_pTransform2D->GetPosition().y > WINSIZEY * 0.5f)
		{
			m_pTransform2D->TransformYAdd(-m_fFloatSpeed * g_pTimeManager->GetDeltaTime());
		}
		else
		{
			
			if (m_vColor.a > 0.0f)
			{
				m_vColor.a -= g_pTimeManager->GetDeltaTime();
			}
			else
			{
				m_vColor.a = 0.0f;
			}
			m_pAniCharacter->SetColor(m_vColor);

			if (m_vColor.a == 0.0f)
			{
				m_pTransform2D->SetPosition(OBJECT_DEFAULTV);
				m_isGameClear = true;
			}

		}
	}
	else
	{
		if (m_eAttackPattern == AttackPattern::Start)
		{
			if (m_pTransform2D->GetPosition().y > FLOATUP)
			{
				m_pTransform2D->TransformYAdd(-m_fFloatSpeed * g_pTimeManager->GetDeltaTime());
			}
			else
			{
				m_eAttackPattern = AttackPattern::ShotBullet;
			}
		}
		else if (m_eAttackPattern == AttackPattern::ShotBullet)
		{

			m_fFloatTimer += g_pTimeManager->GetDeltaTime();
			Float();

			if (m_pTransform2D->GetPosition().x <= m_pTransform2D->GetScale().x * 0.3f || m_pTransform2D->GetPosition().x >= WINSIZEX - m_pTransform2D->GetScale().x * 0.3f)
				m_vDir.x = -1 * m_vDir.x;
			m_pTransform2D->TransformXAdd(m_vDir.x * m_fMoveSpeed * g_pTimeManager->GetDeltaTime());

			if (m_fShotTimer >= m_fShotDelay)
			{
				m_fShotTimer = 0.0f;
				Shot();
			}
			m_fShotTimer += g_pTimeManager->GetDeltaTime();


			ImGui::InputFloat("ShotTimer", &m_fShotTimer);

			if (m_fShotPatternTimer >= m_fShotPatternDuration)
			{
				m_fShotPatternTimer = 0.0f;
				SettingShotPattern((ShotPattern)(rand() % (int)(ShotPattern::Max)));
			}
			m_fShotPatternTimer += g_pTimeManager->GetDeltaTime();
		}
		else if (m_eAttackPattern == AttackPattern::Lazer_L)
		{

		}
		else if (m_eAttackPattern == AttackPattern::Lazer_R)
		{

		}

		for (int i = 0; i < 3; i++)
		{
			m_vBulletSpot[i] = D3DXVECTOR2(m_pTransform2D->GetPosition().x - 200 + i * 200, m_pTransform2D->GetPosition().y);
		}

		for (int i = 0; i < 2; i++)
		{
			m_vLaserSpot[i] = m_pTransform2D->GetPosition();
		}

		if (m_isHit)
		{
			TakeDmg(1);
			m_isHit = false;
			m_isTwinkleOn = true;
		}

		if (m_isTwinkleOn)
		{
			if (m_fTwinkleTimer >= m_fTwinkleDuration)
			{
				m_isTwinkleOn = false;
				m_fTwinkleTimer = 0.0f;
				m_fTwinkleChangeTimer = m_fTwinkleChangeDuration;
				m_pAniCharacter->SetColor(D3DXCOLOR(1, 1, 1, 1));
			}
			else
			{
				if (m_fTwinkleChangeTimer >= m_fTwinkleChangeDuration)
				{
					m_fTwinkleChangeTimer = 0.0f;
					if (m_isColorOff)
					{
						m_pAniCharacter->SetColor(D3DXCOLOR(1, 1, 1, 0.6f));
						m_isColorOff = false;
					}
					else
					{
						m_pAniCharacter->SetColor(D3DXCOLOR(1, 1, 1, 1));
						m_isColorOff = true;
					}
				}
				else
				{
					m_fTwinkleChangeTimer += g_pTimeManager->GetDeltaTime();
				}
				m_fTwinkleTimer += g_pTimeManager->GetDeltaTime();
			}

		}
	}
	if (m_nHp <= 0)
	{
		m_nHp = 0;
		m_isDead = true;
	}

	m_pAniCharacter->SetPosition(m_pTransform2D->GetPosition());
	m_pAniCharacter->SetConstantSizeScale(m_pTransform2D->GetScale());
	m_pHitCollider->GetTransform2D().SetScale(m_pTransform2D->GetScale().x * 0.5f, m_pTransform2D->GetScale().y * 0.5f);
	m_pHitCollider->GetTransform2D().SetPosition(m_pTransform2D->GetPosition());
	
	m_pHpBar->SetProgress(100.0f, m_nHp, true);
	m_pHpBar->SetPos(m_pTransform2D->GetPosition().x - 150.0f , m_pTransform2D->GetPosition().y - 250);

	m_pAniCharacter->Play(m_eBossState);

	SAFE_UPDATE(m_pAniCharacter	);
	SAFE_UPDATE(m_pHitCollider	);
	m_pHpBar->Update();
}

void Boss::Render()
{
	SAFE_RENDER(m_pAniCharacter);
	SAFE_RENDER(m_pHitCollider);
	SAFE_RENDER(m_pHpBar);
}

void Boss::Shot()
{

	Bullet* bullet	= NULL;
	Transform2D* tr	= NULL;

	switch (m_eShotPattern)
	{
	case ShotPattern::ShotDown:
	{
		for (int i = 0; i < 3; i++)
		{
			bullet = new Bullet;
			tr = new Transform2D;
			tr->SetPosition(m_vBulletSpot[i]);
			tr->SetScale(D3DXVECTOR2(BOSS_BULLETSIZE, BOSS_BULLETSIZE));
			bullet->SetTransform2D(tr);
			bullet->SetBulletType(Bullet_Type::Enemy_Normal);
			bullet->SetDamage(1);
			bullet->SetMoveSpeed(250.0f);
			bullet->SetMoveDir(D3DXVECTOR2(0, -1));
			g_pBulletManager->AddEnemyBullet(bullet);
		}
		break;
	}
	case ShotPattern::ShotRandom:
		for (int i = 0; i < 3; i++)
		{
			bullet = new Bullet;
			tr = new Transform2D;
			tr->SetPosition(m_vBulletSpot[i]);
			tr->SetScale(D3DXVECTOR2(BOSS_BULLETSIZE, BOSS_BULLETSIZE));
			bullet->SetTransform2D(tr);
			bullet->SetBulletType(Bullet_Type::Enemy_Normal);
			bullet->SetDamage(1);
			bullet->SetMoveSpeed(250.0f);
			D3DXVECTOR2 v;
			if (rand() % 2)
			{
				v = { 1.0f / (rand() % 18 + 1.0f), -1 };
			}
			else
			{
				v = { -1.0f / (rand() % 18 + 1.0f), -1 };
			}
			D3DXVec2Normalize(&v, &v);
			bullet->SetMoveDir(v);

			g_pBulletManager->AddEnemyBullet(bullet);
			
		}
		break;
	case ShotPattern::ShotTarget:
		for (int i = 0; i < 3; i++)
		{
			bullet = new Bullet;
			tr = new Transform2D;
			tr->SetPosition(m_vBulletSpot[i]);
			tr->SetScale(D3DXVECTOR2(BOSS_BULLETSIZE, BOSS_BULLETSIZE));
			bullet->SetTransform2D(tr);
			bullet->SetBulletType(Bullet_Type::Enemy_Curve);
			bullet->SetDamage(1);
			bullet->SetStart(m_vBulletSpot[i]);
			bullet->SetTarget(m_pPlayer->GetHitCollider()->GetTransform2D().GetPosition());
			if(rand() % 2)
				bullet->SetVia(D3DXVECTOR2(m_vBulletSpot[i].x + 100.0f, m_vBulletSpot[i].y + 100.0f));
			else
				bullet->SetVia(D3DXVECTOR2(m_vBulletSpot[i].x - 100.0f, m_vBulletSpot[i].y + 100.0f));
			bullet->SetTime(1.5f);
			g_pBulletManager->AddEnemyBullet(bullet);
		}
		break;
	default:
		break;
	}
}

void Boss::Float()
{
	if (m_isFlyUp)
	{
		m_pTransform2D->SetPosition(m_pTransform2D->GetPosition().x, 
			LinearInterpolation(FLOATDOWN, FLOATUP, m_fFloatTimer/ FLOATDURATION));
	}
	else
	{
		m_pTransform2D->SetPosition(m_pTransform2D->GetPosition().x,
			LinearInterpolation(FLOATUP, FLOATDOWN, m_fFloatTimer / FLOATDURATION));
	}

	if (m_fFloatTimer >= FLOATDURATION)
	{
		m_fFloatTimer = 0.0f;
		m_isFlyUp = !m_isFlyUp;
	}
}

void Boss::SettingShotPattern(ShotPattern pattern)
{
	m_eShotPattern = pattern;
	switch (m_eShotPattern)
	{
	case ShotPattern::ShotDown:
		m_fShotDelay = SHOTDOWNDELAY;
		m_fShotPatternDuration = 5.0f;
		break;
	case ShotPattern::ShotRandom:
		m_fShotDelay = SHOTRANDOMDELAY;
		m_fShotPatternDuration = 5.0f;
		break;
	case ShotPattern::ShotTarget:
		m_fShotDelay = SHOTTARGETDELAY;
		m_fShotPatternDuration = 5.0f;
		break;
	}

	m_fShotTimer = 0.0f;
	m_fShotPatternTimer = 0.0f;
}
