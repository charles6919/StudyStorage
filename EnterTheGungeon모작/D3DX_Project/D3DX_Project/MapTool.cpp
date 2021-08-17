#include "pch.h"
#include "MapTool.h"

void MapTool::Init()
{
	m_nCurrIndex = 0;
	m_vCameraPos = {0, 0};
	g_pCamera->SetTarget(&m_vCameraPos);
	g_pCamera->SetMapSize(TILE_SIZE * NUM_TILE_X + TOOL_AREA_X, TILE_SIZE * NUM_TILE_Y);
	g_pCamera->Update();

	//생성부
	m_pPaletteBackground= new Sprite(L"Pallete_Background");
	m_pPaletteBackground->SetConstantScale(TOOL_AREA_X, WINSIZEY);
	m_pPaletteBackground->SetLBPosition(g_pCamera->GetPosition().x + (WINSIZEX - TOOL_AREA_X), g_pCamera->GetPosition().y);
	m_pPaletteBackground->Update();

	m_pRtSelect				= new Rect;

	m_pBtnRoom					= new Button;
	m_pBtnDoor					= new Button;
	//m_pBtnTileSet				= new Button;
	//m_pBtnObjectSet			= new Button;
	//m_pBtnNpcSet				= new Button;
	//m_pBtnEraser				= new Button;
	//m_pBtnPageUp				= new Button;
	//m_pBtnPageDown			= new Button;
	m_pBtnBack					= new Button;
	m_pBtnSave					= new Button;
	m_pBtnTitle					= new Button;
	m_pBtnTerrain				= new Button;
	m_pBtnWall					= new Button;
	m_pBtnCeiling				= new Button;

	Sprite* pSprite				= new Sprite(L"Wood_Room");
	pSprite->SetConstantScale(TOOL_AREA_X - 100, TOOL_AREA_X - 100);
	pSprite->SetLBPosition(PALETTE_LBPOSITION_X + m_pPaletteBackground->GetPosition().x - m_pPaletteBackground->GetWidth() * 0.5f , PALETTE_LBPOSITION_Y  + m_pPaletteBackground->GetPosition().y - m_pPaletteBackground->GetHeight() * 0.5f);
	pSprite->Update();
	m_vecRoom.push_back(pSprite);

	pSprite = new Sprite(L"Stone_Room");
	pSprite->SetConstantScale(TOOL_AREA_X - 100, TOOL_AREA_X - 100);
	pSprite->SetLBPosition(PALETTE_LBPOSITION_X + m_pPaletteBackground->GetPosition().x - m_pPaletteBackground->GetWidth() * 0.5f, PALETTE_LBPOSITION_Y + m_pPaletteBackground->GetPosition().y - m_pPaletteBackground->GetHeight() * 0.5f);
	pSprite->Update();
	m_vecRoom.push_back(pSprite);

	pSprite = new Sprite(L"Normal_Door_Palette");
	pSprite->SetConstantScale(TOOL_AREA_X - 200, TOOL_AREA_X - 200);
	pSprite->SetLBPosition(PALETTE_LBPOSITION_X + m_pPaletteBackground->GetPosition().x - m_pPaletteBackground->GetWidth() * 0.5f, PALETTE_LBPOSITION_Y + m_pPaletteBackground->GetPosition().y - m_pPaletteBackground->GetHeight() * 0.5f);
	pSprite->Update();
	m_vecDoor.push_back(pSprite);

	//초기화
	m_pBtnRoom->Init();
	m_pBtnDoor->Init();
	//m_pBtnTileSet->Init();
	//m_pBtnObjectSet->Init();
	//m_pBtnNpcSet->Init();
	//m_pBtnEraser->Init();
	//m_pBtnPageUp->Init();
	//m_pBtnPageDown->Init();
	m_pBtnBack->Init();
	m_pBtnSave->Init();
	m_pBtnTitle->Init();
	m_pBtnTerrain->Init();
	m_pBtnWall->Init();
	m_pBtnCeiling->Init();

	//버튼 애니메이션 세팅
	m_pBtnRoom		->SetAnimation_Sprites(L"Room_Button");
	m_pBtnDoor		->SetAnimation_Sprites(L"Door_Button");
	//m_pBtnTileSet	->SetAnimation_Sprites(L"Room_Button");
	//m_pBtnObjectSet	->SetAnimation_Sprites(L"Room_Button");
	//m_pBtnNpcSet	->SetAnimation_Sprites(L"Room_Button");
	//m_pBtnEraser	->SetAnimation_Sprites(L"Room_Button");
	//m_pBtnPageUp	->SetAnimation_Sprites(L"Room_Button");
	//m_pBtnPageDown	->SetAnimation_Sprites(L"Room_Button");
	m_pBtnBack		->SetAnimation_Sprites(L"Back_Button");
	m_pBtnSave		->SetAnimation_Sprites(L"Save_Button");
	m_pBtnTitle		->SetAnimation_Sprites(L"Title_Btn");
	m_pBtnTerrain	->SetAnimation_Sprites(L"Terrain_Btn");
	m_pBtnWall		->SetAnimation_Sprites(L"Walls_Btn");
	m_pBtnCeiling	->SetAnimation_Sprites(L"Ceiling_Btn");

	

	//position, scale 세팅
	m_pBtnBack->SetScale(D3DXVECTOR2(100,50));
	m_pBtnBack->SetLBPosition(D3DXVECTOR2(m_pPaletteBackground->GetPosition().x - m_pPaletteBackground->GetWidth() * 0.5f, m_pPaletteBackground->GetPosition().y - m_pPaletteBackground->GetHeight() * 0.5f));
	m_pBtnBack->Update();
	
	m_isSettingEndDoor = true;
	m_ePaletteType = PALETTE_TYPE::Select;

	for (int i = NUM_TILE_V - 1; i >= 0; i--)
	{
		for (int j = 0; j < NUM_TILE_U; j++)
		{
			Sprite* pSprite = new Sprite(L"TileTerrain", NUM_TILE_U, NUM_TILE_V, i * NUM_TILE_U + j);
			m_vecTerrain.push_back(pSprite);
		}
	}

	for (int i = NUM_TILE_V - 1; i >= 0; i--)
	{
		for (int j = 0; j < NUM_TILE_U; j++)
		{
			Sprite* pSprite = new Sprite(L"Walls", NUM_TILE_U, NUM_TILE_V, i * NUM_TILE_U + j);
			m_vecWall.push_back(pSprite);
		}
	}

	for (int i = NUM_TILE_V - 1; i >= 0; i--)
	{
		for (int j = 0; j < NUM_TILE_U; j++)
		{
			Sprite* pSprite = new Sprite(L"Ceiling", NUM_TILE_U, NUM_TILE_V, i * NUM_TILE_U + j);
			m_vecCeiling.push_back(pSprite);
		}
	}


	for (int y = 0; y < NUM_TILE_Y; y++)
	{
		for (int x = 0; x < NUM_TILE_X; x++)
		{
			m_stTiles[y][x].eTType = TERRAIN_TYPE::Unwalkable;
			m_stTiles[y][x].nTIndex = 0;
			m_stTiles[y][x].eOType = OBJECT_TYPE::None;
			m_stTiles[y][x].nOIndex = 0;
			m_stTiles[y][x].eUType = UNIT_TYPE::None;
			m_stTiles[y][x].nUIndex = 0;
		}
	}

}

