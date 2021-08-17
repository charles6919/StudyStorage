#include "pch.h"
#include "LoadManager.h"


void LoadManager::Init()
{
	g_pTextureManager->AddTexture(L"ProgressBack", L"CSH_Images/progressBarBack.png");
	g_pTextureManager->AddTexture(L"ProgressFront", L"CSH_Images/progressBarFront.png");
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
		m_vecResourceList.push_back(new tagTextureInfo(RESOURCE_TYPE::Image, L"TitleBackground", L"CSH_Images/Title/TitleBackground.png"));
		m_vecResourceList.push_back(new tagTextureInfo(RESOURCE_TYPE::Image, L"TitleDragun", L"CSH_Images/Title/TitleDragun.png"));
		m_vecResourceList.push_back(new tagTextureInfo(RESOURCE_TYPE::Image, L"Start_Button", L"CSH_Images/Start_Button.png"));
		m_vecResourceList.push_back(new tagTextureInfo(RESOURCE_TYPE::Image, L"Load_Button", L"CSH_Images/Load_Button.png"));
		m_vecResourceList.push_back(new tagTextureInfo(RESOURCE_TYPE::Image, L"Exit_Button", L"CSH_Images/Exit_Button.png"));
		m_vecResourceList.push_back(new tagTextureInfo(RESOURCE_TYPE::Image, L"MapTool_Button", L"CSH_Images/MapTool_Button.png"));
		m_vecResourceList.push_back(new tagTextureInfo(RESOURCE_TYPE::Image, L"Setting_Button", L"CSH_Images/Setting_Button.png"));
		break;
	case SCENE_KIND::Play:
		m_vecResourceList.push_back(new tagTextureInfo(RESOURCE_TYPE::Image, L"TileTerrain", L"CSH_Images/Tiles/TileTerrain.png"));
		m_vecResourceList.push_back(new tagTextureInfo(RESOURCE_TYPE::Image, L"Ceiling", L"CSH_Images/Tiles/Ceiling.png"));
		m_vecResourceList.push_back(new tagTextureInfo(RESOURCE_TYPE::Image, L"Walls", L"CSH_Images/Tiles/Walls.png"));
		m_vecResourceList.push_back(new tagTextureInfo(RESOURCE_TYPE::Image, L"Player_Idle", L"CSH_Images/Player/Player_Idle.png"));
		m_vecResourceList.push_back(new tagTextureInfo(RESOURCE_TYPE::Image, L"Player_Run", L"CSH_Images/Player/Player_Run.png"));
		m_vecResourceList.push_back(new tagTextureInfo(RESOURCE_TYPE::Image, L"Player_Evade", L"CSH_Images/Player/Player_Evade.png"));
		m_vecResourceList.push_back(new tagTextureInfo(RESOURCE_TYPE::Image, L"Sword", L"CSH_Images/Weapon/Sword.png"));
		m_vecResourceList.push_back(new tagTextureInfo(RESOURCE_TYPE::Image, L"Bullets", L"CSH_Images/Bullets.png"));
		m_vecResourceList.push_back(new tagTextureInfo(RESOURCE_TYPE::Image, L"BossChair", L"CSH_Images/Enemy/BossChair.png"));
		m_vecResourceList.push_back(new tagTextureInfo(RESOURCE_TYPE::Image, L"BossBody", L"CSH_Images/Enemy/BossBody.png"));
		m_vecResourceList.push_back(new tagTextureInfo(RESOURCE_TYPE::Image, L"BossHpProgressBarBack", L"CSH_Images/BossHpProgressBarBack.png"));
		m_vecResourceList.push_back(new tagTextureInfo(RESOURCE_TYPE::Image, L"BossHpProgressBarFront", L"CSH_Images/BossHpProgressBarFront.png"));
		m_vecResourceList.push_back(new tagTextureInfo(RESOURCE_TYPE::Image, L"SwordAttack1", L"CSH_Images/Effects/SwordAttack1.png"));
		m_vecResourceList.push_back(new tagTextureInfo(RESOURCE_TYPE::Image, L"Cloud1", L"CSH_Images/Effects/Cloud1.png"));
		m_vecResourceList.push_back(new tagTextureInfo(RESOURCE_TYPE::Image, L"Summon_Effect", L"CSH_Images/Effects/Summon_Effect.png"));
		m_vecResourceList.push_back(new tagTextureInfo(RESOURCE_TYPE::Image, L"Explsion_Effect", L"CSH_Images/Effects/Explsion_Effect.png"));
		m_vecResourceList.push_back(new tagTextureInfo(RESOURCE_TYPE::Image, L"Bullet_Destroy1", L"CSH_Images/Effects/Bullet_Destroy1.png"));
		m_vecResourceList.push_back(new tagTextureInfo(RESOURCE_TYPE::Image, L"OnePixel", L"CSH_Images/OnePixel.png"));
		m_vecResourceList.push_back(new tagTextureInfo(RESOURCE_TYPE::Image, L"Armor", L"CSH_Images/UIImages/Armor.png"));
		m_vecResourceList.push_back(new tagTextureInfo(RESOURCE_TYPE::Image, L"Blank", L"CSH_Images/UIImages/Blank.png"));
		m_vecResourceList.push_back(new tagTextureInfo(RESOURCE_TYPE::Image, L"Coin", L"CSH_Images/UIImages/Coin.png"));
		m_vecResourceList.push_back(new tagTextureInfo(RESOURCE_TYPE::Image, L"Empty_Heart", L"CSH_Images/UIImages/Empty_Heart.png"));
		m_vecResourceList.push_back(new tagTextureInfo(RESOURCE_TYPE::Image, L"Half_Heart", L"CSH_Images/UIImages/Half_Heart.png"));
		m_vecResourceList.push_back(new tagTextureInfo(RESOURCE_TYPE::Image, L"Full_Heart", L"CSH_Images/UIImages/Full_Heart.png"));
		m_vecResourceList.push_back(new tagTextureInfo(RESOURCE_TYPE::Image, L"Bandana_Bullet_Die", L"CSH_Images/Enemy/Bandana_Bullet_Die.png"));
		m_vecResourceList.push_back(new tagTextureInfo(RESOURCE_TYPE::Image, L"Bandana_Bullet_Idle", L"CSH_Images/Enemy/Bandana_Bullet_Idle.png"));
		m_vecResourceList.push_back(new tagTextureInfo(RESOURCE_TYPE::Image, L"Bandana_Bullet_Run", L"CSH_Images/Enemy/Bandana_Bullet_Run.png"));
		m_vecResourceList.push_back(new tagTextureInfo(RESOURCE_TYPE::Image, L"Normal_Bullet_Die", L"CSH_Images/Enemy/Normal_Bullet_Die.png"));
		m_vecResourceList.push_back(new tagTextureInfo(RESOURCE_TYPE::Image, L"Normal_Bullet_Idle", L"CSH_Images/Enemy/Normal_Bullet_Idle.png"));
		m_vecResourceList.push_back(new tagTextureInfo(RESOURCE_TYPE::Image, L"Normal_Bullet_Run", L"CSH_Images/Enemy/Normal_Bullet_Run.png"));
		m_vecResourceList.push_back(new tagTextureInfo(RESOURCE_TYPE::Image, L"Enemy_Weapon_01_R", L"CSH_Images/Weapon/Revolver_R.png"));
		m_vecResourceList.push_back(new tagTextureInfo(RESOURCE_TYPE::Image, L"Enemy_Weapon_01_L", L"CSH_Images/Weapon/Revolver_L.png"));


		break;
	case SCENE_KIND::MapTool:
		m_vecResourceList.push_back(new tagTextureInfo(RESOURCE_TYPE::Image, L"TileTerrain", L"CSH_Images/Tiles/TileTerrain.png"));
		m_vecResourceList.push_back(new tagTextureInfo(RESOURCE_TYPE::Image, L"Ceiling", L"CSH_Images/Tiles/Ceiling.png"));
		m_vecResourceList.push_back(new tagTextureInfo(RESOURCE_TYPE::Image, L"Walls", L"CSH_Images/Tiles/Walls.png"));
		m_vecResourceList.push_back(new tagTextureInfo(RESOURCE_TYPE::Image, L"Wood_Room", L"CSH_Images/Wood_Room.png"));
		m_vecResourceList.push_back(new tagTextureInfo(RESOURCE_TYPE::Image, L"Stone_Room", L"CSH_Images/Stone_Room.png"));
		m_vecResourceList.push_back(new tagTextureInfo(RESOURCE_TYPE::Image, L"Room_Button", L"CSH_Images/Room_Button.png"));
		m_vecResourceList.push_back(new tagTextureInfo(RESOURCE_TYPE::Image, L"Door_Button", L"CSH_Images/Door_Button.png"));
		m_vecResourceList.push_back(new tagTextureInfo(RESOURCE_TYPE::Image, L"Back_Button", L"CSH_Images/Back_Button.png"));
		m_vecResourceList.push_back(new tagTextureInfo(RESOURCE_TYPE::Image, L"Save_Button", L"CSH_Images/Save_Button.png"));
		m_vecResourceList.push_back(new tagTextureInfo(RESOURCE_TYPE::Image, L"Terrain_Btn", L"CSH_Images/Terrain_Btn.png"));
		m_vecResourceList.push_back(new tagTextureInfo(RESOURCE_TYPE::Image, L"Walls_Btn", L"CSH_Images/Walls_Btn.png"));
		m_vecResourceList.push_back(new tagTextureInfo(RESOURCE_TYPE::Image, L"Ceiling_Btn", L"CSH_Images/Ceiling_Btn.png"));
		m_vecResourceList.push_back(new tagTextureInfo(RESOURCE_TYPE::Image, L"Title_Btn", L"CSH_Images/Title_Btn.png"));
		m_vecResourceList.push_back(new tagTextureInfo(RESOURCE_TYPE::Image, L"Normal_Door_Palette", L"CSH_Images/Normal_Door_Palette.png"));
		m_vecResourceList.push_back(new tagTextureInfo(RESOURCE_TYPE::Image, L"Pallete_Background", L"CSH_Images/Pallete_Background.png"));
		break;
	}
}