#pragma once

class MapTool;
class Dijkstra;

class PlayerTest
{
private:
	Rect*			m_pRect;
	POINT			m_ptPosition;

	MapTool*		m_pMapTool;
	vector<POINT>	m_vecMoveRoute;
	Dijkstra*		m_pDijkstra;

	float			m_fMoveSpeed;	// 한칸 이동에 걸리는 초단위 시간
	float			m_fElapsedTime;

private:
	void KeyboardControl();
	void MouseControl();

public:
	PlayerTest();
	~PlayerTest();

	void Init();
	void Update();
	void Render();

	void SetMapTool(MapTool* p) { m_pMapTool = p; }
	POINT GetPostion() { return m_ptPosition; }
};

