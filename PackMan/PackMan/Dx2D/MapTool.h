#pragma once
#include "iGameNode.h"
#include "TileInfo.h"
#include "PlayerTest.h"

#define TOOL_AREA_X 512	// ����â ���� & �ȷ�Ʈ�� ���� ������
#define PALETTE_TILE_SIZE(U) (TOOL_AREA_X / U) // ����â�� �׷��� Ÿ���� ũ��
#define TOOL_AREA_Y(U, V) (PALETTE_TILE_SIZE(U) * V) // �ȷ�Ʈ�� ���� ������

#define UI_FONT_SIZE 48



enum class UNIT_TYPE { Player, NPC, Monster, Max };
enum class NPC_TYPE {};
enum class MONSTER_TYPE {};



class MapTool : public iGameNode
{
private:
	vector<Sprite*>		m_vecTerrain;		// ���� �̹���
	vector<Sprite*>		m_vecObject;		// ������Ʈ �̹���
	tagTileInfo			m_stTiles[NUM_TILE_Y][NUM_TILE_X];

	PALETTE_TYPE		m_ePType;			// ���� ������� �ȷ�Ʈ
	POINT				m_ptUVSize;			// �̹��� UV ������
	tagTileInfo			m_stSelected;		// ������ Ÿ�� ����

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