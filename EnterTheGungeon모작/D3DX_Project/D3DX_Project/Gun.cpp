#include "pch.h"
#include "Gun.h"

Gun::Gun()
	:
	m_pGAnimation(NULL)
{
}

Gun::~Gun()
{
	SAFE_DELETE(m_pGAnimation);
}

void Gun::Init(GunCode code)
{
	m_eState = Gun_State::Idle;
	m_stGunInfo.Init(code);
}

void Gun::Update(Transform2D transform)
{
	if (m_pGAnimation)
	{
		m_pGAnimation->SetConstantSizeScale(transform.scale);
		m_pGAnimation->SetRotation(transform.rotation);
		m_pGAnimation->SetPosition(transform.position);
		m_pGAnimation->SetAniSpeed(m_stGunInfo.fShootSpeed * 0.1f);
		m_pGAnimation->Play(m_eState);
		m_pGAnimation->Update();
	}		
}

void Gun::Render()
{
	if (m_pGAnimation)
	{
		m_pGAnimation->Render();
	}
}
