#include "pch.h"
#include "Player.h"


Player::Player()
{
	m_HitCollider.CreateCircle();
	m_AttackCollider.CreateCircle();

	//캐릭터 애니메이션 생성
	m_pCAnimation = new Animation<Player_AniState>;

	CreateClip(m_pCAnimation, L"Player_Idle", Player_AniState::Idle_R, 6, 4, 6, 6, 0 * 6);
	CreateClip(m_pCAnimation, L"Player_Idle", Player_AniState::Idle_T, 6, 4, 6, 6, 1 * 6);
	CreateClip(m_pCAnimation, L"Player_Idle", Player_AniState::Idle_L, 6, 4, 6, 6, 2 * 6);
	CreateClip(m_pCAnimation, L"Player_Idle", Player_AniState::Idle_B, 6, 4, 6, 6, 3 * 6);

	CreateClip(m_pCAnimation, L"Player_Run", Player_AniState::Run_RT, 6, 6, 6, 10, 0 * 6);
	CreateClip(m_pCAnimation, L"Player_Run", Player_AniState::Run_RB, 6, 6, 6, 10, 1 * 6);
	CreateClip(m_pCAnimation, L"Player_Run", Player_AniState::Run_LT, 6, 6, 6, 10, 2 * 6);
	CreateClip(m_pCAnimation, L"Player_Run", Player_AniState::Run_LB, 6, 6, 6, 10, 3 * 6);
	CreateClip(m_pCAnimation, L"Player_Run" , Player_AniState::Run_B, 6, 6, 6, 10, 4 * 6);
	CreateClip(m_pCAnimation, L"Player_Run" , Player_AniState::Run_T, 6, 6, 6, 10, 5 * 6);

	CreateClip(m_pCAnimation, L"Player_Evade", Player_AniState::Evade_RT , 11, 6, 11, 11, 0 * 11);
	CreateClip(m_pCAnimation, L"Player_Evade", Player_AniState::Evade_RB , 11, 6, 11, 11, 1 * 11);
	CreateClip(m_pCAnimation, L"Player_Evade", Player_AniState::Evade_LT , 11, 6, 11, 11, 2 * 11);
	CreateClip(m_pCAnimation, L"Player_Evade", Player_AniState::Evade_LB , 11, 6, 11, 11, 3 * 11);
	CreateClip(m_pCAnimation, L"Player_Evade" , Player_AniState::Evade_T , 11, 6, 11, 11, 4 * 11);
	CreateClip(m_pCAnimation, L"Player_Evade" , Player_AniState::Evade_B , 11, 6, 11, 11, 5 * 11);

	//총 애니메이션 생성
	Gun* gun = new Gun;
	Animation<Gun_State>* gAni = new Animation<Gun_State>;
	gun->Init(GunCode::Sword);
	CreateClipOnce(gAni, L"Sword", Gun_State::Idle,   7, 3, 1, 16, 0 * 7);
	CreateClipOnce(gAni, L"Sword", Gun_State::Shot,   7, 3, 7, 16, 1 * 7);
	CreateClipOnce(gAni, L"Sword", Gun_State::Reload, 7, 3, 1, 16, 2 * 7);
	gun->SetGunAnimation(gAni);

	m_vecGun.push_back(gun);
	
}

Player::~Player()
{
	SAFE_DELETE(m_pCAnimation);

	for (int i = 0; i < m_vecGun.size(); i++)
	{
		SAFE_DELETE(m_vecGun[i]);
	}
	m_vecGun.clear();

	for (int i = 0; i < m_vecActiveItem.size(); i++)
	{
		SAFE_DELETE(m_vecActiveItem[i]);
	}
	m_vecActiveItem.clear();

	for (int i = 0; i < m_vecPassiveItem.size(); i++)
	{
		SAFE_DELETE(m_vecPassiveItem[i]);
	}
	m_vecPassiveItem.clear();

	m_HitCollider.Release();
	m_AttackCollider.Release();
}


