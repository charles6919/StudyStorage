#include "stdafx.h"
#include "Button.h"

Button::Button()
{
	m_pSprite = NULL;
	Init();
}

Button::~Button()
{
	SAFE_DELETE(m_pSprite);
}

void Button::Init()
{
	m_Transform.Init();
	m_isOnMouse		= false;
	m_isClickDown	= false;
	m_isClickUp		= false;
}

void Button::Update()
{
	if (PointInRect(m_Transform.GetPosition(), m_Transform.GetScale(), D3DXVECTOR2(g_ptMouse.x, g_ptMouse.y)))
	{
		m_isOnMouse = true;

		if (g_pKeyManager->isStayKeyDown(VK_LBUTTON))
		{
			m_isClickDown = true;
		}
		else
			m_isClickDown = false;

		if (g_pKeyManager->isOnceKeyUp(VK_LBUTTON))
		{
			m_isClickUp = true;
		}
		else
			m_isClickUp = false;
	}
	else
	{
		m_isOnMouse = false;
	}

}

void Button::Render()
{
	if (m_pSprite)
	{
		m_pSprite->SetConstantScale(m_Transform.GetScale());
		m_pSprite->SetRotation(m_Transform.GetRotation());
		m_pSprite->SetPosition(m_Transform.GetPosition());
		m_pSprite->Update();
		m_pSprite->Render();
	}
}
