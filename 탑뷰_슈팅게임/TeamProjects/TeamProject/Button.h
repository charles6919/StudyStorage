#pragma once
#include "Components.h"


class Button
{
private:
	Transform2D						m_Transform;
	Sprite*							m_pSprite;		//��ư ��������Ʈ
	bool							m_isOnMouse;		//��ư�� ���콺�� �����͸� �÷ȴ���
	bool							m_isClickDown;		//Ŭ�� �ٿ�
	bool							m_isClickUp;		//Ŭ�� ��


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

