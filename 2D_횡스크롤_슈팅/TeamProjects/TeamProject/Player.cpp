#include "stdafx.h"
#include "Player.h"

Player::Player()
{
	m_pAniCharacter		= NULL;
	m_pAniGun			= NULL;				
	m_pHitCollider		= NULL;
	m_pFootCollider		= NULL;

	{
		g_pTextureManager->AddTexture(L"Player", L"CupHead_Sprites.png");
		g_pTextureManager->AddTexture(L"Player_Gun_R", L"CupHead_HandGun_Idle_R.png");
		g_pTextureManager->AddTexture(L"Player_Gun_L", L"CupHead_HandGun_Idle_L.png");
	}
}

Player::~Player()
{
	SAFE_DELETE(m_pAniCharacter		);
	SAFE_DELETE(m_pAniGun			);
	SAFE_DELETE(m_pHitCollider		);
	SAFE_DELETE(m_pFootCollider		);

}

void Player::Init()
{
	Character::Init();

	m_pTransform2D->SetPosition(WINSIZEX * 0.5f, GroundY);
	m_pTransform2D->SetScale(128, 128);
	m_nHp = 3;
	m_pRigidBody->SetDrag(150);

	m_ePlayerState		= Player_State::Idle_R;
	m_eState			= IDLE;
	m_eGunState			= Gun_State::Idle_R;

	m_isJumping			= false;
	m_isShooting		= false;
	m_isSitting			= false;
	m_isHit				= false;

	m_fJumpPower		= 300.0f;
	m_fMoveSpeed		= 300.0f;

	m_fGunAngle			= 0.0f;
	m_enableToShot		= true;
	m_fShotTimer		= 0.0f;
	m_fShotDelay		= 0.25f;

	m_fInvinvibleTimer		= 0.0f;
	m_fInvincibleDuration	= 1.0f;
	m_isInvincible			= false;
	m_isTwinkleOn			= true;
	m_fTwinkleTimer			= 0.0f;
	m_fTwinkleDuration		= 0.05f;

}

