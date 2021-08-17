#include "stdafx.h"
#include "LoadManager.h"


void LoadManager::Init()
{
	g_pTextureManager->AddTexture(L"ProgressBack", L"CSH/progressBarBack.png");
	g_pTextureManager->AddTexture(L"ProgressFront", L"CSH/progressBarFront.png");
}

void LoadManager::Update()
{
	if (m_vecResourceList.size() == m_nNumLoaded) // 로딩 완료
	{
		g_pSceneManager->Change(m_eNextScene);
		return;
	}

	switch (m_vecResourceList[m_nNumLoaded]->eType)
	{
		case RESOURCE_TYPE::Image:
		{
			tagTextureInfo* info = (tagTextureInfo*)m_vecResourceList[m_nNumLoaded];
			g_pTextureManager->AddTexture(info->sKey, info->sFile);
		}
		break;
		case RESOURCE_TYPE::Sound:
		{
			tagSoundInfo* info = (tagSoundInfo*)m_vecResourceList[m_nNumLoaded];
			g_pSoundManager->AddSound(info->sKey, info->sFile, info->isBgm, info->isLoop);
		}
		break;
	}

	m_nNumLoaded++;
}

void LoadManager::ReleaseAll()
{
	ReleasePrevResources();
}

void LoadManager::ChangeScene(SCENE_KIND eNext)
{
	g_pSceneManager->Change(SCENE_KIND::Loading);

	m_eNextScene = eNext;
	ReleasePrevResources();
	MakeAResourcesList();
}

void LoadManager::ReleasePrevResources()
{
	for (int i = 0; i < m_vecResourceList.size(); i++)
	{
		switch (m_vecResourceList[i]->eType)
		{
			case RESOURCE_TYPE::Image:
			{
				tagTextureInfo* info = (tagTextureInfo*)m_vecResourceList[i];
				g_pTextureManager->Release(info->sKey);
				SAFE_DELETE(info);
			}
			break;
			case RESOURCE_TYPE::Sound:
			{
				tagSoundInfo* info = (tagSoundInfo*)m_vecResourceList[i];
				g_pSoundManager->ReleaseSound(info->sKey);
				SAFE_DELETE(info);
			}
			break;
		}
	}
	m_vecResourceList.clear();
}

void LoadManager::MakeAResourcesList()
{
	m_nNumLoaded = 0;

	switch (m_eNextScene)
	{
	case SCENE_KIND::Title:
		m_vecResourceList.push_back(new tagTextureInfo(RESOURCE_TYPE::Image, L"TitleBack", L"CSH/ChloeBennet.bmp"));
		break;
	case SCENE_KIND::Play:
		m_vecResourceList.push_back(new tagTextureInfo(RESOURCE_TYPE::Image, L"TileSet1", L"CSH/Tilesets/Dungeon_A2.png"));
		m_vecResourceList.push_back(new tagTextureInfo(RESOURCE_TYPE::Image, L"ObjectSet1", L"CSH/Tilesets/Inside_C.png"));
		m_vecResourceList.push_back(new tagTextureInfo(RESOURCE_TYPE::Image, L"Player", L"CSH/Character/PackMan.png"));
		m_vecResourceList.push_back(new tagTextureInfo(RESOURCE_TYPE::Image, L"Player_Dead", L"CSH/Character/PackMan_Die.png"));
		m_vecResourceList.push_back(new tagTextureInfo(RESOURCE_TYPE::Image, L"Enemy_Red_Move", L"CSH/Character/Enemy_Red_Move.png"));
		m_vecResourceList.push_back(new tagTextureInfo(RESOURCE_TYPE::Image, L"Enemy_Scared", L"CSH/Character/Enemy_Scared.png"));
		m_vecResourceList.push_back(new tagTextureInfo(RESOURCE_TYPE::Image, L"Enemy_Jailed", L"CSH/Character/Enemy_Jailed.png"));
		m_vecResourceList.push_back(new tagTextureInfo(RESOURCE_TYPE::Image, L"Normal_Item", L"CSH/Items/Normal_Item.png"));
		m_vecResourceList.push_back(new tagTextureInfo(RESOURCE_TYPE::Image, L"Attack_Item", L"CSH/Items/Attack_Item.png"));
		break;
	case SCENE_KIND::MapTool:
		m_vecResourceList.push_back(new tagTextureInfo(RESOURCE_TYPE::Image, L"TileSet1", L"CSH/Tilesets/Dungeon_A2.png"));
		m_vecResourceList.push_back(new tagTextureInfo(RESOURCE_TYPE::Image, L"ObjectSet1", L"CSH/Tilesets/Inside_C.png"));
		m_vecResourceList.push_back(new tagTextureInfo(RESOURCE_TYPE::Image, L"SelectUI", L"CSH/System/Window.png"));
		break;
	}
}