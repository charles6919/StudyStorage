#include "pch.h"
#include "Enemy.h"

void Enemy::AngleUpdate()
{
	if (m_isAlive)
	{


		m_fAngle = GetAngleAsRadian(m_transform2D.position, *m_pTarget);
		m_vMoveDir.x = cosf(m_fAngle);
		m_vMoveDir.y = sinf(m_fAngle);

		if (m_fAngle >= 0.0f && m_fAngle < D3DX_PI * 0.5f)
		{
			//RT
			m_eCharacterDir = Character_Dir::RT;
		}
		else if (m_fAngle < D3DX_PI)
		{
			//LT
			m_eCharacterDir = Character_Dir::LT;
		}
		else if (m_fAngle < D3DX_PI * 1.5f)
		{
			//LB
			m_eCharacterDir = Character_Dir::LB;
		}
		else
		{
			//RB
			m_eCharacterDir = Character_Dir::RB;
		}
	}

}

void Enemy::StateUpdate()
{
	if (!m_isAlive)
	{
		m_eEState = EnemyState::Die;
	}

	else if (m_vMoveDir.x != 0.0f || m_vMoveDir.y != 0.0f)
	{
		m_eEState = EnemyState::Run;
		Move();
	}
	else
	{
		m_eEState = EnemyState::Idle;
	}
}

Enemy::Enemy()
	:m_pGun(NULL),
	m_pTarget(NULL)
{
	m_HitCollider.CreateCircle();

	m_pCAnimation = new Animation<Enemy_AniState>;

	CreateClip(m_pCAnimation, L"Normal_Bullet_Idle", Enemy_AniState::Idle_LB, 2, 3, 2, 10, 0 * 2);
	CreateClip(m_pCAnimation, L"Normal_Bullet_Idle", Enemy_AniState::Idle_RB, 2, 3, 2, 10, 1 * 2);
	CreateClip(m_pCAnimation, L"Normal_Bullet_Idle", Enemy_AniState::Idle_T, 2, 3, 2, 10, 2 * 2);

	CreateClip(m_pCAnimation, L"Normal_Bullet_Run", Enemy_AniState::Run_LB, 7, 4, 6, 10, 0 * 7);
	CreateClip(m_pCAnimation, L"Normal_Bullet_Run", Enemy_AniState::Run_RB, 7, 4, 6, 10, 1 * 7);
	CreateClip(m_pCAnimation, L"Normal_Bullet_Run", Enemy_AniState::Run_LT, 7, 4, 7, 10, 2 * 7);
	CreateClip(m_pCAnimation, L"Normal_Bullet_Run", Enemy_AniState::Run_RT, 7, 4, 4, 10, 3 * 7);

	CreateClipOnce(m_pCAnimation, L"Normal_Bullet_Die", Enemy_AniState::Die, 4, 1, 4, 10, 0 * 4);

	//총 애니메이션 생성
	m_pGun = new Gun;
	Animation<Gun_State>* gAni = new Animation<Gun_State>;
	m_pGun->Init(GunCode::Enemy_Weapon_01);
	CreateClipOnce(gAni, L"Enemy_Weapon_01_R", Gun_State::Idle, 5, 2, 1, 16, 0 * 5);
	CreateClipOnce(gAni, L"Enemy_Weapon_01_R", Gun_State::Shot, 5, 2, 5, 16, 1 * 5);
	CreateClipOnce(gAni, L"Enemy_Weapon_01_L", Gun_State::Idle_L, 5, 2, 1, 16, 0 * 5);
	CreateClipOnce(gAni, L"Enemy_Weapon_01_L", Gun_State::Shot_L, 5, 2, 5, 16, 1 * 5);
	m_pGun->SetGunAnimation(gAni);

}

Enemy::~Enemy()
{
	m_HitCollider.Release();
}

void Enemy::Init()
{
	Unit::Init();

	m_transform2D.scale = { 64, 64 };
	m_eEState = EnemyState::Idle;

	m_isAttack = false;

	m_nMaxHp = 24;			//최대체력

	m_fElapsedShotTimer = 0.0f;
	m_fElapsedReloadTimer = 1.0f;

	m_enableToMove = true;
	m_isShooting = false;

	m_vMoveDir = {0,0};
	m_fMoveSpeed = 50.0f;

	m_transform2DGun.scale = { 64, 64 };
	m_fElapsedAttackTimer = 0.0f;
	m_fAttackCoolTime = 1.0f;

	m_fDeadTime = 3.0f;
	m_fElapsedDeadTimer = 0.0f;
}