void Player::AngleUpdate()
{
	m_fAngle = GetAngleAsRadian(m_transform2D.position, D3DXVECTOR2(g_ptMouse.x + g_pCamera->GetPosition().x, g_ptMouse.y + g_pCamera->GetPosition().y));
	if (m_ePState != Player_State::Evade)
	{
		if (m_fAngle >= 0.0f && m_fAngle < D3DX_PI * 0.33f)
		{
			//RT
			m_eCharacterDir = Character_Dir::RT;
		}
		else if (m_fAngle < D3DX_PI * 0.66f )
		{
			//T
			m_eCharacterDir = Character_Dir::T;
		}
		else if (m_fAngle < D3DX_PI)
		{
			//LT
			m_eCharacterDir = Character_Dir::LT;
		}
		else if(m_fAngle < D3DX_PI * 1.33f)
		{
			//LB
			m_eCharacterDir = Character_Dir::LB;
		}
		else if (m_fAngle < D3DX_PI * 1.66f)
		{
			//B
			m_eCharacterDir = Character_Dir::B;
		}
		else
		{
			//RB
			m_eCharacterDir = Character_Dir::RB;
		}
	}
}

void Player::ItemUpdate(int code)
{
	switch (code)
	{
		
	}
}

void Player::GunUpdate(GunCode code)
{
	switch (code)
	{

	}
}

void Player::KeyboardUpdate()
{
	if (g_pKeyManager->IsOnceKeyDown(VK_NUMPAD1))
	{
		if (m_nHp == m_nMaxHp)
		{
			m_nMaxHp += 2;
			m_nHp++;
		}
		else
			m_nHp++;
	}

	if (m_enableToMove)
	{
		if (g_pKeyManager->IsStayKeyDown('W'))
		{
			m_vMoveDir.y = 1;
		}
		else if (g_pKeyManager->IsStayKeyDown('S'))
		{
			m_vMoveDir.y = -1;
		}
		else
		{
			m_vMoveDir.y = 0;
		}

		if (g_pKeyManager->IsStayKeyDown('A'))
		{
			m_vMoveDir.x = -1;
		}
		else if (g_pKeyManager->IsStayKeyDown('D'))
		{
			m_vMoveDir.x = +1;
		}
		else
		{
			m_vMoveDir.x = 0;
		}

		D3DXVec2Normalize(&m_vMoveDir, &m_vMoveDir);
	}

	if (g_pKeyManager->IsOnceKeyDown(VK_LSHIFT))
	{
		if (m_vecActiveItem.size() - 1 > m_nCurrIndexSlot)
			m_nCurrIndexSlot++;
		else
			m_nCurrIndexSlot = 0;
	}

	if (g_pKeyManager->IsOnceKeyDown(VK_SPACE))
	{
		if(m_vecActiveItem.size() > 0)
			UseActiveItem();
	}

	
}

void Player::AttackColliderUpdate()
{
	D3DXVECTOR2 v;
	float angle = GetAngleAsRadian(m_transform2D.position, D3DXVECTOR2{ g_ptMouse.x + g_pCamera->GetPosition().x , g_ptMouse.y + g_pCamera->GetPosition().y });
	v.x = m_transform2D.position.x + (cosf(angle)) * 50;
	v.y = m_transform2D.position.y + (sinf(angle)) * 50;
	m_AttackCollider.transform2D.position = v;
	m_AttackCollider.Update();
}

void Player::MouseUpdate()
{
	AngleUpdate();

	if (g_pKeyManager->IsOnceKeyDown(VK_RBUTTON))
	{
		if (!m_isEvading && !(m_vMoveDir.x == 0.0f && m_vMoveDir.y == 0.0f))
		{
			m_isEvading = true;
			m_enableToMove = false;
		}
	}

	if (!m_isEvading && !m_isShooting)
	{
		if (g_pKeyManager->IsStayKeyDown(VK_LBUTTON))
		{
			m_isShooting = true;
		}
	}
}

void Player::StateUpdate()
{
	if (!m_isAlive)
	{
		m_ePState = Player_State::Die;
	}
	if (m_isEvading)
	{
		m_ePState = Player_State::Evade;
		Evade();
	}
	else if (m_vMoveDir.x != 0.0f || m_vMoveDir.y != 0.0f)
	{
		m_ePState = Player_State::Run;
		Move();
	}
	else
	{
		m_ePState = Player_State::Idle;
	}

	
}

