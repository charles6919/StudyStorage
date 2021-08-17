#include "stdafx.h"
#include "Player.h"

Player::Player()
{
	m_pAnimation		= NULL;
	m_pHitCollider		= NULL;
	m_pAggroCollider	= NULL;
	m_pHpBar			= NULL;

	m_stPistol._type = GunType::Pistol;
	m_stPistol._numMagazineAmmo = 12;

	m_stRifle._type = GunType::Rifle;
	m_stRifle._numMagazineAmmo = 30;

}

Player::~Player()
{
	SAFE_DELETE(m_pAnimation);
	SAFE_DELETE(m_pHitCollider);
	SAFE_DELETE(m_pAggroCollider);
	SAFE_DELETE(m_pHpBar);
}

void Player::Init()
{
	GameObject2D::Init();
	m_pTransform2D->SetPosition(MAPSIZEX *0.5f, MAPSIZEY * 0.5f);
	m_pTransform2D->SetScale(75, 75);
	m_pTransform2D->SetRotation(0,0,0);

	m_stPistol._numCurrAmmo = 12;
	m_stPistol._numAmmo = m_stPistol._numMagazineAmmo * 5;

	m_stRifle._numCurrAmmo = m_stRifle._numMagazineAmmo;
	m_stRifle._numAmmo = m_stRifle._numMagazineAmmo * 5;

	m_eState		= Player_DefaultState::Idle;
	m_eAniState		= PlayerState::HIdle;
	
	m_pCurrGun = &m_stPistol;
	m_nHp = 100;
	m_fMoveSpeed = 300.0f;
	m_fRotSpeed	= 3.0f;
	m_fShotTimer = 0.0f;
	m_fShotDelay = 0.3f;
	m_fReloadTimer = 0.0f;
	m_fReloadDelay = 1.0f;
	m_vShotPos = {m_pTransform2D->GetPosition().x - 30.0f, m_pTransform2D->GetPosition().y - 30.0f};
	m_vShotDir = { 0,0 };
	m_vMoveDir = {0,0};
	m_enableShot = true;
	m_isShoting = false;
	m_isReloading = false;
	m_isMoveing = false;
	m_isDead = false;

}

