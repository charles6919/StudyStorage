#include "stdafx.h"
#include "PlayerTest.h"
#include "MapTool.h"
#include "Dijkstra.h"


PlayerTest::PlayerTest()
{
	m_pRect = new Rect;
	m_pRect->SetSize(TILE_SIZE - 4, TILE_SIZE - 4);
}


PlayerTest::~PlayerTest()
{
	SAFE_DELETE(m_pRect);
}

void PlayerTest::Init()
{
	m_ptPosition.x = 0;
	m_ptPosition.y = 0;

	m_pDijkstra = new Dijkstra(m_pMapTool);

	m_fMoveSpeed = 0.2f;
	m_fElapsedTime = 0.0f;
}

void PlayerTest::KeyboardControl()
{
	tagTileInfo* stTile = NULL;
	POINT ptNext = m_ptPosition;

	if (g_pKeyManager->isOnceKeyDown('A') && m_ptPosition.x > 0)
	{
		ptNext.x -= 1;
		stTile = &m_pMapTool->GetTileInfo(ptNext.x, ptNext.y);
	}
	else if (g_pKeyManager->isOnceKeyDown('D') && m_ptPosition.x < NUM_TILE_X - 1)
	{
		ptNext.x += 1;
		stTile = &m_pMapTool->GetTileInfo(ptNext.x, ptNext.y);
	}

	if (g_pKeyManager->isOnceKeyDown('W') && m_ptPosition.y < NUM_TILE_Y - 1)
	{
		ptNext.y += 1;
		stTile = &m_pMapTool->GetTileInfo(ptNext.x, ptNext.y);
	}
	else if (g_pKeyManager->isOnceKeyDown('S') && m_ptPosition.y > 0)
	{
		ptNext.y -= 1;
		stTile = &m_pMapTool->GetTileInfo(ptNext.x, ptNext.y);
	}

	if (stTile)
	{
		if (stTile->eTType == TERRAIN_TYPE::Walkable)
		{
			if (stTile->eOType == OBJECT_TYPE::None)
				m_ptPosition = ptNext;
			else if (stTile->eOType == OBJECT_TYPE::Breakable)
				stTile->eOType = OBJECT_TYPE::None;
		}
	}
}

void PlayerTest::MouseControl()
{
	m_fElapsedTime += g_pTimeManager->GetDeltaTime();

	if (m_fElapsedTime >= m_fMoveSpeed)
	{
		m_fElapsedTime = 0.0f;
		m_ptPosition = m_vecMoveRoute.back();
		m_vecMoveRoute.pop_back();
	}
}

void PlayerTest::Update()
{
	if (m_pDijkstra && g_pKeyManager->isOnceKeyDown(VK_MBUTTON))
	{
		int x = (g_ptMouse.x - TOOL_AREA_X) / TILE_SIZE;
		int y = g_ptMouse.y / TILE_SIZE;
		POINT pt = { x, y };

		m_pDijkstra->StartFindARoute(m_ptPosition, pt, m_vecMoveRoute);
	}

	if (m_vecMoveRoute.empty())
		KeyboardControl();
	else
		MouseControl();

	if (m_pRect)
	{
		m_pRect->SetPosition(TOOL_AREA_X + m_ptPosition.x * TILE_SIZE + TILE_SIZE * 0.5f,
			m_ptPosition.y * TILE_SIZE + TILE_SIZE * 0.5f);
		m_pRect->Update();
	}
}

void PlayerTest::Render()
{
	if (m_pRect)
		m_pRect->Render();
}
