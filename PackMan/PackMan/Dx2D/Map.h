#pragma once
#include "TileInfo.h"

class Map
{
private:
	vector<Sprite*>		m_vecTerrain;		// ���� �̹���
	vector<Sprite*>		m_vecObject;		// ������Ʈ �̹���
	tagTileInfo			m_stTiles[NUM_TILE_Y][NUM_TILE_X];
	vector<POINT>		m_vecRoutes; //�̵� ������ ����Point

public:
	Map();
	~Map();

	void LoadMap();
	void Render();

	tagTileInfo GetTileInfo(LONG x, LONG y) { return m_stTiles[y][x]; }
	tagTileInfo GetTileInfo(POINT pt) { return GetTileInfo(pt.x, pt.y); }

	vector<POINT>& GetVectorRoute() { return m_vecRoutes; }


};

