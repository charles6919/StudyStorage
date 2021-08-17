#include "pch.h"
#include "TitleScene.h"

void TitleScene::Init()
{
	m_pAnimation = NULL;
	m_pBackgroundSprite = NULL;
	m_transform2D.position = {0,0};
	m_transform2D.scale = {WINSIZEX, WINSIZEY};
	m_pBtnStart = new Button;
	m_pBtnContinue = new Button;
	m_pBtnExit = new Button;
	m_pBtnMapTool = new Button;

	//TODO: 애니메이션 세팅해야함.
	m_pBackgroundSprite = new Sprite(L"TitleBackground");
	m_pBackgroundSprite->SetLBPosition(0, 0);
	m_pBackgroundSprite->SetConstantScale(WINSIZEX, WINSIZEY);
	m_pBackgroundSprite->Update();

	m_pAnimation = new Animation<TitleState>;
	CreateClip(m_pAnimation, L"TitleDragun", TitleState::Title, 8, 1, 8, 8, 0);
	m_pAnimation->Play(TitleState::Title);
	m_pAnimation->SetLBPosition(1000, 420);
	m_pAnimation->SetScale(1, 1);
	m_pAnimation->Update();

	m_pBtnStart->Init();
	m_pBtnContinue->Init();
	m_pBtnExit->Init();
	m_pBtnMapTool->Init();

	m_pBtnStart->SetAnimation_Sprites(L"Start_Button");
	m_pBtnContinue->SetAnimation_Sprites(L"Load_Button");
	m_pBtnExit->SetAnimation_Sprites(L"Exit_Button");
	m_pBtnMapTool->SetAnimation_Sprites(L"MapTool_Button");

	m_pBtnExit->SetScale(D3DXVECTOR2(100,25));
	m_pBtnExit->SetLBPosition(D3DXVECTOR2(100,50));

	m_pBtnContinue->SetScale(D3DXVECTOR2(100, 25));
	m_pBtnContinue->SetLBPosition(D3DXVECTOR2(100, 100));

	m_pBtnMapTool->SetScale(D3DXVECTOR2(175, 25));
	m_pBtnMapTool->SetLBPosition(D3DXVECTOR2(100, 150));

	m_pBtnStart->SetScale(D3DXVECTOR2(125, 25));
	m_pBtnStart->SetLBPosition(D3DXVECTOR2(100, 200));

	m_pBtnStart->Update();
	m_pBtnContinue->Update();
	m_pBtnExit->Update();
	m_pBtnMapTool->Update();

}

void TitleScene::Update()
{


	if (m_pAnimation)
	{
		m_pAnimation->Play(TitleState::Title);
		//m_pAnimation->SetLBPosition(m_transform2D.position);
		//m_pAnimation->SetConstantSizeScale(m_transform2D.scale);
		m_pAnimation->Update();
	}

	if (m_pBtnStart)
	{
		m_pBtnStart->Update();
		if (m_pBtnStart->GetButtonState() == Button_State::ClickUp)
		{
			//Play
			m_isContinue = false;
			g_pLoadManager->ChangeScene(SCENE_KIND::Play);


		}
	}

	if (m_pBtnContinue)
	{
		m_pBtnContinue->Update();
		if (m_pBtnContinue->GetButtonState() == Button_State::ClickUp)
		{
			//continue
			g_pLoadManager->ChangeScene(SCENE_KIND::Play);


		}
	}

	if (m_pBtnExit)
	{
		m_pBtnExit->Update();
		if (m_pBtnExit->GetButtonState() == Button_State::ClickUp)
		{
			//Exit
			PostQuitMessage(0);


		}
	}

	if (m_pBtnMapTool)
	{
		m_pBtnMapTool->Update();
		if (m_pBtnMapTool->GetButtonState() == Button_State::ClickUp)
		{
			//MapTool
			g_pLoadManager->ChangeScene(SCENE_KIND::MapTool);


		}
	}
}

void TitleScene::Render()
{
	if (m_pBackgroundSprite)
		m_pBackgroundSprite->Render();

	if (m_pAnimation)
		m_pAnimation->Render();

	if (m_pBtnStart)
		m_pBtnStart->Render();

	if (m_pBtnContinue)
		m_pBtnContinue->Render();

	if (m_pBtnExit)
		m_pBtnExit->Render();

	if (m_pBtnMapTool)
		m_pBtnMapTool->Render();
}

void TitleScene::Release()
{
	
	SAFE_DELETE(m_pBtnMapTool);
	SAFE_DELETE(m_pBtnExit);
	SAFE_DELETE(m_pBtnContinue);
	SAFE_DELETE(m_pBtnStart);
	SAFE_DELETE(m_pAnimation);
}