void Player::Init()
{
	Unit::Init();

	m_transform2D.scale = { 64, 64 };
	m_ePState = Player_State::Idle;

	
	m_fElapsedEvadeTimer	= 0.0f;
	m_fEvadeDuration		= 1.0f;

	m_nGunIndex				= 0;

	m_nMaxHp				= 6;
	m_nHp					= m_nMaxHp;
	m_nArmor				= 2;
	m_nBlank				= 2;

	m_nSlotActiveItem		= 1;
	m_nCurrIndexSlot		= 0;

	m_fHitTimer				= 1.0f;
	m_fElapsedHitTimer		= 0.0f;

	m_fElapsedShotTimer		= 0.0f;
	m_fElapsedReloadTimer	= 0.0f;

	m_vMoveDir				= {0,0};

	m_enableToControl = true;
	m_isControlPause = false;
	m_enableToMove = true;
	m_isEvading = false;
	m_isShooting = false;
	m_isReloading = false;
	m_enableToHit = true;

	m_transform2DGun.scale = {150, 150};

	m_nAttack = 0;
	m_AttackCollider.transform2D.scale = { 100,100 };


	m_fElapsedCloudTimer = 0.0f;
	m_fCloudCoolTime = 0.3f;
}

void Player::Update()
{
	m_HitCollider.transform2D.position = { m_transform2D.position.x , m_transform2D.position.y - m_transform2D.scale.y * 0.25f };
	m_HitCollider.transform2D.scale = { 24,24 };
	m_HitCollider.Update();

	if (m_isAlive && m_enableToControl)
	{
		KeyboardUpdate();
		MouseUpdate();
		StateUpdate();
	}

	if (m_isHit)
	{
		if (m_fElapsedHitTimer >= m_fHitTimer)
		{
			m_fElapsedHitTimer = 0.0f;
			m_isHit = false;
			m_enableToHit = true;
		}
		else
		{
			m_enableToHit = false;
			m_fElapsedHitTimer += g_pTimeManager->GetDeltaTime();
		}
	}

	if (m_ePState == Player_State::Idle)
	{
		switch (m_eCharacterDir)
		{
		case Character_Dir::RT:
			m_eCState = Player_AniState::Idle_R;
			break;
		case Character_Dir::T:
			m_eCState = Player_AniState::Idle_T;
			break;
		case Character_Dir::LT:
			m_eCState = Player_AniState::Idle_L;
			break;
		case Character_Dir::LB:
			m_eCState = Player_AniState::Idle_L;
			break;
		case Character_Dir::B:
			m_eCState = Player_AniState::Idle_B;
			break;
		case Character_Dir::RB:
			m_eCState = Player_AniState::Idle_R;
			break;
		}
	}
	else if (m_ePState == Player_State::Run)
	{
		switch (m_eCharacterDir)
		{
		case Character_Dir::RT:
			m_eCState = Player_AniState::Run_RT;
			break;
		case Character_Dir::T:
			m_eCState = Player_AniState::Run_T;
			break;
		case Character_Dir::LT:
			m_eCState = Player_AniState::Run_LT;
			break;
		case Character_Dir::LB:
			m_eCState = Player_AniState::Run_LB;
			break;
		case Character_Dir::B:
			m_eCState = Player_AniState::Run_B;
			break;
		case Character_Dir::RB:
			m_eCState = Player_AniState::Run_RB;
			break;
		}
	}
	else if (m_ePState == Player_State::Evade)
	{
		switch (m_eCharacterDir)
		{
		case Character_Dir::R:
			m_eCState = Player_AniState::Evade_RB;
			break;
		case Character_Dir::RT:
			m_eCState = Player_AniState::Evade_RT;
			break;
		case Character_Dir::T:
			m_eCState = Player_AniState::Evade_T;
			break;
		case Character_Dir::LT:
			m_eCState = Player_AniState::Evade_LT;
			break;
		case Character_Dir::L:
			m_eCState = Player_AniState::Evade_LB;
			break;
		case Character_Dir::LB:
			m_eCState = Player_AniState::Evade_LB;
			break;
		case Character_Dir::B:
			m_eCState = Player_AniState::Evade_B;
			break;
		case Character_Dir::RB:
			m_eCState = Player_AniState::Evade_RB;
			break;
		}
	}
	else if (m_ePState == Player_State::Die)
	{
		if (m_fAngle >= D3DX_PI * 0.5f && m_fAngle < D3DX_PI * 1.5f)
		{
			m_eCState = Player_AniState::Die_L;
		}
		else
		{
			m_eCState = Player_AniState::Die_R;
		}
	}

	Unit::Update();
	Rotate();

	if (m_ePState == Player_State::Run)
	{
		m_fElapsedCloudTimer += g_pTimeManager->GetDeltaTime();
		if (m_fElapsedCloudTimer >= m_fCloudCoolTime)
		{
			m_fElapsedCloudTimer = 0.0f;
			Effect* effect = new Effect;
			effect->Init();
			effect->m_fDurationTime = 0.5f;
			effect->m_eType = EffectType::Cloud1;
			effect->m_transform2D.position.x = m_HitCollider.transform2D.position.x;
			effect->m_transform2D.position.y = m_HitCollider.transform2D.position.y - 16;
			effect->m_transform2D.scale = { 16, 16 };
			g_pEffectManager->GetVecEffect()->push_back(effect);
		}
	}

	if (m_isShooting)
	{
		m_vecGun[m_nGunIndex]->SetState(Gun_State::Shot);
		if (m_vecGun[m_nGunIndex]->GetGunInfo().eGunCode == GunCode::Sword)
		{
			if (m_fElapsedShotTimer >= 0.1f && m_nAttack == 0)
			{
				m_isAttack = true;
				m_nAttack++;
				Effect* effect = new Effect;
				effect->Init();
				effect->m_fDurationTime = 0.2f;
				effect->m_eType = EffectType::SwordAttack1;
				effect->m_transform2D.position.x = m_AttackCollider.transform2D.position.x + cosf(m_fAngle) * 50.0f;
				effect->m_transform2D.position.y = m_AttackCollider.transform2D.position.y + sinf(m_fAngle) * 50.0f;
				effect->m_transform2D.scale = { 100, 100 };
				effect->m_transform2D.rotation.z = m_fAngle - D3DX_PI * 0.25f;
				g_pEffectManager->GetVecEffect()->push_back(effect);
			}
			else if (m_fElapsedShotTimer >= 0.3f && m_nAttack == 1)
			{
				Shot();
				m_isAttack = true;
				m_nAttack++;
				Effect* effect = new Effect;
				effect->Init();
				effect->m_fDurationTime = 0.2f;
				effect->m_eType = EffectType::SwordAttack1;
				effect->m_transform2D.position.x = m_AttackCollider.transform2D.position.x + cosf(m_fAngle) * 50.0f;
				effect->m_transform2D.position.y = m_AttackCollider.transform2D.position.y + sinf(m_fAngle) * 50.0f;
				effect->m_transform2D.scale = { 100, 100 };
				effect->m_transform2D.rotation.z = m_fAngle - D3DX_PI * 0.25f;
				g_pEffectManager->GetVecEffect()->push_back(effect);
			}
			else
			{
				m_isAttack = false;
			}
		}
		else
		{
			Shot();
		}


		m_fElapsedShotTimer += g_pTimeManager->GetDeltaTime();
		if (m_fElapsedShotTimer >= (float)m_vecGun[m_nGunIndex]->GetGunInfo().fShootSpeed * 0.1f)
		{
			m_vecGun[m_nGunIndex]->SetState(Gun_State::Idle);
			m_isShooting = false;
			m_fElapsedShotTimer = 0.0f;
			m_nAttack = 0;
		}
	}
	else if (m_isReloading)
	{
		m_vecGun[m_nGunIndex]->SetState(Gun_State::Reload);
	}
	else
	{
		m_vecGun[m_nGunIndex]->SetState(Gun_State::Idle);
	}

	m_vecGun[m_nGunIndex]->Update(m_transform2DGun);
	AttackColliderUpdate();
}

