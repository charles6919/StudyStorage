#include "stdafx.h"
#include "LoadManager.h"


void LoadManager::Init()
{
	g_pTextureManager->AddTexture(L"ProgressBack",  L"CSH/progressBarBack.png");
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
		m_vecResourceList.push_back(new tagTextureInfo(RESOURCE_TYPE::Image, L"Title_Back",		L"CSH/Title/Title_Back.png"));
		m_vecResourceList.push_back(new tagTextureInfo(RESOURCE_TYPE::Image, L"Title_Manual",	L"CSH/Title/Title_Manual.png"));
		m_vecResourceList.push_back(new tagTextureInfo(RESOURCE_TYPE::Image, L"Start",			L"CSH/Title/Start.png"));
		m_vecResourceList.push_back(new tagTextureInfo(RESOURCE_TYPE::Image, L"Exit",			L"CSH/Title/Exit.png"));
		m_vecResourceList.push_back(new tagTextureInfo(RESOURCE_TYPE::Image, L"Manual",			L"CSH/Title/Manual.png"));

		m_vecResourceList.push_back(new tagSoundInfo(RESOURCE_TYPE::Sound, "TitleBgm",		"CSH/TitleBgm.ogg"	,true ,true));
		m_vecResourceList.push_back(new tagSoundInfo(RESOURCE_TYPE::Sound, "TitleSelect",	"CSH/TitleSelect.wav", false, false));

		break;
	case SCENE_KIND::Play:
		m_vecResourceList.push_back(new tagTextureInfo(RESOURCE_TYPE::Image, L"Player_HIdle",   L"CSH/Player/Player_HIdle.png"));
		m_vecResourceList.push_back(new tagTextureInfo(RESOURCE_TYPE::Image, L"Player_HRun",    L"CSH/Player/Player_HRun.png"));
		m_vecResourceList.push_back(new tagTextureInfo(RESOURCE_TYPE::Image, L"Player_HShot",   L"CSH/Player/Player_HShot.png"));
		m_vecResourceList.push_back(new tagTextureInfo(RESOURCE_TYPE::Image, L"Player_HReload", L"CSH/Player/Player_HReload.png"));
		m_vecResourceList.push_back(new tagTextureInfo(RESOURCE_TYPE::Image, L"Player_RIdle",   L"CSH/Player/Player_RIdle.png"));
		m_vecResourceList.push_back(new tagTextureInfo(RESOURCE_TYPE::Image, L"Player_RRun",    L"CSH/Player/Player_RRun.png"));
		m_vecResourceList.push_back(new tagTextureInfo(RESOURCE_TYPE::Image, L"Player_RShot",   L"CSH/Player/Player_RShot.png"));
		m_vecResourceList.push_back(new tagTextureInfo(RESOURCE_TYPE::Image, L"Player_RReload", L"CSH/Player/Player_RReload.png"));
		m_vecResourceList.push_back(new tagTextureInfo(RESOURCE_TYPE::Image, L"Bullet",			L"CSH/BulletPlayer.png"));
		m_vecResourceList.push_back(new tagTextureInfo(RESOURCE_TYPE::Image, L"Enemy_Idle",		L"CSH/Enemy/Enemy_Idle.png"));
		m_vecResourceList.push_back(new tagTextureInfo(RESOURCE_TYPE::Image, L"Enemy_Run",		L"CSH/Enemy/Enemy_Run.png"));
		m_vecResourceList.push_back(new tagTextureInfo(RESOURCE_TYPE::Image, L"AmmoPack",		L"CSH/Item/AmmoPack.png"));
		m_vecResourceList.push_back(new tagTextureInfo(RESOURCE_TYPE::Image, L"HealPack",		L"CSH/Item/HealPack.png"));
		m_vecResourceList.push_back(new tagTextureInfo(RESOURCE_TYPE::Image, L"SteamPack",		L"CSH/Item/SteamPack.png"));
		m_vecResourceList.push_back(new tagTextureInfo(RESOURCE_TYPE::Image, L"Background",		L"CSH/Background.png"));

		m_vecResourceList.push_back(new tagSoundInfo(RESOURCE_TYPE::Sound, "PlayBgm",		"CSH/PlayBgm.mp3"	, true, true));
		m_vecResourceList.push_back(new tagSoundInfo(RESOURCE_TYPE::Sound, "Shot",			"CSH/Shot.wav"		, false, false));
		m_vecResourceList.push_back(new tagSoundInfo(RESOURCE_TYPE::Sound, "HumanHit",		"CSH/HumanHit.wav"	, false, false));
		m_vecResourceList.push_back(new tagSoundInfo(RESOURCE_TYPE::Sound, "ZombieHit",		"CSH/ZombieHit.wav"	, false, false));
		m_vecResourceList.push_back(new tagSoundInfo(RESOURCE_TYPE::Sound, "Run",			"CSH/Run.wav"		, false, false));
		break;
	}
}