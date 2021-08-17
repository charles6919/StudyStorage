#include "pch.h"
#include "LoadingScene.h"

void LoadingScene::Init()
{
	//m_pAnimation = new Animation<LoadState>;
}

void LoadingScene::Update()
{
	g_pLoadManager->Update();
}

void LoadingScene::Render()
{
}

void LoadingScene::Release()
{
}
