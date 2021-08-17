#pragma once
#include "iGameNode.h"

#define PALETTE_LBPOSITION_X 50
#define PALETTE_LBPOSITION_Y 50

#define TOOL_AREA_X 360	// 도구창 영역 & 팔레트의 가로 사이즈
#define PALETTE_TILE_SIZE(U) ((TOOL_AREA_X + 100) / U) // 도구창에 그려질 타일의 크기
#define TOOL_AREA_Y(U, V) (PALETTE_TILE_SIZE(U) * V) // 팔레트의 세로 사이즈

#define UI_FONT_SIZE 48

enum class PALETTE_TYPE{ Select, Room, Door, Terrain, Walls, Ceiling, ObjectSet, NpcSet, Max};


class MapTool : public iGameNode
{

private:
	D3DXVECTOR2 m_vCameraPos;
	Sprite* m_pPaletteBackground;

	Rect*	m_pRtSelect;

	tagTileInfo m_stTiles[NUM_TILE_Y][NUM_TILE_X];

	vector<Sprite*> m_vecRoom;
	vector<Sprite*> m_vecDoor;
	vector<Sprite*> m_vecTerrain;
	vector<Sprite*> m_vecWall;
	vector<Sprite*> m_vecCeiling;
	vector<Sprite*> m_vecObject;
	vector<Sprite*> m_vecUnit;

	int m_nCurrIndex;
	int m_nCurrBrush;
	POINT m_ptRoomLT;
	POINT m_ptRoomRB;
	POINT m_ptCurrTile;
	vector<POINT> m_vecRoomPt;
	bool m_enableToRoomSetting;
	bool m_enableToDoorSetting;
	bool m_isSettingEndDoor;

	Button* m_pBtnRoom;					//방을 세팅하는 팔레트를 열어주는 버튼
	Button* m_pBtnDoor;					//문을 세팅하는 팔레트를 열어주는 버튼
	Button* m_pBtnTileSet;				//단일 타일을 세팅하는 팔레트를 열어주는 버튼
	Button* m_pBtnObjectSet;			//오브젝트를 세팅하는 팔레트를 열어주는 버튼
	Button* m_pBtnNpcSet;				//Npc를 세팅하는 팔레트를 열어주는 버튼
	Button* m_pBtnTerrain;
	Button* m_pBtnWall;
	Button* m_pBtnCeiling;

	Button* m_pBtnEraser;				//지우개 버튼
	Button* m_pBtnPageUp;				//페이지 업 버튼
	Button* m_pBtnPageDown;				//페이지 다운 버튼

	Button* m_pBtnBack;					//뒤로 돌아가는 버튼
	Button* m_pBtnSave;					//세이브를 하는 버튼
	Button* m_pBtnTitle;				//타이틀로 돌아가는 버튼


	PALETTE_TYPE m_ePaletteType;

public:
	virtual void Init();
	virtual void Update();
	virtual void Render();
	virtual void Release();

	void SaveTileInfo();


};

