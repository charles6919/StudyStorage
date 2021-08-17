#include "stdafx.h"
#include "MapTool.h"


void MapTool::TestInit()
{
	m_pPlayer = new PlayerTest();
	m_pPlayer->SetMapTool(this);
	m_pPlayer->Init();
}

void MapTool::TestUpdate()
{
	if (m_pPlayer)
		m_pPlayer->Update();
}

void MapTool::TestRender()
{
	if (m_pPlayer)
		m_pPlayer->Render();
}

void MapTool::TestRelease()
{
	SAFE_DELETE(m_pPlayer);
}

void MapTool::Init()
{
	for (int i = NUM_TILE_V - 1; i >= 0; i--)
	{
		for (int j = 0; j < NUM_TILE_U; j++)
		{
			Sprite* pSprite = new Sprite(L"TileSet1", NUM_TILE_U, NUM_TILE_V, i * NUM_TILE_U + j);
			m_vecTerrain.push_back(pSprite);
		}
	}

	for (int i = NUM_OBJECT_UV - 1; i >= 0; i--)
	{
		for (int j = 0; j < NUM_OBJECT_UV; j++)
		{
			Sprite* pSprite = new Sprite(L"ObjectSet1", NUM_OBJECT_UV, NUM_OBJECT_UV, i * NUM_OBJECT_UV + j);
			m_vecObject.push_back(pSprite);
		}
	}

	for (int i = 0; i < NUM_TILE_Y; i++)
	{
		for (int j = 0; j < NUM_TILE_X; j++)
		{
			m_stTiles[i][j].eTType = TERRAIN_TYPE::Walkable;
			m_stTiles[i][j].nTIndex = 0;
			m_stTiles[i][j].eOType = OBJECT_TYPE::None;
			m_stTiles[i][j].nOIndex = 0;
		}
	}

	m_ePType = PALETTE_TYPE::Terrain;
	m_ptUVSize.x = NUM_TILE_U;
	m_ptUVSize.y = NUM_TILE_V;
	m_stSelected.eTType = TERRAIN_TYPE::Walkable;
	m_stSelected.nTIndex = 0;
	m_stSelected.eOType = OBJECT_TYPE::Breakable;
	m_stSelected.nOIndex = 0;

	m_pRect = new Rect;
	m_pRect->SetBorder(true);
	m_pRect->SetDraw(false);

	m_pSelectUI = new Sprite(L"SelectUI", 8, 8, 39);
	m_pSelectUI->SetConstantScale(UI_FONT_SIZE, UI_FONT_SIZE);

	TestInit();
}

void MapTool::ImguiSetting()
{
	// 팔레트 선택 UI
	static int PType;
	static const char* szPNames[(int)PALETTE_TYPE::Max];
	szPNames[(int)PALETTE_TYPE::Terrain] = new char[32];
	szPNames[(int)PALETTE_TYPE::Terrain] = "Terrain";
	szPNames[(int)PALETTE_TYPE::Object] = new char[32];
	szPNames[(int)PALETTE_TYPE::Object] = "Object";
	ImGui::ListBox("PaletteType", &PType, szPNames, (int)PALETTE_TYPE::Max);
	m_ePType = (PALETTE_TYPE)PType;

	// 지형 속성
	static int TType;
	static const char* szTNames[(int)TERRAIN_TYPE::Max];
	for (int i = 0; i < (int)TERRAIN_TYPE::Max; i++)
		szTNames[i] = new char[32];
	szTNames[(int)TERRAIN_TYPE::Walkable] = "Walkable";
	szTNames[(int)TERRAIN_TYPE::Unwalkable] = "Unwalkable";
	szTNames[(int)TERRAIN_TYPE::Rough] = "Rough";
	szTNames[(int)TERRAIN_TYPE::Slippery] = "Slippery";
	ImGui::ListBox("TerrainType", &TType, szTNames, (int)TERRAIN_TYPE::Max);
	m_stSelected.eTType = (TERRAIN_TYPE)TType;

	// 오브젝트 속성
	static int OType;
	static const char* szONames[(int)PALETTE_TYPE::Max];
	szONames[(int)OBJECT_TYPE::Breakable] = new char[32];
	szONames[(int)OBJECT_TYPE::Breakable] = "Breakable";
	szONames[(int)OBJECT_TYPE::Unbreakable] = new char[32];
	szONames[(int)OBJECT_TYPE::Unbreakable] = "Unbreakable";
	ImGui::ListBox("ObjectType", &OType, szONames, (int)OBJECT_TYPE::Max - 1);
	m_stSelected.eOType = (OBJECT_TYPE)OType;

	// 선택한 팔레트 종류의 UV값에 따라 크기 설정
	switch (m_ePType)
	{
	case PALETTE_TYPE::Terrain:
		m_ptUVSize.x = NUM_TILE_U;
		m_ptUVSize.y = NUM_TILE_V;
		break;
	case PALETTE_TYPE::Object:
		m_ptUVSize.x = NUM_OBJECT_UV;
		m_ptUVSize.y = NUM_OBJECT_UV;
		break;
	}
}