void Player::Update()
{
	float dirX = m_vDir.x;
	ImGui::InputFloat("DirX", &dirX);

	if (m_fShotTimer >= m_fShotDelay)
	{
		m_fShotTimer = 0.0f;
		m_enableToShot = true;
	}
	m_fShotTimer += g_pTimeManager->GetDeltaTime();

	if (m_isInvincible)
	{
		if (m_fInvinvibleTimer >= m_fInvincibleDuration)
		{
			m_isHit = false;
			m_fInvinvibleTimer = 0.0f;
			m_isInvincible = false;
			m_pAniCharacter->SetColorAllClip(D3DXCOLOR(1, 1, 1, 1));
		}
		m_fInvinvibleTimer += g_pTimeManager->GetDeltaTime();
	}
	//키입력
	{
		if (m_isDead == false && m_isHit == false)
		{
			if (m_enableToShot)
			{
				if (g_pKeyManager->isStayKeyDown(VK_LBUTTON))
				{
					m_isShooting = true;
				}
			}

			if (g_pKeyManager->isStayKeyDown('D'))
			{
				m_eDir = CharacterDir::RIGHT;
				m_isRunning = true;
			}
			else if (g_pKeyManager->isStayKeyDown('A'))
			{
				m_eDir = CharacterDir::LEFT;
				m_isRunning = true;
			}
			else
			{
				m_isRunning = false;
			}

			if (m_pRigidBody->GetIsFalling() == false)
			{
				if (g_pKeyManager->isOnceKeyDown(VK_SPACE))
				{
					m_isJumping = true;
				}
			}

			if (g_pKeyManager->isOnceKeyDown(VK_F3))
			{
				m_isHit = true;
			}
		}
	}

	if (m_isDead)
	{
		m_eState = STATE::DIE;
	}
	else
	{
		if (m_isHit)
		{
			if (!m_isInvincible)
			{
				this->TakeDmg(1);
				m_pRigidBody->SetForce(D3DXVECTOR2( -m_vDir.x * 150.0f, 100.0f));
				m_pRigidBody->SetIsFalling(true);
				m_isInvincible = true;
				if (m_nHp <= 0)
				{
					m_isDead = true;
				}

			}
		}
		else
		{
			if (m_isJumping)
			{
				Jump();
			}

			m_pHitCollider->GetTransform2D().SetScale(STAND_SCALE);

			if (m_isShooting)
			{
				Shot();
				m_isShooting = false;
				m_enableToShot = false;
				m_fShotTimer = 0.0f;
			}

			if (m_isRunning)
			{
				Move();
			}
		}
	}

	if (m_isInvincible)
	{
		if (m_fTwinkleTimer >= m_fTwinkleDuration)
		{
			m_fTwinkleTimer = 0.0f;
			if(m_isTwinkleOn)
				m_pAniCharacter->SetColor(D3DXCOLOR(1, 1, 1, 1));
			else
				m_pAniCharacter->SetColor(D3DXCOLOR(1, 1, 1, 0.3f));
			m_isTwinkleOn = !m_isTwinkleOn;
		}
		m_fTwinkleTimer += g_pTimeManager->GetDeltaTime();
	}

	//Animation 분기점
	if (m_isHit)
	{
		m_eState = STATE::Hit;
	}
	else if (m_pRigidBody->GetIsFalling() == true)
	{
		if (m_pRigidBody->GetForce().y >= 0)
		{
			m_eState = STATE::JumpUp;
		}
		else
		{
			m_eState = STATE::Fall;
		}
	}
	else if (m_isRunning)
	{
		m_eState = STATE::RUN;
	}
	else
	{
		m_eState = STATE::IDLE;
	}

	Character::Update();

	if (m_pTransform2D->GetPosition().y <= GroundY)
	{
		m_pRigidBody->SetIsFalling(false);
	}

	m_pAniCharacter->SetConstantSizeScale(m_pTransform2D->GetScale());
	m_pAniCharacter->SetPosition(m_pTransform2D->GetPosition());
	
	m_pHitCollider->GetTransform2D().SetPosition(m_pTransform2D->GetPosition().x, m_pTransform2D->GetPosition().y - 15);

	m_pFootCollider->GetTransform2D().SetScale(20, 6);
	m_pFootCollider->GetTransform2D().SetPosition(m_pAniCharacter->GetPosition().x ,
		m_pAniCharacter->GetPosition().y - m_pTransform2D->GetScale().y * 0.5f + m_pFootCollider->GetTransform2D().GetScale().y * 0.5f);

	m_fGunAngle = GetRadianAngle(m_pHitCollider->GetTransform2D().GetPosition(), D3DXVECTOR2(g_ptMouse.x, g_ptMouse.y));

	m_pAniGun->SetConstantSizeScale(m_pTransform2D->GetScale());
	m_pAniGun->SetRotation(D3DXVECTOR3(0, 0, m_fGunAngle));
	m_pAniGun->SetPosition(m_pTransform2D->GetPosition().x , m_pTransform2D->GetPosition().y - 24);

	switch (m_eState)
	{
	case IDLE:
	{
		if (m_eDir == CharacterDir::RIGHT)
		{
			m_ePlayerState = Player_State::Idle_R;
		}
		else
		{
			m_ePlayerState = Player_State::Idle_L;
		}
	}
		break;
	case RUN:
	{
		if (m_eDir == CharacterDir::RIGHT)
		{
			m_ePlayerState = Player_State::Run_R;
		}
		else
		{
			m_ePlayerState = Player_State::Run_L;
		}
	}
		break;
	case JumpUp:
	{
		if (m_eDir == CharacterDir::RIGHT)
		{
			m_ePlayerState = Player_State::JumpUp_R;
		}
		else
		{
			m_ePlayerState = Player_State::JumpUp_L;
		}
	}
		break;
	case Fall:
	{
		if (m_eDir == CharacterDir::RIGHT)
		{
			m_ePlayerState = Player_State::Fall_R;
		}
		else
		{
			m_ePlayerState = Player_State::Fall_L;
		}
	}
		break;
	case Hit:
	{
		if (m_eDir == CharacterDir::RIGHT)
		{
			m_ePlayerState = Player_State::Hit_R;
		}
		else
		{
			m_ePlayerState = Player_State::Hit_L;
		}
	}
		break;
	case DIE:
	{
		
	}
		break;
	default:
		break;
	}

	if (m_fGunAngle > D3DX_PI * 0.5f && m_fGunAngle < D3DX_PI * 1.5f)
	{
		m_eGunState = Gun_State::Idle_L;
	}
	else
	{
		m_eGunState = Gun_State::Idle_R;
	}

	
	m_pAniCharacter->Play(m_ePlayerState);
	m_pAniGun->Play(m_eGunState);

	if (m_pTransform2D->GetPosition().x < 0)
		m_pTransform2D->SetPosition(0.0f, m_pTransform2D->GetPosition().y);
	if (m_pTransform2D->GetPosition().x > WINSIZEX)
		m_pTransform2D->SetPosition(WINSIZEX, m_pTransform2D->GetPosition().y);

	SAFE_UPDATE(m_pAniCharacter		);
	SAFE_UPDATE(m_pAniGun			);
	SAFE_UPDATE(m_pHitCollider		);
	SAFE_UPDATE(m_pFootCollider		);

}

void Player::Render()
{
	SAFE_RENDER(m_pAniGun);
	SAFE_RENDER(m_pAniCharacter);
	SAFE_RENDER(m_pHitCollider);
	SAFE_RENDER(m_pFootCollider);
}

void Player::Jump()
{
	m_pRigidBody->SetIsFalling(true);
	m_pRigidBody->SetForceY(m_fJumpPower);
	m_isJumping = false;
}

void Player::Shot()
{
	D3DXVECTOR2 dir = D3DXVECTOR2(g_ptMouse.x, g_ptMouse.y) - m_pAniGun->GetPosition();
	D3DXVec2Normalize(&dir, &dir);
	Transform2D* tr = new Transform2D;
	tr->SetPosition(m_pAniGun->GetPosition());
	tr->SetScale(10, 10);
	Bullet* bullet = new Bullet;
	bullet->SetBulletType(Bullet_Type::Player_Normal);
	bullet->SetDamage(1);
	bullet->SetMoveDir(dir);
	bullet->SetMoveSpeed(500.0f);
	bullet->SetTransform2D(tr);
	g_pBulletManager->AddPlayerBullet(bullet);

}