void Player::Render()
{
	if (m_eCharacterDir == Character_Dir::RT || m_eCharacterDir == Character_Dir::T || m_eCharacterDir == Character_Dir::LT)
	{
		if(!m_isEvading)
			m_vecGun[m_nGunIndex]->Render();
		Unit::Render();
	}
	else
	{
		Unit::Render();
		if(!m_isEvading)
			m_vecGun[m_nGunIndex]->Render();
	}
	m_HitCollider.Render();
	m_AttackCollider.Render();
}


void Player::Move()
{
	D3DXVECTOR2 moveAmount;
	moveAmount.x = m_vMoveDir.x * m_fMoveSpeed * g_pTimeManager->GetDeltaTime();
	moveAmount.y = m_vMoveDir.y * m_fMoveSpeed * g_pTimeManager->GetDeltaTime();
	D3DXVECTOR2 v;
	if (m_vMoveDir.x > 0)
		v.x = m_HitCollider.transform2D.scale.x * 0.5f;
	else if (m_vMoveDir.x < 0)
		v.x = -m_HitCollider.transform2D.scale.x * 0.5f;
	else
		v.x = 0.0f;

	if (m_vMoveDir.y >= 0)
		v.y = m_HitCollider.transform2D.scale.y * 0.5f;
	else if (m_vMoveDir.y < 0)
		v.y = -m_HitCollider.transform2D.scale.y * 0.5f;
	else
		v.y = 0.0f;

	POINT pt = GET_TILE_POINT(m_HitCollider.transform2D.position.x + moveAmount.x + v.x, m_HitCollider.transform2D.position.y + moveAmount.y + v.y);
	//POINT currPt = GET_TILE_POINT(m_transform2D.position.x , m_transform2D.position.y);
	
	if (m_stTileInfo[pt.y][pt.x].eTType == TERRAIN_TYPE::Walkable	&&
		m_stTileInfo[pt.y][pt.x].eOType == OBJECT_TYPE::None		&&
		m_stTileInfo[pt.y][pt.x].eUType == UNIT_TYPE::None)
	{
		//갈수 있는 곳일때
		m_transform2D.position.x += moveAmount.x;
		m_transform2D.position.y += moveAmount.y;
	}
	//else
	//{
	//	//갈수 없는 곳일때
	//	if (currPt.x < pt.x)
	//	{
	//		//오른쪽이 막혀있을 때
	//		m_transform2D.position.x = GET_TILE_LBPOSITION(pt).x - v.x;
	//	}
	//	else if (currPt.x > pt.x)
	//	{
	//		//왼쪽이 막혀있을 때
	//		m_transform2D.position.x = GET_TILE_LBPOSITION(currPt).x + v.x;
	//	}
	//	else
	//	{
	//		//막힌곳의 x좌표가 같을 때
	//		m_transform2D.position.x += moveAmount.x;
	//	}
	//
	//	if (currPt.y < pt.y)
	//	{
	//		//위쪽이 막혀있을 때
	//		m_transform2D.position.y = GET_TILE_LBPOSITION(pt).y - v.y;
	//	}
	//	else if (currPt.y > pt.y)
	//	{
	//		//아래쪽이 막혀있을 때
	//		m_transform2D.position.y = GET_TILE_LBPOSITION(currPt).y + v.y;
	//	}
	//	else
	//	{
	//		//막힌곳의 y좌표가 같을 때
	//		m_transform2D.position.y += moveAmount.y;
	//	}
	//}

	
}

