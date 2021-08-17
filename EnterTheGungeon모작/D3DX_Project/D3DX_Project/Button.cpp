#include "pch.h"
#include "Button.h"

Button::Button()
	:m_pAniButton(NULL)
{
}

Button::~Button()
{
	SAFE_DELETE(m_pAniButton);
}

void Button::Init()
{
	m_eState = Button_State::DeActivate;
	m_isActive = true;
	m_isClickUp = false;
}

void Button::ButtonStateUpdate()
{
	if (PointInRect(m_transform2D.position, m_transform2D.scale, D3DXVECTOR2(g_ptMouse.x + g_pCamera->GetPosition().x, g_ptMouse.y + g_pCamera->GetPosition().y)))
	{
		if (g_pKeyManager->IsOnceKeyUp(VK_LBUTTON))
		{
			m_eState = Button_State::ClickUp;
		}
		else if (g_pKeyManager->IsStayKeyDown(VK_LBUTTON))
		{
			m_eState = Button_State::ClickDown;
		}
		else
		{
			m_eState = Button_State::Activate;
		}
	}
	else
	{
		m_eState = Button_State::DeActivate;
	}
}

void Button::Update()
{
	if (m_isActive)
	{

		ButtonStateUpdate();

		if (m_pAniButton)
		{
			m_pAniButton->Play(m_eState);
			m_pAniButton->SetPosition(m_transform2D.position);
			m_pAniButton->SetConstantSizeScale(m_transform2D.scale);
			m_pAniButton->SetRotation(m_transform2D.rotation);
			m_pAniButton->Update();
		}
	}
}

void Button::Render()
{
	if (m_isActive)
	{
		if (m_pAniButton)
			m_pAniButton->Render();
	}
}



void Button::SetAnimation_Sprites(wstring Sp_name)
{
	m_pAniButton = new Animation<Button_State>;
	CreateClip(m_pAniButton, Sp_name, Button_State::DeActivate, 1, 4, 1, 1, 0);
	CreateClip(m_pAniButton, Sp_name, Button_State::Activate, 1, 4, 1, 1, 1);
	CreateClip(m_pAniButton, Sp_name, Button_State::ClickDown, 1, 4, 1, 1, 2);
	CreateClip(m_pAniButton, Sp_name, Button_State::ClickUp, 1, 4, 1, 1, 3);
}

void Button::SetAnimation_DeActivate(wstring Sp_name, int Sizex, int Sizey, int spriteIndex, float framerate, int indexnum)
{
	m_pAniButton = new Animation<Button_State>;
	CreateClip(m_pAniButton, Sp_name, Button_State::DeActivate, Sizex, Sizey, spriteIndex, framerate, indexnum);
}

void Button::SetAnimation_Activate(wstring Sp_name, int Sizex, int Sizey, int spriteIndex, float framerate, int indexnum)
{
	m_pAniButton = new Animation<Button_State>;
	CreateClip(m_pAniButton, Sp_name, Button_State::Activate, Sizex, Sizey, spriteIndex, framerate, indexnum);
}

void Button::SetAnimation_ClickDown(wstring Sp_name, int Sizex, int Sizey, int spriteIndex, float framerate, int indexnum)
{
	m_pAniButton = new Animation<Button_State>;
	CreateClip(m_pAniButton, Sp_name, Button_State::ClickDown, Sizex, Sizey, spriteIndex, framerate, indexnum);
}

void Button::SetAnimation_ClickUp(wstring Sp_name, int Sizex, int Sizey, int spriteIndex, float framerate, int indexnum)
{
	m_pAniButton = new Animation<Button_State>;
	CreateClip(m_pAniButton, Sp_name, Button_State::ClickUp, Sizex, Sizey, spriteIndex, framerate, indexnum);
}