void MapTool::Update()
{
	if (g_pKeyManager->IsStayKeyDown('W'))
	{
		m_vCameraPos.y += 500 * g_pTimeManager->GetDeltaTime();
	}
	else if(g_pKeyManager->IsStayKeyDown('S'))
	{
		m_vCameraPos.y -= 500 * g_pTimeManager->GetDeltaTime();
	}

	if (g_pKeyManager->IsStayKeyDown('A'))
	{
		m_vCameraPos.x -= 500 * g_pTimeManager->GetDeltaTime();
	}
	else if (g_pKeyManager->IsStayKeyDown('D'))
	{
		m_vCameraPos.x += 500 * g_pTimeManager->GetDeltaTime();
	}

	g_pCamera->Update();
	m_pPaletteBackground->SetLBPosition(g_pCamera->GetPosition().x + (WINSIZEX - TOOL_AREA_X), g_pCamera->GetPosition().y );
	m_pPaletteBackground->Update();
	
	//팔레트
	if (m_ePaletteType == PALETTE_TYPE::Select)
	{
		if (m_pBtnRoom)
		{
			m_pBtnRoom->SetScale(D3DXVECTOR2(TOOL_AREA_X - 50, 50));
			m_pBtnRoom->SetPosition(D3DXVECTOR2(m_pPaletteBackground->GetPosition().x,
				m_pPaletteBackground->GetPosition().y + HALFSIZEY - 50));

			m_pBtnRoom->Update();
			if (m_pBtnRoom->GetButtonState() == Button_State::ClickUp)
			{
				m_ePaletteType = PALETTE_TYPE::Room;
				m_nCurrIndex = 0;
				m_nCurrBrush = 0;
			}
		}	

		if (m_pBtnDoor)
		{
			m_pBtnDoor->SetScale(D3DXVECTOR2(TOOL_AREA_X - 50, 50));
			m_pBtnDoor->SetPosition(D3DXVECTOR2(m_pPaletteBackground->GetPosition().x,
				m_pPaletteBackground->GetPosition().y + HALFSIZEY - 50 * 2));
		
			m_pBtnDoor->Update();
			if (m_pBtnDoor->GetButtonState() == Button_State::ClickUp)
			{
				m_ePaletteType = PALETTE_TYPE::Terrain;
				m_nCurrIndex = 0;
				m_nCurrBrush = 0;
			}
		}

		if (m_pBtnTerrain)
		{
			m_pBtnTerrain->SetScale(D3DXVECTOR2(TOOL_AREA_X - 50, 50));
			m_pBtnTerrain->SetPosition(D3DXVECTOR2(m_pPaletteBackground->GetPosition().x,
				m_pPaletteBackground->GetPosition().y + HALFSIZEY - 50 * 2));

			m_pBtnTerrain->Update();
			if (m_pBtnTerrain->GetButtonState() == Button_State::ClickUp)
			{
				m_ePaletteType = PALETTE_TYPE::Terrain;
				m_nCurrIndex = 0;
				m_nCurrBrush = 0;
			}
		}

		if (m_pBtnSave)
		{
			m_pBtnSave->SetScale(D3DXVECTOR2(TOOL_AREA_X - 50, 50));
			m_pBtnSave->SetPosition(D3DXVECTOR2(m_pPaletteBackground->GetPosition().x,
				m_pPaletteBackground->GetPosition().y + HALFSIZEY - 50 * 6));
			m_pBtnSave->Update();
			if (m_pBtnSave->GetButtonState() == Button_State::ClickUp)
			{
				SaveTileInfo();
			}
		}

	}
	else if (m_ePaletteType == PALETTE_TYPE::Room)
	{

		ImGui::InputInt("Brush",&m_nCurrBrush);

		m_vecRoom[m_nCurrIndex]->Update();
		if (g_pKeyManager->IsOnceKeyDown(VK_RIGHT))
		{
			if (m_nCurrIndex < m_vecRoom.size() - 1)
			{
				m_nCurrIndex++;
			}
		}
		else if (g_pKeyManager->IsOnceKeyDown(VK_LEFT))
		{
			if (m_nCurrIndex > 0)
			{
				m_nCurrIndex--;
			}
		}

		//룸 팔레트영역
		if (PointInRect(m_vecRoom[m_nCurrIndex]->GetPosition(), D3DXVECTOR2(TOOL_AREA_X - 100, TOOL_AREA_X - 100), D3DXVECTOR2(g_ptMouse.x + g_pCamera->GetPosition().x, g_ptMouse.y + g_pCamera->GetPosition().y)))
		{
			m_vecRoom[m_nCurrIndex]->SetBorder(true);

			if (g_pKeyManager->IsOnceKeyUp(VK_LBUTTON))
			{
				m_nCurrBrush = m_nCurrIndex;
			}
		}
		else
		{
			m_vecRoom[m_nCurrIndex]->SetBorder(false);
		}
		

		//작업영역
		if (!PointInRect(m_pPaletteBackground->GetPosition(), D3DXVECTOR2(TOOL_AREA_X , WINSIZEY), D3DXVECTOR2(g_ptMouse.x + g_pCamera->GetPosition().x, g_ptMouse.y + g_pCamera->GetPosition().y)))
		{
 
			POINT mousePt = { g_pCamera->GetPosition().x + g_ptMouse.x, g_pCamera->GetPosition().y + g_ptMouse.y };
			POINT indexMousePt = { mousePt.x / TILE_SIZE, (mousePt.y / TILE_SIZE) + 1 };

			
			if (g_pKeyManager->IsOnceKeyUp(VK_LBUTTON))
			{
				m_enableToRoomSetting = true;
				for (int i = 0; i < m_ptRoomLT.y - m_ptRoomRB.y ; i++)
				{
					for (int j = 0; j < m_ptRoomRB.x - m_ptRoomLT.x; j++)
					{
						POINT pt = { m_ptRoomLT.x + j, m_ptRoomRB.y + i };

						if (m_stTiles[pt.y][pt.x].nTIndex != 0) //세팅되는 타일중 비어있는 타일(0)이 없다면 세팅하지 않는다.
						{
							m_enableToRoomSetting = false;
							m_vecRoomPt.clear();
							i = m_ptRoomLT.y - m_ptRoomRB.y;
							break;
						}
				

						m_vecRoomPt.push_back(pt);

						if (i == (m_ptRoomLT.y - m_ptRoomRB.y) -1 && j == (m_ptRoomRB.x - m_ptRoomLT.x) - 1)
						{
							if (m_nCurrBrush == 0)//나무방
							{
								for (int k = 0; k < m_vecRoomPt.size(); k++)
								{
									if (k == 0)//LB
									{
										m_stTiles[m_vecRoomPt[k].y][m_vecRoomPt[k].x].nTIndex = 55;
										m_stTiles[m_vecRoomPt[k].y][m_vecRoomPt[k].x].eTType = TERRAIN_TYPE::Ceiling;
									}
									else if (m_vecRoomPt[k].y == m_ptRoomRB.y && m_vecRoomPt[k].x == m_ptRoomRB.x - 1)//RB
									{
										m_stTiles[m_vecRoomPt[k].y][m_vecRoomPt[k].x].nTIndex = 56;
										m_stTiles[m_vecRoomPt[k].y][m_vecRoomPt[k].x].eTType = TERRAIN_TYPE::Ceiling;
									}
									else if (m_vecRoomPt[k].y == m_ptRoomRB.y)//B
									{
										m_stTiles[m_vecRoomPt[k].y][m_vecRoomPt[k].x].nTIndex = 36;
										m_stTiles[m_vecRoomPt[k].y][m_vecRoomPt[k].x].eTType = TERRAIN_TYPE::Ceiling;
									}
									else if (m_vecRoomPt[k].x == m_ptRoomLT.x && m_vecRoomPt[k].y == m_ptRoomLT.y - 1)//LT
									{ 
										m_stTiles[m_vecRoomPt[k].y][m_vecRoomPt[k].x].nTIndex = 66;
										m_stTiles[m_vecRoomPt[k].y][m_vecRoomPt[k].x].eTType = TERRAIN_TYPE::Ceiling;
									}
									else if (m_vecRoomPt[k].x == m_ptRoomRB.x - 1 && m_vecRoomPt[k].y == m_ptRoomLT.y - 1)//RT
									{
										m_stTiles[m_vecRoomPt[k].y][m_vecRoomPt[k].x].nTIndex = 67;
										m_stTiles[m_vecRoomPt[k].y][m_vecRoomPt[k].x].eTType = TERRAIN_TYPE::Ceiling;
									}
									else if (m_vecRoomPt[k].x == m_ptRoomLT.x)//L
									{
										m_stTiles[m_vecRoomPt[k].y][m_vecRoomPt[k].x].nTIndex = 25;
										m_stTiles[m_vecRoomPt[k].y][m_vecRoomPt[k].x].eTType = TERRAIN_TYPE::Ceiling;
									}
									else if (m_vecRoomPt[k].x == m_ptRoomRB.x - 1)//R
									{
										m_stTiles[m_vecRoomPt[k].y][m_vecRoomPt[k].x].nTIndex = 14;
										m_stTiles[m_vecRoomPt[k].y][m_vecRoomPt[k].x].eTType = TERRAIN_TYPE::Ceiling;
									}
									else if (m_vecRoomPt[k].y == m_ptRoomLT.y - 1)//T
									{
										m_stTiles[m_vecRoomPt[k].y][m_vecRoomPt[k].x].nTIndex = 3;
										m_stTiles[m_vecRoomPt[k].y][m_vecRoomPt[k].x].eTType = TERRAIN_TYPE::Ceiling;
									}
									else if (m_vecRoomPt[k].y == m_ptRoomLT.y - 2)//T-1
									{
										m_stTiles[m_vecRoomPt[k].y][m_vecRoomPt[k].x].nTIndex = 11;
										m_stTiles[m_vecRoomPt[k].y][m_vecRoomPt[k].x].eTType = TERRAIN_TYPE::Wall;
									}
									else if (m_vecRoomPt[k].y == m_ptRoomLT.y - 3)//T-2
									{
										m_stTiles[m_vecRoomPt[k].y][m_vecRoomPt[k].x].nTIndex = 0;
										m_stTiles[m_vecRoomPt[k].y][m_vecRoomPt[k].x].eTType = TERRAIN_TYPE::Wall;
									}
									else
									{
										m_stTiles[m_vecRoomPt[k].y][m_vecRoomPt[k].x].nTIndex = 11;
										m_stTiles[m_vecRoomPt[k].y][m_vecRoomPt[k].x].eTType = TERRAIN_TYPE::Walkable;
									}
								}
								
							}
							else if (m_nCurrBrush == 1)//돌방
							{
								for (int k = 0; k < m_vecRoomPt.size(); k++)
								{
									if (k == 0)//LB
									{
										m_stTiles[m_vecRoomPt[k].y][m_vecRoomPt[k].x].nTIndex = 55 + 4;
										m_stTiles[m_vecRoomPt[k].y][m_vecRoomPt[k].x].eTType = TERRAIN_TYPE::Ceiling;
									}
									else if (m_vecRoomPt[k].y == m_ptRoomRB.y && m_vecRoomPt[k].x == m_ptRoomRB.x - 1)//RB
									{
										m_stTiles[m_vecRoomPt[k].y][m_vecRoomPt[k].x].nTIndex = 56 + 4;
										m_stTiles[m_vecRoomPt[k].y][m_vecRoomPt[k].x].eTType = TERRAIN_TYPE::Ceiling;
									}
									else if (m_vecRoomPt[k].y == m_ptRoomRB.y)//B
									{
										m_stTiles[m_vecRoomPt[k].y][m_vecRoomPt[k].x].nTIndex = 36 + 4;
										m_stTiles[m_vecRoomPt[k].y][m_vecRoomPt[k].x].eTType = TERRAIN_TYPE::Ceiling;
									}
									else if (m_vecRoomPt[k].x == m_ptRoomLT.x && m_vecRoomPt[k].y == m_ptRoomLT.y - 1)//LT
									{
										m_stTiles[m_vecRoomPt[k].y][m_vecRoomPt[k].x].nTIndex = 66 + 4;
										m_stTiles[m_vecRoomPt[k].y][m_vecRoomPt[k].x].eTType = TERRAIN_TYPE::Ceiling;
									}
									else if (m_vecRoomPt[k].x == m_ptRoomRB.x - 1 && m_vecRoomPt[k].y == m_ptRoomLT.y - 1)//RT
									{
										m_stTiles[m_vecRoomPt[k].y][m_vecRoomPt[k].x].nTIndex = 67 + 4;
										m_stTiles[m_vecRoomPt[k].y][m_vecRoomPt[k].x].eTType = TERRAIN_TYPE::Ceiling;
									}
									else if (m_vecRoomPt[k].x == m_ptRoomLT.x)//L
									{
										m_stTiles[m_vecRoomPt[k].y][m_vecRoomPt[k].x].nTIndex = 25 + 4;
										m_stTiles[m_vecRoomPt[k].y][m_vecRoomPt[k].x].eTType = TERRAIN_TYPE::Ceiling;
									}
									else if (m_vecRoomPt[k].x == m_ptRoomRB.x - 1)//R
									{
										m_stTiles[m_vecRoomPt[k].y][m_vecRoomPt[k].x].nTIndex = 14 + 4;
										m_stTiles[m_vecRoomPt[k].y][m_vecRoomPt[k].x].eTType = TERRAIN_TYPE::Ceiling;
									}
									else if (m_vecRoomPt[k].y == m_ptRoomLT.y - 1)//T
									{
										m_stTiles[m_vecRoomPt[k].y][m_vecRoomPt[k].x].nTIndex = 3 + 4;
										m_stTiles[m_vecRoomPt[k].y][m_vecRoomPt[k].x].eTType = TERRAIN_TYPE::Ceiling;
									}
									else if (m_vecRoomPt[k].y == m_ptRoomLT.y - 2)//T-1
									{
										m_stTiles[m_vecRoomPt[k].y][m_vecRoomPt[k].x].nTIndex = 34;
										m_stTiles[m_vecRoomPt[k].y][m_vecRoomPt[k].x].eTType = TERRAIN_TYPE::Wall;
									}
									else if (m_vecRoomPt[k].y == m_ptRoomLT.y - 3)//T-2
									{
										m_stTiles[m_vecRoomPt[k].y][m_vecRoomPt[k].x].nTIndex = 23;
										m_stTiles[m_vecRoomPt[k].y][m_vecRoomPt[k].x].eTType = TERRAIN_TYPE::Wall;
									}
									else
									{
										m_stTiles[m_vecRoomPt[k].y][m_vecRoomPt[k].x].nTIndex = 23;
										m_stTiles[m_vecRoomPt[k].y][m_vecRoomPt[k].x].eTType = TERRAIN_TYPE::Walkable;
									}
								}

							}

							m_vecRoomPt.clear();
						}
					}
				}
			}
			else if (g_pKeyManager->IsStayKeyDown(VK_LBUTTON))
			{
				if (indexMousePt.x > m_ptRoomLT.x && indexMousePt.y < m_ptRoomLT.y)
				{
					m_ptRoomRB.x = indexMousePt.x;
					m_ptRoomRB.y = indexMousePt.y;
				}

				m_enableToRoomSetting = true;

				for (int i = 0; i < m_ptRoomLT.y - m_ptRoomRB.y; i++)
				{
					for (int j = 0; j < m_ptRoomRB.x - m_ptRoomLT.x; j++)
					{
						POINT pt = { m_ptRoomLT.x + j, m_ptRoomRB.y + i };

						if (m_stTiles[pt.y][pt.x].nTIndex != 0) 
							m_enableToRoomSetting = false;
					}
				}

			}
			else
			{
				m_ptRoomLT.x = indexMousePt.x;
				m_ptRoomLT.y = indexMousePt.y;

				m_ptRoomRB.x = m_ptRoomLT.x + 1;
				m_ptRoomRB.y = m_ptRoomLT.y - 1;

				for (int i = 0; i < m_ptRoomLT.y - m_ptRoomRB.y; i++)
				{
					for (int j = 0; j < m_ptRoomRB.x - m_ptRoomLT.x; j++)
					{
						POINT pt = { m_ptRoomLT.x + j, m_ptRoomRB.y + i };

						if (m_stTiles[pt.y][pt.x].nTIndex != 0)
							m_enableToRoomSetting = false;
					}
				}

			}
		}

		if (m_pBtnBack)
		{
			m_pBtnBack->SetLBPosition(D3DXVECTOR2(m_pPaletteBackground->GetPosition().x - m_pPaletteBackground->GetWidth() * 0.5f, m_pPaletteBackground->GetPosition().y - m_pPaletteBackground->GetHeight() * 0.5f));
			m_pBtnBack->Update();
			if (m_pBtnBack->GetButtonState() == Button_State::ClickUp)
			{
				m_ePaletteType = PALETTE_TYPE::Select;
			}
		}
		

	}
	else if (m_ePaletteType == PALETTE_TYPE::Door)
	{
		//도어 파레트 영역
		if (PointInRect(m_vecDoor[m_nCurrIndex]->GetPosition(), D3DXVECTOR2(TOOL_AREA_X - 200, TOOL_AREA_X - 200), D3DXVECTOR2(g_ptMouse.x + g_pCamera->GetPosition().x, g_ptMouse.y + g_pCamera->GetPosition().y)))
		{
			m_vecDoor[m_nCurrIndex]->SetBorder(true);

			if (g_pKeyManager->IsOnceKeyUp(VK_LBUTTON))
			{
				m_nCurrBrush = m_nCurrIndex;
			}
		}
		else
		{
			m_vecDoor[m_nCurrIndex]->SetBorder(false);
		}

		if (!PointInRect(m_pPaletteBackground->GetPosition(), D3DXVECTOR2(TOOL_AREA_X, WINSIZEY), D3DXVECTOR2(g_ptMouse.x + g_pCamera->GetPosition().x, g_ptMouse.y + g_pCamera->GetPosition().y)))
		{

			POINT mousePt = { g_pCamera->GetPosition().x + g_ptMouse.x, g_pCamera->GetPosition().y + g_ptMouse.y };
			m_ptCurrTile = { mousePt.x / TILE_SIZE, (mousePt.y / TILE_SIZE) };

			if (m_stTiles[m_ptCurrTile.y][m_ptCurrTile.x].eTType == TERRAIN_TYPE::Wall ||
				m_stTiles[m_ptCurrTile.y][m_ptCurrTile.x].eTType == TERRAIN_TYPE::Ceiling)
			{
				m_enableToDoorSetting = true;
			}
			else
			{
				m_enableToDoorSetting = false;
			}

			if (g_pKeyManager->IsOnceKeyUp(VK_LBUTTON))
			{
				int a = 0;
			}
			else
			{

			}


		}

		if (m_pBtnBack)
		{
			m_pBtnBack->SetLBPosition(D3DXVECTOR2(m_pPaletteBackground->GetPosition().x - m_pPaletteBackground->GetWidth() * 0.5f, m_pPaletteBackground->GetPosition().y - m_pPaletteBackground->GetHeight() * 0.5f));
			m_pBtnBack->Update();
			if (m_pBtnBack->GetButtonState() == Button_State::ClickUp)
			{
				m_ePaletteType = PALETTE_TYPE::Select;
			}
		}
	}
	else if (m_ePaletteType == PALETTE_TYPE::Terrain)
	{
		if (PointInRect(m_vecRoom[m_nCurrIndex]->GetPosition(), D3DXVECTOR2(TOOL_AREA_X - 100, TOOL_AREA_X - 100), D3DXVECTOR2(g_ptMouse.x + g_pCamera->GetPosition().x, g_ptMouse.y + g_pCamera->GetPosition().y)))
		{
			
		}
	}
	else if (m_ePaletteType == PALETTE_TYPE::ObjectSet)
	{

	}
	else if (m_ePaletteType == PALETTE_TYPE::NpcSet)
	{

	}


}