void Player::Rotate()
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


	m_transform2DGun.rotation.z = m_fAngle - D3DX_PI * 0.25f;
}

void Player::Evade()
{
	m_fElapsedEvadeTimer += g_pTimeManager->GetDeltaTime();
	
	if (m_fElapsedEvadeTimer >= m_fEvadeDuration)
	{
		m_fElapsedEvadeTimer = 0.0f;
		m_isEvading = false;
		m_enableToMove = true;
		m_enableToHit = true;
		m_fEvadeSpeed = 0.0f;
	}
	else
	{
		m_enableToHit = false;
		m_fEvadeSpeed = LinearInterpolation((float)EVADE_SPEED, 0.0f, m_fElapsedEvadeTimer / m_fEvadeDuration);

		D3DXVECTOR2 moveAmount;
		moveAmount.x = m_vMoveDir.x * m_fEvadeSpeed * g_pTimeManager->GetDeltaTime();
		moveAmount.y = m_vMoveDir.y * m_fEvadeSpeed * g_pTimeManager->GetDeltaTime();
		D3DXVECTOR2 v;
		if (m_vMoveDir.x >= 0)
			v.x = m_HitCollider.transform2D.scale.x * 0.5f;
		else if (m_vMoveDir.x < 0)
			v.x = -m_HitCollider.transform2D.scale.x * 0.5f;

		if (m_vMoveDir.y >= 0)
			v.y = m_HitCollider.transform2D.scale.y * 0.5f;
		else if (m_vMoveDir.y < 0)
			v.y = -m_HitCollider.transform2D.scale.y * 0.5f;

		POINT pt = GET_TILE_POINT(m_HitCollider.transform2D.position.x + moveAmount.x + v.x, m_HitCollider.transform2D.position.y + moveAmount.y + v.y);
		POINT currPt = GET_TILE_POINT(m_transform2D.position.x, m_transform2D.position.y);

		if (m_stTileInfo[pt.y][pt.x].eTType == TERRAIN_TYPE::Walkable &&
			m_stTileInfo[pt.y][pt.x].eOType == OBJECT_TYPE::None &&
			m_stTileInfo[pt.y][pt.x].eUType == UNIT_TYPE::None)
		{
			//갈수 있는 곳일때
			m_transform2D.position.x += moveAmount.x;
			m_transform2D.position.y += moveAmount.y;
		}
		//else
		//{
		//	//갈수 없는 곳일때
		//	if (currPt.x < pt.x)
		//	{
		//		//오른쪽이 막혀있을 때
		//		m_transform2D.position.x = GET_TILE_LBPOSITION(pt).x - m_HitCollider.transform2D.scale.x * 0.5f;
		//	}
		//	else if (currPt.x > pt.x)
		//	{
		//		//왼쪽이 막혀있을 때
		//		m_transform2D.position.x = GET_TILE_LBPOSITION(currPt).x + m_HitCollider.transform2D.scale.x * 0.5f;
		//	}
		//	else
		//	{
		//		//막힌곳의 x좌표가 같을 때
		//		m_transform2D.position.x += moveAmount.x;
		//	}
		//
		//	if (currPt.y < pt.y)
		//	{
		//		//위쪽이 막혀있을 때
		//		m_transform2D.position.y = GET_TILE_LBPOSITION(pt).y - m_HitCollider.transform2D.scale.y * 0.5f;
		//	}
		//	else if (currPt.y > pt.y)
		//	{
		//		//아래쪽이 막혀있을 때
		//		m_transform2D.position.y = GET_TILE_LBPOSITION(currPt).y + m_HitCollider.transform2D.scale.y * 0.5f;
		//	}
		//	else
		//	{
		//		//막힌곳의 y좌표가 같을 때
		//		m_transform2D.position.y += moveAmount.y;
		//	}
		//}
	}

	if (m_vMoveDir.x > 0.0f)
	{
		//오른
		if (m_vMoveDir.y > 0.0f)
		{
			//오른위
			m_eCharacterDir = Character_Dir::RT;
		}
		else if (m_vMoveDir.y < 0.0f)
		{
			//오른아래
			m_eCharacterDir = Character_Dir::RB;
		}
		else
		{
			//오른
			m_eCharacterDir = Character_Dir::R;
		}
	}
	else if (m_vMoveDir.x < 0.0f)
	{
		//왼
		if (m_vMoveDir.y > 0.0f)
		{
			//왼위
			m_eCharacterDir = Character_Dir::LT;
		}
		else if (m_vMoveDir.y < 0.0f)
		{
			//왼아래
			m_eCharacterDir = Character_Dir::LB;
		}
		else
		{
			//왼
			m_eCharacterDir = Character_Dir::L;
		}
	}
	else
	{
		if (m_vMoveDir.y > 0.0f)
		{
			//위
			m_eCharacterDir = Character_Dir::T;
		}
		else if (m_vMoveDir.y < 0.0f)
		{
			//아래
			m_eCharacterDir = Character_Dir::B;
		}
	}
}