void MapTool::Update()
{
	ImguiSetting();

	if (g_pKeyManager->isOnceKeyDown(VK_ESCAPE))
		g_pLoadManager->ChangeScene(SCENE_KIND::Title);

	// 팔레트 영역
	if (g_ptMouse.x > 0 && g_ptMouse.x < TOOL_AREA_X)
	{
		if (g_ptMouse.y < TOOL_AREA_Y(m_ptUVSize.x, m_ptUVSize.y))
		{
			int x = g_ptMouse.x / PALETTE_TILE_SIZE(m_ptUVSize.x);
			int y = g_ptMouse.y / PALETTE_TILE_SIZE(m_ptUVSize.x);

			if (m_pRect)
			{
				m_pRect->SetSize(PALETTE_TILE_SIZE(m_ptUVSize.x), PALETTE_TILE_SIZE(m_ptUVSize.x));
				m_pRect->SetLBPosition(x * PALETTE_TILE_SIZE(m_ptUVSize.x), y * PALETTE_TILE_SIZE(m_ptUVSize.x));
				m_pRect->Update();
			}

			if (g_pKeyManager->isOnceKeyDown(VK_LBUTTON))
			{
				switch (m_ePType)
				{
				case PALETTE_TYPE::Terrain:
					m_stSelected.nTIndex = y * NUM_TILE_U + x;
					break;
				case PALETTE_TYPE::Object:
					m_stSelected.nOIndex = y * NUM_TILE_U + x;
					break;
				}
			}
		}
	}
	else // 작업 영역
	{
		int x = (g_ptMouse.x - TOOL_AREA_X) / TILE_SIZE;
		int y = g_ptMouse.y / TILE_SIZE;

		if (m_pRect)
		{
			m_pRect->SetSize(TILE_SIZE, TILE_SIZE);
			m_pRect->SetLBPosition(x * TILE_SIZE + TOOL_AREA_X, y * TILE_SIZE);
			m_pRect->Update();
		}

		if (g_pKeyManager->isStayKeyDown(VK_LBUTTON))
		{
			switch (m_ePType)
			{
			case PALETTE_TYPE::Terrain:
				m_stTiles[y][x].nTIndex = m_stSelected.nTIndex;
				m_stTiles[y][x].eTType = m_stSelected.eTType;
				break;
			case PALETTE_TYPE::Object:
				m_stTiles[y][x].nOIndex = m_stSelected.nOIndex;
				m_stTiles[y][x].eOType = m_stSelected.eOType;
				break;
			}
		}
		else if (g_pKeyManager->isStayKeyDown(VK_RBUTTON))
		{
			m_stTiles[y][x].eOType = OBJECT_TYPE::None;
		}
	}

	if (g_pKeyManager->isStayKeyDown(VK_CONTROL) && g_pKeyManager->isOnceKeyDown('S'))
	{
		//맵 저장
		
		for (int i = 0; i < NUM_TILE_Y; i++)
		{
			for (int j = 0; j < NUM_TILE_X; j++)
			{
				wstring wStr = L"Tile_" + to_wstring(j) + L"_" + to_wstring(i);
				//Terrian Index
				g_pFileManager->AddSaveInt(wStr, L"Terrian Index", m_stTiles[i][j].nTIndex);
				//Terrian Type
				g_pFileManager->AddSaveInt(wStr, L"Terrian Type", (int)m_stTiles[i][j].eTType);
				//Object Index
				g_pFileManager->AddSaveInt(wStr, L"Object Index", m_stTiles[i][j].nOIndex);
				//Object Type
				g_pFileManager->AddSaveInt(wStr, L"Object Type", (int)m_stTiles[i][j].eOType);
			}
		}
		g_pFileManager->IniSave(L"MapInfo");
	}
	

	TestUpdate();
}

