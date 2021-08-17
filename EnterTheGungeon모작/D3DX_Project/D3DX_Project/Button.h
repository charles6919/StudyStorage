#pragma once
#include "ObjectComponent.h"

enum class Button_State {READY, DeActivate, Activate, ClickDown, ClickUp};

class Button
{
private:
	Animation<Button_State>* m_pAniButton;
	Button_State m_eState;
	Transform2D m_transform2D;
	bool m_isActive;
	bool m_isClickUp;

public:
	Button();
	~Button();

	void Init();
	void ButtonStateUpdate();
	void Update();
	void Render();

	void SetAnimation_Sprites(wstring Sp_name);
	void SetAnimation_DeActivate(wstring Sp_name, int Sizex, int Sizey, int spriteIndex, float framerate, int indexnum);
	void SetAnimation_Activate(wstring Sp_name, int Sizex, int Sizey, int spriteIndex, float framerate, int indexnum);
	void SetAnimation_ClickDown(wstring Sp_name, int Sizex, int Sizey, int spriteIndex, float framerate, int indexnum);
	void SetAnimation_ClickUp(wstring Sp_name, int Sizex, int Sizey, int spriteIndex, float framerate, int indexnum);
	void SetButtonState(Button_State state) { m_eState = state; }
	void SetIsActive(bool b) { m_isActive = b; }
	void SetTransform2D(Transform2D transfrom) { m_transform2D = transfrom; }
	void SetPosition(D3DXVECTOR2 pos) { m_transform2D.position = pos; }
	void SetLBPosition(D3DXVECTOR2 pos) { m_transform2D.position = { pos.x + m_transform2D.scale.x * 0.5f , pos.y + m_transform2D.scale.y * 0.5f }; }
	void SetScale(D3DXVECTOR2 scale) { m_transform2D.scale = scale; }
	void SetRotation(D3DXVECTOR3 rot) { m_transform2D.rotation = rot; }

	Transform2D GetTransform2D() { return m_transform2D; }
	Button_State GetButtonState() { return m_eState; }
	bool IsClickUp() { return m_isClickUp; }

};