void Enemy::Update()
{

	m_HitCollider.transform2D.position = { m_transform2D.position.x , m_transform2D.position.y - m_transform2D.scale.y * 0.25f };
	m_HitCollider.transform2D.scale = { 24,24 };
	m_HitCollider.Update();

	AngleUpdate();
	StateUpdate();

	if (m_eEState == EnemyState::Idle)
	{
		switch (m_eCharacterDir)
		{
		case Character_Dir::RT:
			m_eCState = Enemy_AniState::Idle_T;
			break;
		case Character_Dir::LT:
			m_eCState = Enemy_AniState::Idle_T;
			break;
		case Character_Dir::LB:
			m_eCState = Enemy_AniState::Idle_LB;
			break;
		case Character_Dir::RB:
			m_eCState = Enemy_AniState::Idle_RB;
			break;
		}
	}
	else if (m_eEState == EnemyState::Run)
	{
		switch (m_eCharacterDir)
		{
		case Character_Dir::RT:
			m_eCState = Enemy_AniState::Run_RT;
			break;
		case Character_Dir::LT:
			m_eCState = Enemy_AniState::Run_LT;
			break;
		case Character_Dir::LB:
			m_eCState = Enemy_AniState::Run_LB;
			break;
		case Character_Dir::RB:
			m_eCState = Enemy_AniState::Run_RB;
			break;
		}
	}
	else if (m_eEState == EnemyState::Die)
	{
		m_eCState = Enemy_AniState::Die;
	}

	

	Unit::Update();
	Rotate();
	if (m_isAlive)
	{
		m_fElapsedAttackTimer += g_pTimeManager->GetDeltaTime();
		if (m_fElapsedAttackTimer >= m_fAttackCoolTime)
		{
			m_isShooting = true;
			m_fElapsedAttackTimer = 0.0f;
		}
	}

	if (m_isShooting)
	{
		if(m_eCharacterDir == Character_Dir::RB || m_eCharacterDir == Character_Dir::RT)
			m_pGun->SetState(Gun_State::Shot);
		else
			m_pGun->SetState(Gun_State::Shot_L);

		Shot();
		m_isShooting = false;	
	}
	else
	{
		if (m_eCharacterDir == Character_Dir::RB || m_eCharacterDir == Character_Dir::RT)
			m_pGun->SetState(Gun_State::Idle);
		else
			m_pGun->SetState(Gun_State::Idle_L);
	}
	m_pGun->Update(m_transform2DGun);

}

void Enemy::Render()
{
	if (m_eCharacterDir == Character_Dir::RT || m_eCharacterDir == Character_Dir::LT)
	{
		
		m_pGun->Render();
		Unit::Render();
	}
	else
	{
		Unit::Render();
		m_pGun->Render();
	}
	m_HitCollider.Render();
}

void Enemy::Rotate()
{
	
	if (m_fAngle <= D3DX_PI * 0.5f || m_fAngle >= D3DX_PI * 1.5f)
	{
		m_transform2DGun.position.x = m_HitCollider.transform2D.position.x + GUN_DISTANCE;
		m_transform2DGun.position.y = m_HitCollider.transform2D.position.y;
	}
	else
	{
		m_transform2DGun.position.x = m_HitCollider.transform2D.position.x - GUN_DISTANCE;
		m_transform2DGun.position.y = m_HitCollider.transform2D.position.y;
	}


	m_transform2DGun.rotation.z = m_fAngle;
	
}

void Enemy::Move()
{
	m_transform2D.position.x += m_vMoveDir.x * m_fMoveSpeed * g_pTimeManager->GetDeltaTime();
	m_transform2D.position.y += m_vMoveDir.y * m_fMoveSpeed * g_pTimeManager->GetDeltaTime();
}

void Enemy::Dead()
{
	m_isAlive = false;
}

void Enemy::Shot()
{
	Bullet* p = new Bullet;
	p->Init();
	p->m_stInfo.transform.rotation = { 0,0, (float)(m_transform2DGun.rotation.z) };
	p->m_stInfo.transform.position = m_transform2DGun.position;
	p->m_stInfo.transform.scale = { 40,40 };
	p->m_stInfo.colTransform = m_transform2DGun;
	p->m_stInfo.colTransform.scale = { 50,50 };
	D3DXVECTOR2 v = { cosf(m_transform2DGun.rotation.z),sinf(m_transform2DGun.rotation.z) };
	D3DXVec2Normalize(&v, &v);
	p->m_stInfo.moveDir = v;
	p->m_stInfo.moveSpeed = 250.0f;
	p->m_stInfo.shape = BulletShape::Default;
	p->m_stInfo.type = BulletType::Enemy;
	
	g_pBulletManager->GetBulletVector().push_back(p);
}

void Enemy::Hit(int dmg)
{
	m_nHp -= dmg;
	if (m_nHp <= 0)
		Dead();
}

void Enemy::KnockBack(float power, D3DXVECTOR2 dir)
{
}

void Enemy::SetTileInfo(tagTileInfo tileInfo[NUM_TILE_Y][NUM_TILE_X])
{
	for (int y = 0; y < NUM_TILE_Y; y++)
	{
		for (int x = 0; x < NUM_TILE_X; x++)
		{
			m_stTileInfo[y][x] = tileInfo[y][x];
		}
	}
}