void Player::Update()
{
	if (m_nHp <= 0 && m_isDead == false)
	{
		m_isDead = true;
	}

	if (g_pKeyManager->isStayKeyDown(VK_LBUTTON))
	{
		if (m_enableShot && !m_isReloading)
		{
			//shot
			if (m_pCurrGun->_numCurrAmmo > 0)
			{
				Shot(D3DXVECTOR2(cosf(m_pTransform2D->GetRotation().z), sinf(m_pTransform2D->GetRotation().z)));
				m_enableShot = false;
				m_isShoting = true;
			}
			else
			{
				if (m_isReloading == false && m_pCurrGun->_numAmmo > 0 && m_pCurrGun->_numCurrAmmo <= 0)
				{
					m_isReloading = true;
				}
			}
		}
	}

	//ShotTimer
	if (m_enableShot == false)
	{
		if (m_fShotTimer >= m_fShotDelay)
		{
			g_pSoundManager->Stop("Shot");
			m_enableShot = true;
			m_isShoting = false;
			m_fShotTimer = 0.0f;
		}
		else
		{
			m_fShotTimer += g_pTimeManager->GetDeltaTime();
		}
	}



	if (g_pKeyManager->isOnceKeyDown('R'))
	{
		if (m_isReloading == false && m_pCurrGun->_numAmmo > 0 && m_pCurrGun->_numCurrAmmo < m_pCurrGun->_numMagazineAmmo)
		{
			m_isReloading = true;
		}
	}

	//ReloadTimer
	if (m_isReloading)
	{
		if (m_fReloadTimer >= m_fReloadDelay)
		{
			int numReloadAmmo = m_pCurrGun->_numMagazineAmmo - m_pCurrGun->_numCurrAmmo;

			if (m_pCurrGun->_numAmmo >= numReloadAmmo)
			{
				m_pCurrGun->_numCurrAmmo = m_pCurrGun->_numMagazineAmmo;
				m_pCurrGun->_numAmmo -= numReloadAmmo;
			}
			else
			{
				m_pCurrGun->_numCurrAmmo += numReloadAmmo;
				m_pCurrGun->_numAmmo = 0;
			}

			m_isReloading = false;
			m_fReloadTimer = 0.0f;
		}
		else
		{
			m_fReloadTimer += g_pTimeManager->GetDeltaTime();
		}
	}

	if (g_pKeyManager->isOnceKeyDown('1'))
	{
		m_pCurrGun = &m_stPistol;
		m_fShotDelay = 0.3f;
	}
	else if (g_pKeyManager->isOnceKeyDown('2'))
	{
		m_pCurrGun = &m_stRifle;
		m_fShotDelay = 0.15f;
	}



	if (g_pKeyManager->isStayKeyDown('D'))
	{
		m_vMoveDir.x = 1.0f;
		m_isMovingX = true;
	}
	else if (g_pKeyManager->isStayKeyDown('A'))
	{
		m_vMoveDir.x = -1.0f;
		m_isMovingX = true;
	}
	else
	{
		m_vMoveDir.x = 0.0f;
		m_isMovingX = false;
	}
	
	if (g_pKeyManager->isStayKeyDown('W'))
	{
		m_vMoveDir.y = 1.0f;
		m_isMovingY = true;
	}
	else if (g_pKeyManager->isStayKeyDown('S'))
	{
		m_vMoveDir.y = -1.0f;
		m_isMovingY = true;
	}
	else
	{
		m_vMoveDir.y = 0.0f;
		m_isMovingY = false;
	}

	if (m_isMovingX || m_isMovingY)
	{
		m_isMoveing = true;
		g_pSoundManager->Play("Run");
	}
	else
		m_isMoveing = false;

	if (m_isReloading)
	{
		m_fSoundRadius = STEPSOUND_R;
		m_eState = Player_DefaultState::Reload;
	}
	else if (m_isShoting)
	{
		g_pSoundManager->Play("Shot");
		m_fSoundRadius = GUNSOUND_R;
		m_eState = Player_DefaultState::Shot;
	}
	else if (m_isMoveing)
	{
		m_fSoundRadius = STEPSOUND_R;
		m_eState = Player_DefaultState::Run;
	}
	else
	{
		m_fSoundRadius = AGGROCOLLIDER_R;
		m_eState = Player_DefaultState::Idle;;
	}

	D3DXVec2Normalize(&m_vMoveDir, &m_vMoveDir);

	Move();
	Rotate();

	

	m_pAnimation->SetConstantSizeScale(m_pTransform2D->GetScale());
	m_pAnimation->SetRotation(m_pTransform2D->GetRotation());
	m_pAnimation->SetPosition(m_pTransform2D->GetPosition());
	switch (m_eState)
	{
	case Player_DefaultState::Idle:
		if (m_pCurrGun->_type == GunType::Pistol)
			m_eAniState = PlayerState::HIdle;
		else
			m_eAniState = PlayerState::RIdle;
		break;
	case Player_DefaultState::Run:
		if (m_pCurrGun->_type == GunType::Pistol)
			m_eAniState = PlayerState::HRun;
		else
			m_eAniState = PlayerState::RRun;
		break;
	case Player_DefaultState::Shot:
		if (m_pCurrGun->_type == GunType::Pistol)
			m_eAniState = PlayerState::HShot;
		else
			m_eAniState = PlayerState::RShot;
		break;
	case Player_DefaultState::Reload:
		if (m_pCurrGun->_type == GunType::Pistol)
			m_eAniState = PlayerState::HReload;
		else
			m_eAniState = PlayerState::RReload;
		break;
	default:
		break;
	}
	m_pAnimation->Play(m_eAniState);


	Transform2D t1;
	t1.SetScale(HITCOLLIDER_R , HITCOLLIDER_R);
	t1.SetRotation(m_pTransform2D->GetRotation());
	t1.SetPosition(m_pTransform2D->GetPosition());
	m_pHitCollider->SetTransform2D(t1);

	Transform2D t2;
	t2.SetScale(m_fSoundRadius, m_fSoundRadius);
	t2.SetRotation(m_pTransform2D->GetRotation());
	t2.SetPosition(m_pTransform2D->GetPosition());
	m_pAggroCollider->SetTransform2D(t2);

	m_pHpBar->SetSize(m_pTransform2D->GetScale().x, 15);
	m_pHpBar->SetPos(m_pTransform2D->GetPosition().x - m_pTransform2D->GetScale().x *0.5f, m_pTransform2D->GetPosition().y + m_pTransform2D->GetScale().y * 0.5f + 20.0f );
	m_pHpBar->SetProgress(PLAYER_MAXHP, m_nHp, true);
	
	if(m_pAnimation)
		m_pAnimation->Update();

	if(m_pHitCollider)
		m_pHitCollider->Update();

	if(m_pAggroCollider)
		m_pAggroCollider->Update();

	if(m_pHpBar)
		m_pHpBar->Update();
}

