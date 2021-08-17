#pragma once
#define TILE_SIZE	32
#define NUM_TILE_X	50
#define NUM_TILE_Y	50

#define TILESET_SIZE 24
#define NUM_TILE_U	11
#define NUM_TILE_V	11

#define GET_TILE_POINT(X,Y) POINT{(LONG)((X) / TILE_SIZE), (LONG)((Y) / TILE_SIZE)}
#define GET_TILE_POSITION(P) D3DXVECTOR2{(float)(P.x * TILE_SIZE + TILE_SIZE * 0.5f),(float(P.y * TILE_SIZE + TILE_SIZE * 0.5f))}
#define GET_TILE_LBPOSITION(P) D3DXVECTOR2{(float)(P.x * TILE_SIZE), (float)(P.y * TILE_SIZE)}

#define GET_TILESET_LBPOSITON(P) D3DXVECTOR2{(float)(P.x * TILESET_SIZE), (float)(P.y * TILESET_SIZE)}

enum class TERRAIN_TYPE { Walkable, Wall, Ceiling,Unwalkable, Max };
enum class OBJECT_TYPE { None, Breakable, Unbreakable, Max };
enum class UNIT_TYPE { None, Player, NPC, BOSS, Max };

struct tagTileInfo
{
	TERRAIN_TYPE	eTType;
	int				nTIndex;
	OBJECT_TYPE		eOType;
	int				nOIndex;
	UNIT_TYPE		eUType;
	int				nUIndex;
};