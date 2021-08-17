#pragma once

#define TILE_SIZE 32
#define NUM_TILE_X 32
#define NUM_TILE_Y 22
#define NUM_TILE_U 16
#define NUM_TILE_V 12
#define NUM_OBJECT_UV 16

#define GET_TILE_REALPOINT(X,Y) (POINT{(LONG)(X * TILE_SIZE + TILE_SIZE * 0.5f), (LONG)(Y * TILE_SIZE + TILE_SIZE * 0.5f)})
#define GET_TILE_INDEXPOINT(X,Y) (POINT{(LONG)(X / TILE_SIZE),(LONG)(Y / TILE_SIZE)})

enum class PALETTE_TYPE { Terrain, Object, Max };
enum class TERRAIN_TYPE { Walkable, Rough, Slippery, Unwalkable, Max };
enum class OBJECT_TYPE { Breakable, Unbreakable, None, Max };

struct tagTileInfo
{
	TERRAIN_TYPE	eTType;
	int				nTIndex;
	OBJECT_TYPE		eOType;
	int				nOIndex;
};