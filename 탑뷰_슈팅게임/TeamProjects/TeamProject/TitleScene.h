#pragma once
#include "iGameNode.h"
#include "Button.h"

class TitleScene : public iGameNode
{
#define START_DEFAULT D3DXVECTOR2(114, 78)
#define START_ONMOUSE_SIZE D3DXVECTOR2(152, 104)
#define MANUAL_DEFAULT D3DXVECTOR2(320, 78)
#define MANUAL_ONMOUSE_SIZE D3DXVECTOR2(380, 104)
#define EXIT_DEFAULT D3DXVECTOR2(96, 78)
#define EXIT_ONMOUSE_SIZE D3DXVECTOR2(132, 104)


private:
	Sprite* m_pTitleImg;

	Button* m_pBtnStart;
	Button* m_pBtnRetry;
	Button* m_pBtnManual;
	Button* m_pBtnExit;

	Sprite* m_pSpriteManual;

	bool m_isDrawManual;
	bool m_isOnStartSound;
	bool m_isOnManualSound;
	bool m_isOnExitSound;
	

public:
	TitleScene();
	~TitleScene();

	virtual void Init()		override;
	virtual void Update()	override;
	virtual void Render()	override;
	virtual void Release()	override;
};