void Player::Render()
{
	if (m_pAnimation)
		m_pAnimation->Render();

	if (m_pHitCollider)
		m_pHitCollider->Render();

	if (m_pAggroCollider)
		m_pAggroCollider->Render();

	if (m_pHpBar)
		m_pHpBar->Render();

	g_pTextManager->IntRender(m_pCurrGun->_numCurrAmmo, 10 + g_pCamera->GetPosition().x, 10 + g_pCamera->GetPosition().y, 50, NumberType::White);
	g_pTextManager->WhiteTextRender("/", 120 + g_pCamera->GetPosition().x, 10 + g_pCamera->GetPosition().y, 50);
	g_pTextManager->IntRender(m_pCurrGun->_numAmmo, 180 + g_pCamera->GetPosition().x, 10 + g_pCamera->GetPosition().y, 50, NumberType::White);
}

void Player::Rotate()
{
	D3DXVECTOR2 fixedMouse(g_ptMouse.x + g_pCamera->GetPosition().x, g_ptMouse.y + g_pCamera->GetPosition().y);

	//Player Trnasform Rot
	float angle = GetRadian(m_pTransform2D->GetPosition(), fixedMouse);
	angle -= m_pTransform2D->GetRotation().z;

	float rotVolume = m_fRotSpeed * g_pTimeManager->GetDeltaTime();

	if (angle < 0.0f)
		angle += 2 * D3DX_PI;
	if (fabsf(angle) > rotVolume)
	{
		if (angle > D3DX_PI)
			m_pTransform2D->SetRotation(0, 0, m_pTransform2D->GetRotation().z - rotVolume);
		else
			m_pTransform2D->SetRotation(0, 0, m_pTransform2D->GetRotation().z + rotVolume);
	}
	if (m_pTransform2D->GetRotation().z < 0)
		m_pTransform2D->SetRotation(0, 0, m_pTransform2D->GetRotation().z + 2 * D3DX_PI);
	else if (m_pTransform2D->GetRotation().z > 2 * D3DX_PI)
		m_pTransform2D->SetRotation(0, 0, m_pTransform2D->GetRotation().z - 2 * D3DX_PI);


	//player ShotPos Rot
	//m_vShotPos.x = (m_vShotPos.x - m_pTransform2D->GetPosition().x) * cosf(m_pTransform2D->GetRotation().z) + m_pTransform2D->GetPosition().x;
	//m_vShotPos.y = (m_vShotPos.y - m_pTransform2D->GetPosition().y) * sinf(m_pTransform2D->GetRotation().z) + m_pTransform2D->GetPosition().y;
	m_vShotPos.x = m_pTransform2D->GetPosition().x + cosf((m_pTransform2D->GetRotation().z - D3DX_PI * 0.3f)) * 30.0f;
	m_vShotPos.y = m_pTransform2D->GetPosition().y + sinf((m_pTransform2D->GetRotation().z - D3DX_PI * 0.3f)) * 30.0f;
}

void Player::Move()
{
	m_pTransform2D->Translate2D(m_vMoveDir.x * m_fMoveSpeed * g_pTimeManager->GetDeltaTime(),
		m_vMoveDir.y * m_fMoveSpeed * g_pTimeManager->GetDeltaTime());

	if (m_pTransform2D->GetPosition().x < 0)
		m_pTransform2D->SetPosition(0, m_pTransform2D->GetPosition().y);
	else if (m_pTransform2D->GetPosition().x > MAPSIZEX)
		m_pTransform2D->SetPosition(MAPSIZEX, m_pTransform2D->GetPosition().y);

	if (m_pTransform2D->GetPosition().y < 0)
		m_pTransform2D->SetPosition(m_pTransform2D->GetPosition().x, 0);
	else if (m_pTransform2D->GetPosition().y > MAPSIZEY)
		m_pTransform2D->SetPosition(m_pTransform2D->GetPosition().x, MAPSIZEY);
}

void Player::Shot(D3DXVECTOR2 dest)
{
	Bullet* bullet = new Bullet;
	
	D3DXVECTOR2 fixedMouse(g_ptMouse.x + g_pCamera->GetPosition().x, g_ptMouse.y + g_pCamera->GetPosition().y);

	switch (m_pCurrGun->_type)
	{
	case GunType::Pistol:
		bullet->SettingBullet(m_vShotPos, fixedMouse, dest, BulletType::TRACKING , m_pTransform2D->GetRotation().z, 3);
		g_pBulletManager->AddBullet(bullet);
		break;
	case GunType::Rifle:
		bullet->SettingBullet(m_vShotPos, { 0,0 }, dest, BulletType::DIRECT, m_pTransform2D->GetRotation().z, 3);
		g_pBulletManager->AddBullet(bullet);
		break;
	default:
		break;
	}
	m_pCurrGun->_numCurrAmmo--;

}

