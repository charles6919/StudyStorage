#pragma once
#include "Components.h"


class Button
{
private:
	Transform2D						m_Transform;
	Sprite*							m_pSprite;		//버튼 스프라이트
	bool							m_isOnMouse;		//버튼에 마우스를 포인터를 올렸는지
	bool							m_isClickDown;		//클릭 다운
	bool							m_isClickUp;		//클릭 업


public:
	Button();
	~Button();

	void Init();
	void Update();
	void Render();

	void SetSprite(Sprite* p) { m_pSprite = p; }
	Transform2D& GetTransform2D() { return m_Transform; }

	bool GetIsOnMouse()		{ return m_isOnMouse;	}
	bool GetIsClickDown()	{ return m_isClickDown; }
	bool GetIsClickUp()		{ return m_isClickUp;	}

};

