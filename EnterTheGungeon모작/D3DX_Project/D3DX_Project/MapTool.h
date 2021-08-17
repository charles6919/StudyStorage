#pragma once
#include "iGameNode.h"

#define PALETTE_LBPOSITION_X 50
#define PALETTE_LBPOSITION_Y 50

#define TOOL_AREA_X 360	// ����â ���� & �ȷ�Ʈ�� ���� ������
#define PALETTE_TILE_SIZE(U) ((TOOL_AREA_X + 100) / U) // ����â�� �׷��� Ÿ���� ũ��
#define TOOL_AREA_Y(U, V) (PALETTE_TILE_SIZE(U) * V) // �ȷ�Ʈ�� ���� ������

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

	Button* m_pBtnRoom;					//���� �����ϴ� �ȷ�Ʈ�� �����ִ� ��ư
	Button* m_pBtnDoor;					//���� �����ϴ� �ȷ�Ʈ�� �����ִ� ��ư
	Button* m_pBtnTileSet;				//���� Ÿ���� �����ϴ� �ȷ�Ʈ�� �����ִ� ��ư
	Button* m_pBtnObjectSet;			//������Ʈ�� �����ϴ� �ȷ�Ʈ�� �����ִ� ��ư
	Button* m_pBtnNpcSet;				//Npc�� �����ϴ� �ȷ�Ʈ�� �����ִ� ��ư
	Button* m_pBtnTerrain;
	Button* m_pBtnWall;
	Button* m_pBtnCeiling;

	Button* m_pBtnEraser;				//���찳 ��ư
	Button* m_pBtnPageUp;				//������ �� ��ư
	Button* m_pBtnPageDown;				//������ �ٿ� ��ư

	Button* m_pBtnBack;					//�ڷ� ���ư��� ��ư
	Button* m_pBtnSave;					//���̺긦 �ϴ� ��ư
	Button* m_pBtnTitle;				//Ÿ��Ʋ�� ���ư��� ��ư


	PALETTE_TYPE m_ePaletteType;

public:
	virtual void Init();
	virtual void Update();
	virtual void Render();
	virtual void Release();

	void SaveTileInfo();


};