void MapTool::Render()
{
	// 팔레트 영역
	for (int i = 0; i < m_ptUVSize.y; i++)
	{
		for (int j = 0; j < m_ptUVSize.x; j++)
		{
			switch (m_ePType)
			{
			case PALETTE_TYPE::Terrain:
				m_vecTerrain[i * m_ptUVSize.x + j]->SetConstantScale(PALETTE_TILE_SIZE(m_ptUVSize.x), PALETTE_TILE_SIZE(m_ptUVSize.x));
				m_vecTerrain[i * m_ptUVSize.x + j]->SetLBPosition(j * PALETTE_TILE_SIZE(m_ptUVSize.x), i * PALETTE_TILE_SIZE(m_ptUVSize.x));
				m_vecTerrain[i * m_ptUVSize.x + j]->UpdateNRender();
				break;
			case PALETTE_TYPE::Object:
				m_vecObject[i * m_ptUVSize.x + j]->SetConstantScale(PALETTE_TILE_SIZE(m_ptUVSize.x), PALETTE_TILE_SIZE(m_ptUVSize.x));
				m_vecObject[i * m_ptUVSize.x + j]->SetLBPosition(j * PALETTE_TILE_SIZE(m_ptUVSize.x), i * PALETTE_TILE_SIZE(m_ptUVSize.x));
				m_vecObject[i * m_ptUVSize.x + j]->UpdateNRender();
				break;
			}
		}
	}

	// 드로잉 영역
	for (int i = 0; i < NUM_TILE_Y; i++)
	{
		for (int j = 0; j < NUM_TILE_X; j++)
		{
			// 지형
			int tileTIndex = m_stTiles[i][j].nTIndex;
			m_vecTerrain[tileTIndex]->SetConstantScale(TILE_SIZE, TILE_SIZE);
			m_vecTerrain[tileTIndex]->SetLBPosition(j * TILE_SIZE + TOOL_AREA_X, i * TILE_SIZE);
			m_vecTerrain[tileTIndex]->UpdateNRender();

			// 오브젝트
			if (m_stTiles[i][j].eOType == OBJECT_TYPE::None) continue;

			int tileOIndex = m_stTiles[i][j].nOIndex;
			m_vecObject[tileOIndex]->SetConstantScale(TILE_SIZE, TILE_SIZE);
			m_vecObject[tileOIndex]->SetLBPosition(j * TILE_SIZE + TOOL_AREA_X, i * TILE_SIZE);
			m_vecObject[tileOIndex]->UpdateNRender();
		}
	}

	if (m_pRect)
		m_pRect->Render();

	TestRender();
}

void MapTool::Release()
{
	SAFE_DELETE(m_pSelectUI);
	SAFE_DELETE(m_pRect);

	for (int i = 0; i < m_vecTerrain.size(); i++)
		SAFE_DELETE(m_vecTerrain[i]);
	m_vecTerrain.clear();

	TestRelease();
}