void MapTool::Render()
{

	for (int y = 0; y < NUM_TILE_Y; y++)
	{
		for (int x = 0; x < NUM_TILE_X; x++)
		{
			switch (m_stTiles[y][x].eTType)
			{
			case TERRAIN_TYPE::Walkable:
				m_vecTerrain[m_stTiles[y][x].nTIndex]->SetConstantScale(D3DXVECTOR2(TILE_SIZE, TILE_SIZE));
				m_vecTerrain[m_stTiles[y][x].nTIndex]->SetLBPosition(D3DXVECTOR2(x * TILE_SIZE, y * TILE_SIZE));
				m_vecTerrain[m_stTiles[y][x].nTIndex]->UpdateNRender();
				break;

			case TERRAIN_TYPE::Wall:
				m_vecWall[m_stTiles[y][x].nTIndex]->SetConstantScale(D3DXVECTOR2(TILE_SIZE, TILE_SIZE));
				m_vecWall[m_stTiles[y][x].nTIndex]->SetLBPosition(D3DXVECTOR2(x * TILE_SIZE, y * TILE_SIZE));
				m_vecWall[m_stTiles[y][x].nTIndex]->UpdateNRender();
				break;

			case TERRAIN_TYPE::Ceiling:
				m_vecCeiling[m_stTiles[y][x].nTIndex]->SetConstantScale(D3DXVECTOR2(TILE_SIZE, TILE_SIZE));
				m_vecCeiling[m_stTiles[y][x].nTIndex]->SetLBPosition(D3DXVECTOR2(x * TILE_SIZE, y * TILE_SIZE));
				m_vecCeiling[m_stTiles[y][x].nTIndex]->UpdateNRender();
				break;
			}

			

			//m_vecObject[m_stTiles[y][x].nOIndex]->SetConstantScale(D3DXVECTOR2(TILE_SIZE, TILE_SIZE));
			//m_vecObject[m_stTiles[y][x].nOIndex]->SetLBPosition(D3DXVECTOR2(x * TILE_SIZE, y * TILE_SIZE));
			//m_vecObject[m_stTiles[y][x].nOIndex]->UpdateNRender();
			//
			//m_vecUnit[m_stTiles[y][x].nUIndex]->SetConstantScale(D3DXVECTOR2(TILE_SIZE, TILE_SIZE));
			//m_vecUnit[m_stTiles[y][x].nUIndex]->SetLBPosition(D3DXVECTOR2(x * TILE_SIZE, y * TILE_SIZE));
			//m_vecUnit[m_stTiles[y][x].nUIndex]->UpdateNRender();
		}
	}

	m_pPaletteBackground->Render();

	if (m_ePaletteType == PALETTE_TYPE::Select)
	{
		if (m_pBtnRoom)
			m_pBtnRoom->Render();

		if (m_pBtnDoor)
			m_pBtnDoor->Render();

		if (m_pBtnSave)
			m_pBtnSave->Render();

	}
	else if (m_ePaletteType == PALETTE_TYPE::Room)
	{
		m_pRtSelect->SetSize(D3DXVECTOR2{ (float)((m_ptRoomRB.x - m_ptRoomLT.x) * TILE_SIZE) ,  (float)((m_ptRoomLT.y - m_ptRoomRB.y) * TILE_SIZE) });
		m_pRtSelect->SetLBPosition(D3DXVECTOR2{ (float)(m_ptRoomLT.x * TILE_SIZE), (float)((m_ptRoomRB.y) * TILE_SIZE) });
		if (m_enableToRoomSetting)
			m_pRtSelect->SetColor(D3DXCOLOR(0, 1, 0, 0.5f));
		else
			m_pRtSelect->SetColor(D3DXCOLOR(1, 0, 0, 0.5f));
		m_pRtSelect->UpdateNRender();

		m_vecRoom[m_nCurrIndex]->SetLBPosition(PALETTE_LBPOSITION_X + m_pPaletteBackground->GetPosition().x - m_pPaletteBackground->GetWidth() * 0.5f, PALETTE_LBPOSITION_Y + m_pPaletteBackground->GetPosition().y - m_pPaletteBackground->GetHeight() * 0.5f);
		m_vecRoom[m_nCurrIndex]->UpdateNRender();

		m_pBtnBack->Render();

	}
	else if (m_ePaletteType == PALETTE_TYPE::Door)
	{
		m_pRtSelect->SetSize(D3DXVECTOR2{ (float)(TILE_SIZE) ,  (float)(TILE_SIZE) });
		m_pRtSelect->SetLBPosition(D3DXVECTOR2{ (float)(m_ptCurrTile.x * TILE_SIZE), (float)((m_ptCurrTile.y) * TILE_SIZE) });
		if (m_enableToDoorSetting)
			m_pRtSelect->SetColor(D3DXCOLOR(0, 1, 0, 0.5f));
		else
			m_pRtSelect->SetColor(D3DXCOLOR(1, 0, 0, 0.5f));
		m_pRtSelect->UpdateNRender();

		m_vecDoor[m_nCurrIndex]->SetLBPosition(PALETTE_LBPOSITION_X + m_pPaletteBackground->GetPosition().x - m_pPaletteBackground->GetWidth() * 0.5f, PALETTE_LBPOSITION_Y + m_pPaletteBackground->GetPosition().y - m_pPaletteBackground->GetHeight() * 0.5f);
		m_vecDoor[m_nCurrIndex]->UpdateNRender();

		m_pBtnBack->Render();
	}
	else if (m_ePaletteType == PALETTE_TYPE::Terrain)
	{
		for (int v = 0; v < NUM_TILE_V; v++)
		{
			for (int u = 0; u < NUM_TILE_U; u++)
			{
				POINT pt = { u,v };
				D3DXVECTOR2 pos = GET_TILESET_LBPOSITON(pt);
				m_vecTerrain[u + v * NUM_TILE_U]->SetConstantScale(TILESET_SIZE, TILESET_SIZE);
				m_vecTerrain[u + v * NUM_TILE_U]->SetLBPosition(pos.x + m_pPaletteBackground->GetPosition().x - (NUM_TILE_U * 0.5f * TILESET_SIZE), pos.y + m_pPaletteBackground->GetPosition().y - 100.0f);
				m_vecTerrain[u + v * NUM_TILE_U]->UpdateNRender();
			}
		}
	}
	else if (m_ePaletteType == PALETTE_TYPE::ObjectSet)
	{

	}
	else if (m_ePaletteType == PALETTE_TYPE::NpcSet)
	{

	}
}

void MapTool::Release()
{
	SAFE_DELETE(m_pPaletteBackground);
}

void MapTool::SaveTileInfo()
{
	for (int y = 0; y < NUM_TILE_Y; y++)
	{
		for (int x = 0; x < NUM_TILE_X; x++)
		{
			wstring wStr = L"TILE_INFO(" + to_wstring(y) + L" , " + to_wstring(x) + L" )";
			g_pFileManager->AddSaveTileInfo(wStr, L"TileInfo", m_stTiles[y][x]);
		}
	}
	g_pFileManager->IniSave(L"MAP001-1");
}
