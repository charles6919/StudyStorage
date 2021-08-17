#pragma once
#include "iGameNode.h"

enum TitleState{READY, Title};

class TitleScene : public iGameNode
{
private:
	Animation<TitleState>*	m_pAnimation;
	Sprite*					m_pBackgroundSprite;
	Transform2D				m_transform2D;
	Button*					m_pBtnStart;
	Button*					m_pBtnContinue;
	Button*					m_pBtnExit;
	Button*					m_pBtnMapTool;

	bool					m_isContinue;

public:
	virtual void Init();
	virtual void Update();
	virtual void Render();
	virtual void Release();

};

