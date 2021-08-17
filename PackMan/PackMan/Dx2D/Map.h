#pragma once
#include "TileInfo.h"

class Map
{
private:
	vector<Sprite*>		m_vecTerrain;		// 지형 이미지
	vector<Sprite*>		m_vecObject;		// 오브젝트 이미지
	tagTileInfo			m_stTiles[NUM_TILE_Y][NUM_TILE_X];
	vector<POINT>		m_vecRoutes; //이동 가능한 지형Point

public:
	Map();
	~Map();

	void LoadMap();
	void Render();

	tagTileInfo GetTileInfo(LONG x, LONG y) { return m_stTiles[y][x]; }
	tagTileInfo GetTileInfo(POINT pt) { return GetTileInfo(pt.x, pt.y); }

	vector<POINT>& GetVectorRoute() { return m_vecRoutes; }


};

