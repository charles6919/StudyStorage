#include "stdafx.h"
#include "Map.h"


Map::Map()
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
}


Map::~Map()
{
	
}

void Map::LoadMap()
{
	for (int i = 0; i < NUM_TILE_Y; i++)
	{
		for (int j = 0; j < NUM_TILE_X; j++)
		{
			wstring wStr = L"Tile_" + to_wstring(j) + L"_" + to_wstring(i);
			//Terrian Index
			m_stTiles[i][j].nTIndex = g_pFileManager->LoadIntegerData(L"MapInfo", wStr, L"Terrian Index");
			//Terrian Type
			m_stTiles[i][j].eTType = (TERRAIN_TYPE)g_pFileManager->LoadIntegerData(L"MapInfo", wStr, L"Terrian Type");
			//Object Index
			m_stTiles[i][j].nOIndex = g_pFileManager->LoadIntegerData(L"MapInfo", wStr, L"Object Index");
			//Object Type
			m_stTiles[i][j].eOType = (OBJECT_TYPE)g_pFileManager->LoadIntegerData(L"MapInfo", wStr, L"Object Type");

			if (m_stTiles[i][j].eOType == OBJECT_TYPE::None && m_stTiles[i][j].eTType != TERRAIN_TYPE::Unwalkable)
			{
				m_vecRoutes.push_back(POINT{j, i});
			}
		}
	}
}

void Map::Render()
{
	for (int i = 0; i < NUM_TILE_Y; i++)
	{
		for (int j = 0; j < NUM_TILE_X; j++)
		{
			// 지형
			int tileTIndex = m_stTiles[i][j].nTIndex;
			m_vecTerrain[tileTIndex]->SetConstantScale(TILE_SIZE, TILE_SIZE);
			m_vecTerrain[tileTIndex]->SetLBPosition(j * TILE_SIZE, i * TILE_SIZE);
			m_vecTerrain[tileTIndex]->UpdateNRender();

			// 오브젝트
			if (m_stTiles[i][j].eOType == OBJECT_TYPE::None) continue;

			int tileOIndex = m_stTiles[i][j].nOIndex;
			m_vecObject[tileOIndex]->SetConstantScale(TILE_SIZE, TILE_SIZE);
			m_vecObject[tileOIndex]->SetLBPosition(j * TILE_SIZE, i * TILE_SIZE);
			m_vecObject[tileOIndex]->UpdateNRender();
		}
	}
}