void Player::UseBlank()
{

}

void Player::UseActiveItem()
{

}

void Player::Dead()
{
	m_isAlive = false;
}

void Player::Shot()
{
	Bullet* p = new Bullet;
	p->Init();
	p->m_stInfo.transform.rotation = { 0,0, (float)(m_transform2DGun.rotation.z + D3DX_PI * 0.25f) };
	p->m_stInfo.transform.position = m_transform2DGun.position;
	p->m_stInfo.transform.scale = { 100,100 };
	p->m_stInfo.colTransform = m_transform2DGun;
	p->m_stInfo.colTransform.scale = { 50,50 };
	D3DXVECTOR2 v = { cosf(m_transform2DGun.rotation.z + D3DX_PI * 0.25f),sinf(m_transform2DGun.rotation.z + D3DX_PI * 0.25f) };
	D3DXVec2Normalize(&v, &v);
	p->m_stInfo.moveDir = v;
	p->m_stInfo.moveSpeed = 600.0f;
	p->m_stInfo.shape = BulletShape::Sword;
	g_pBulletManager->GetBulletVector().push_back(p);
}

void Player::Reload()
{
}

void Player::Hit()
{
	if (m_nArmor <= 0)
	{
		m_nHp--;
		if (m_nHp <= 0)
			Dead();
	}
	else
	{
		m_nArmor--;
	}
	m_isHit = true;
}

