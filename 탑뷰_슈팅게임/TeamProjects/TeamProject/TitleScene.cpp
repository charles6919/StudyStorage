#include "stdafx.h"
#include "TitleScene.h"

TitleScene::TitleScene()
{
	m_pTitleImg			= NULL;
	m_pBtnStart			= NULL;
	m_pBtnRetry			= NULL;
	m_pBtnManual		= NULL;
	m_pBtnExit			= NULL;
	m_pSpriteManual		= NULL;
}

TitleScene::~TitleScene()
{
	SAFE_DELETE(m_pTitleImg		);
	SAFE_DELETE(m_pBtnStart		);
	SAFE_DELETE(m_pBtnRetry		);
	SAFE_DELETE(m_pBtnManual	);
	SAFE_DELETE(m_pBtnExit		);
	SAFE_DELETE(m_pSpriteManual	);
}

void TitleScene::Init()
{
	m_isDrawManual = false;
	m_isOnStartSound = false;
	m_isOnManualSound = false;
	m_isOnExitSound = false;

	m_pTitleImg = new Sprite(L"Title_Back");
	m_pSpriteManual = new Sprite(L"Title_Manual");

	Sprite* sp = new Sprite(L"Start");
	m_pBtnStart = new Button;
	m_pBtnStart->SetSprite(sp);

	sp = new Sprite(L"Exit");
	m_pBtnExit = new Button();
	m_pBtnExit->SetSprite(sp);

	sp = new Sprite(L"Manual");
	m_pBtnManual = new Button();
	m_pBtnManual->SetSprite(sp);

	m_pTitleImg->SetConstantScale(WINSIZEX, WINSIZEY);
	m_pTitleImg->SetPosition(HALFSIZEX, HALFSIZEY);
	m_pSpriteManual->SetConstantScale(WINSIZEX * 0.5, WINSIZEY * 0.5);
	m_pSpriteManual->SetPosition(HALFSIZEX, HALFSIZEY);

	m_pBtnStart->GetTransform2D().SetPosition(HALFSIZEX - m_pBtnStart->GetTransform2D().GetScale().x * 0.5f, HALFSIZEY - m_pBtnStart->GetTransform2D().GetScale().y * 0.5f);
	m_pBtnManual->GetTransform2D().SetPosition(HALFSIZEX - m_pBtnManual->GetTransform2D().GetScale().x * 0.5f, HALFSIZEY - m_pBtnManual->GetTransform2D().GetScale().y * 0.5f - 110 * 1);
	m_pBtnExit->GetTransform2D().SetPosition(HALFSIZEX - m_pBtnExit->GetTransform2D().GetScale().x * 0.5f, HALFSIZEY - m_pBtnExit->GetTransform2D().GetScale().y * 0.5f -110 *2);

}

void TitleScene::Update()
{

	g_pSoundManager->Play("TitleBgm");

	if (m_pBtnStart)
		m_pBtnStart->Update();

	if (m_pBtnRetry)
		m_pBtnRetry->Update();

	if (m_pBtnManual)
		m_pBtnManual->Update();

	if (m_pBtnExit)
		m_pBtnExit->Update();

	//버튼의 상태가 update에서 바뀌기 때문에 위에 넣어야 한다.


	if (m_pBtnStart->GetIsOnMouse())
	{
		m_pBtnStart->GetTransform2D().SetScale(START_ONMOUSE_SIZE);

		if (m_isOnStartSound == false)
		{
			g_pSoundManager->Play("TitleSelect");
			m_isOnStartSound = true;
		}

		if (m_pBtnStart->GetIsClickDown())
		{
			m_pBtnStart->GetTransform2D().SetScale(START_DEFAULT);
		}
		else if (m_pBtnStart->GetIsClickUp())
		{
			g_pLoadManager->ChangeScene(SCENE_KIND::Play);
		}

	}
	else
	{
		m_pBtnStart->GetTransform2D().SetScale(START_DEFAULT);
		m_isOnStartSound = false;
	}

	//if (m_pBtnRetry->GetIsOnMouse())
	//{
	//	if (m_pBtnRetry->GetIsClickDown())
	//	{
	//
	//	}
	//	else if (m_pBtnRetry->GetIsClickUp())
	//	{
	//
	//	}
	//	else
	//	{
	//
	//	}
	//
	//}
	//else
	//{
	//
	//}

	if (m_pBtnManual->GetIsOnMouse())
	{
		if (m_isOnManualSound == false)
		{
			g_pSoundManager->Play("TitleSelect");
			m_isOnManualSound = true;
		}

		m_pBtnManual->GetTransform2D().SetScale(MANUAL_ONMOUSE_SIZE);
		if (m_pBtnManual->GetIsClickDown())
		{
			m_pBtnManual->GetTransform2D().SetScale(MANUAL_DEFAULT);

		}
		else if (m_pBtnManual->GetIsClickUp())
		{
			m_isDrawManual = !m_isDrawManual;
		}

	}
	else
	{
		m_pBtnManual->GetTransform2D().SetScale(MANUAL_DEFAULT);
		m_isOnManualSound = false;
	}

	if (m_pBtnExit->GetIsOnMouse())
	{
		if (m_isOnExitSound == false)
		{
			g_pSoundManager->Play("TitleSelect");
			m_isOnExitSound = true;
		}

		m_pBtnExit->GetTransform2D().SetScale(EXIT_ONMOUSE_SIZE);
		if (m_pBtnExit->GetIsClickDown())
		{
			m_pBtnExit->GetTransform2D().SetScale(EXIT_DEFAULT);

		}
		else if (m_pBtnExit->GetIsClickUp())
		{
			PostQuitMessage(0);
		}

	}
	else
	{
		m_isOnExitSound = false;
		m_pBtnExit->GetTransform2D().SetScale(EXIT_DEFAULT);
	}



	if (m_pTitleImg)
		m_pTitleImg->Update();

	if (m_pSpriteManual)
		m_pSpriteManual->Update();
}

void TitleScene::Render()
{
	if (m_pTitleImg)
		m_pTitleImg->Render();

	if (m_pSpriteManual && m_isDrawManual)
		m_pSpriteManual->Render();

	if (m_pBtnStart)
		m_pBtnStart->Render();

	//if (m_pBtnRetry)
	//	m_pBtnRetry->Render();

	if (m_pBtnManual)
		m_pBtnManual->Render();

	if (m_pBtnExit)
		m_pBtnExit->Render();

}

void TitleScene::Release()
{
	//g_pTextureManager->Release();
	g_pSoundManager->Stop("TitleBgm");
}
