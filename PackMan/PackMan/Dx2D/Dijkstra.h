#pragma once

class MapTool;

/* 다익스트라(Dijstra) 알고리즘 (길찾기 알고리즘)
노드 : 출발, 도착 또는 경유지 설정 지역
엣지 : 하나의 노드에서 다른 노드로 연결 되어 있는 경로
엣지노드 : 특정 노드에서 엣지를 통해서 갈 수 있는 노드

노드가 가지는 정보
Closed : 노드에 대한 비용 검사 완료 유무 (Open : 검사가 덜 끝남, Closed : 끝남)
Via : 현재 노드에 도달하기 위한 이전 노드
Cost : 출발 노드부터 현재 노드까지 도달하는데 드는 '총' 비용

EdgeCost : 하나의 엣지를 지나기 위한 비용

0. 시작노드 찾기 (타일맵이 아닌 경우 노드 이외의 위치에서 출발 할 때)
1. 시작 노드 정보 갱신(코스트: 0, 비아: 자기자신 또는 NULL, Closed)
2. 오픈 된 노드 중에서 비용이 가장 작은 노드를 찾는다.
3. 선택 된 노드를 클로즈, 비아설정, 코스트 계산 하고 주변 노드를 갱신한다.
4. 도착노드가 선택 될 때까지 2, 3번을 반복한다.
5. 도착노드가 클로즈 되면 비아 노드로 역으로 추적하여 경로를 찾는다.
*/

struct tagNode
{
	POINT	ptMapIndex;
	bool	isClosed;
	POINT	ptVia;
	float	fCost;

	tagNode() {	}
	tagNode(POINT pos, POINT via, float cost)
	{
		ptMapIndex = pos;
		ptVia = via;
		fCost = cost;
		isClosed = false;
	}
};

class Dijkstra
{
#define MAP_INDEX(pt) (pt.x + pt.y * NUM_TILE_X)

private:
	MapTool*			m_pMapTool;
	POINT				m_ptStart;
	tagNode				m_stMinNode;
	vector<tagNode>		m_vecOpenNode;

	map<int, tagNode>	m_mapUpdatedNode; // <노드 인덱스, 비아 인덱스>

private:
	// 2. 오픈 된 노드 중에서 비용이 가장 작은 노드를 찾는다.
	tagNode GetMinCostNode();
	// 3. 선택 된 노드를 클로즈, 비아설정, 코스트 계산 하고 주변 노드를 갱신한다.
	// 4. 도착노드 여부 확인
	void UpdateEdgeNode(int dirX, int dirY);
	void UpdateMinNode();
	// 5. 도착노드가 클로즈 되면 비아 노드로 역으로 추적하여 경로를 찾는다.
	void MakeARoute(vector<POINT>& moveVec);

public:
	Dijkstra(MapTool* map);
	~Dijkstra();

	// 1. 시작 노드 정보 갱신(코스트: 0, 비아 : 자기자신 또는 NULL, Closed)
	void StartFindARoute(POINT start, POINT dest, vector<POINT>& moveVec);
};