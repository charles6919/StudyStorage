#pragma once
#include "iGameNode.h"
#include "TileInfo.h"
#include "PlayerTest.h"

#define TOOL_AREA_X 512	// 도구창 영역 & 팔레트의 가로 사이즈
#define PALETTE_TILE_SIZE(U) (TOOL_AREA_X / U) // 도구창에 그려질 타일의 크기
#define TOOL_AREA_Y(U, V) (PALETTE_TILE_SIZE(U) * V) // 팔레트의 세로 사이즈

#define UI_FONT_SIZE 48



enum class UNIT_TYPE { Player, NPC, Monster, Max };
enum class NPC_TYPE {};
enum class MONSTER_TYPE {};



class MapTool : public iGameNode
{
private:
	vector<Sprite*>		m_vecTerrain;		// 지형 이미지
	vector<Sprite*>		m_vecObject;		// 오브젝트 이미지
	tagTileInfo			m_stTiles[NUM_TILE_Y][NUM_TILE_X];

	PALETTE_TYPE		m_ePType;			// 현재 사용중인 팔레트
	POINT				m_ptUVSize;			// 이미지 UV 사이즈
	tagTileInfo			m_stSelected;		// 선택한 타일 정보

	Rect*				m_pRect;
	Sprite*				m_pSelectUI;

private:
	void ImguiSetting();

private:
	PlayerTest*			m_pPlayer;

	void TestInit();
	void TestUpdate();
	void TestRender();
	void TestRelease();

public:
	MapTool() {};
	~MapTool() {};

	virtual void Init() override;
	virtual void Update() override;
	virtual void Render() override;
	virtual void Release() override;

	tagTileInfo& GetTileInfo(int x, int y) { return m_stTiles[y][x]; }
};