void Player::Falling()
{
}

void Player::KnockBack(float power, D3DXVECTOR2 dir)
{
	D3DXVECTOR2 moveAmount;
	moveAmount.x = dir.x * power * g_pTimeManager->GetDeltaTime();
	moveAmount.y = dir.y * power * g_pTimeManager->GetDeltaTime();
	D3DXVECTOR2 v;
	if (m_vMoveDir.x >= 0)
		v.x = m_HitCollider.transform2D.scale.x * 0.5f;
	else if (m_vMoveDir.x < 0)
		v.x = -m_HitCollider.transform2D.scale.x * 0.5f;

	if (m_vMoveDir.y >= 0)
		v.y = m_HitCollider.transform2D.scale.y * 0.5f;
	else if (m_vMoveDir.y < 0)
		v.y = -m_HitCollider.transform2D.scale.y * 0.5f;

	POINT pt = GET_TILE_POINT(m_HitCollider.transform2D.position.x + moveAmount.x + v.x, m_HitCollider.transform2D.position.y + moveAmount.y + v.y);
	POINT currPt = GET_TILE_POINT(m_transform2D.position.x, m_transform2D.position.y);

	if (m_stTileInfo[pt.y][pt.x].eTType == TERRAIN_TYPE::Walkable &&
		m_stTileInfo[pt.y][pt.x].eOType == OBJECT_TYPE::None &&
		m_stTileInfo[pt.y][pt.x].eUType == UNIT_TYPE::None)
	{
		//갈수 있는 곳일때
		m_transform2D.position.x += moveAmount.x;
		m_transform2D.position.y += moveAmount.y;
	}
	//else
	//{
	//	//갈수 없는 곳일때
	//	if (currPt.x < pt.x)
	//	{
	//		//오른쪽이 막혀있을 때
	//		m_transform2D.position.x = GET_TILE_LBPOSITION(pt).x - m_HitCollider.transform2D.scale.x * 0.5f;
	//	}
	//	else if (currPt.x > pt.x)
	//	{
	//		//왼쪽이 막혀있을 때
	//		m_transform2D.position.x = GET_TILE_LBPOSITION(currPt).x + m_HitCollider.transform2D.scale.x * 0.5f;
	//	}
	//	else
	//	{
	//		//막힌곳의 x좌표가 같을 때
	//		m_transform2D.position.x += moveAmount.x;
	//	}
	//
	//	if (currPt.y < pt.y)
	//	{
	//		//위쪽이 막혀있을 때
	//		m_transform2D.position.y = GET_TILE_LBPOSITION(pt).y - m_HitCollider.transform2D.scale.y * 0.5f;
	//	}
	//	else if (currPt.y > pt.y)
	//	{
	//		//아래쪽이 막혀있을 때
	//		m_transform2D.position.y = GET_TILE_LBPOSITION(currPt).y + m_HitCollider.transform2D.scale.y * 0.5f;
	//	}
	//	else
	//	{
	//		//막힌곳의 y좌표가 같을 때
	//		m_transform2D.position.y += moveAmount.y;
	//	}
	//}
}

void Player::SetTileInfo(tagTileInfo tileInfo[NUM_TILE_Y][NUM_TILE_X])
{
	for (int y = 0; y < NUM_TILE_Y; y++)
	{
		for (int x = 0; x < NUM_TILE_X; x++)
		{
			m_stTileInfo[y][x] = tileInfo[y][x];
		}
	}
}

void Player::SetRectCollider(CircleCollider CircleCollider)
{
	m_HitCollider = CircleCollider;
}
