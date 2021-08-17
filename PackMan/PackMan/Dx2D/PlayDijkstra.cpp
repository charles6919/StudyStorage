#include "stdafx.h"
#include "PlayDijkstra.h"
#include "Map.h"


PlayDijkstra::PlayDijkstra(Map* map)
{
	m_pMap = map;
}


PlayDijkstra::~PlayDijkstra()
{
}

void PlayDijkstra::StartFindARoute(POINT start, POINT dest, vector<POINT>& moveVec)
{
	moveVec.clear();
	m_vecOpenNode.clear();
	m_mapUpdatedNode.clear();

	m_ptStart = start;

	// 1. 시작 노드 정보를 셋팅하고 오픈 노드로 지정
	tagNode node(start, start, 0);
	m_vecOpenNode.push_back(node);

	// 갱신 되는 모든 노드를 넣는다.
	m_mapUpdatedNode.insert(make_pair(MAP_INDEX(node.ptMapIndex), node));

	while (true) // 5. 목적지를 찾을 때까지 반복
	{
		// 2. 오픈 된 노드 중에 비용이 가장 낮은 노드 찾기
		m_stMinNode = GetMinCostNode();

		// !. 길이 없는 경우 예외 처리
		if (m_stMinNode.ptMapIndex.x == -1)
			break;

		// 3. 찾은 노드가 목적지인지 확인 : 목적지인 경우 길찾기 완료
		if (m_stMinNode.ptMapIndex.x == dest.x &&
			m_stMinNode.ptMapIndex.y == dest.y)
			break;

		// 4. 찾은 노드가 목적지가 아닌 경우 찾은 노드의 엣지 노드 갱신
		UpdateMinNode();
	}

	if (m_stMinNode.ptMapIndex.x != -1)
		MakeARoute(moveVec);
}

tagNode PlayDijkstra::GetMinCostNode()
{
	float minCost = FLT_MAX;
	int nIndex = -1;

	for (int i = 0; i < m_vecOpenNode.size(); i++)
	{
		if (m_vecOpenNode[i].fCost < minCost)
		{
			minCost = m_vecOpenNode[i].fCost;
			nIndex = i;
		}
	}

	tagNode minNode;

	if (nIndex == -1) // 길이 없는 경우
		minNode.ptMapIndex.x = -1;
	else
	{
		minNode = m_vecOpenNode[nIndex]; // 찾은 노드를 반환노드로 저장하고 클로즈로 변경
		minNode.isClosed = true;
		m_vecOpenNode.erase(m_vecOpenNode.begin() + nIndex); // 찾은 노드는 오픈 노드에서 제거
	}

	return minNode;
}

void PlayDijkstra::UpdateEdgeNode(int dirX, int dirY)
{
	POINT pt = { m_stMinNode.ptMapIndex.x + dirX, m_stMinNode.ptMapIndex.y + dirY };

	// 이동할 수 있는 블럭인지 확인
	if (m_pMap->GetTileInfo(pt.x, pt.y).eTType != TERRAIN_TYPE::Unwalkable &&
		m_pMap->GetTileInfo(pt.x, pt.y).eOType == OBJECT_TYPE::None)
	{
		map<int, tagNode>::iterator iter = m_mapUpdatedNode.find(MAP_INDEX(pt));

		// 이전에 업데이트가 된적이 있고 아직 클로즈가 되지 않은 노드
		if (iter != m_mapUpdatedNode.end() && iter->second.isClosed == false)
		{
			if (iter->second.fCost > m_stMinNode.fCost + 1) // 갱신 대상
			{
				iter->second.fCost = m_stMinNode.fCost + 1;
				iter->second.ptVia = m_stMinNode.ptMapIndex;
			}
		}
		else
		{
			// 최초 업데이트 되는 노트에 대한 값 설정
			tagNode updateNode(pt, m_stMinNode.ptMapIndex, m_stMinNode.fCost + 1);

			// 업데이트 된 노드맵과 오픈노드 벡터에 담아준다.
			m_mapUpdatedNode.insert(make_pair(MAP_INDEX(pt), updateNode));
			m_vecOpenNode.push_back(updateNode);
		}
	}
}

void PlayDijkstra::UpdateMinNode()
{
	// 4방향 이동일 경우 좌우상하 검색
	if (m_stMinNode.ptMapIndex.x > 0) // 좌측이 존재할 때
		UpdateEdgeNode(-1, 0);

	if (m_stMinNode.ptMapIndex.x < NUM_TILE_X - 1) // 우측이 존재할 때
		UpdateEdgeNode(1, 0);

	if (m_stMinNode.ptMapIndex.y < NUM_TILE_Y - 1) // 상측이 존재할 때
		UpdateEdgeNode(0, 1);

	if (m_stMinNode.ptMapIndex.y > 0) // 하측이 존재할 때
		UpdateEdgeNode(0, -1);
}

void PlayDijkstra::MakeARoute(vector<POINT>& moveVec)
{
	moveVec.push_back(m_stMinNode.ptMapIndex); // 최종 목적지

	while (true)
	{
		moveVec.push_back(m_stMinNode.ptVia);
		m_stMinNode = m_mapUpdatedNode[MAP_INDEX(m_stMinNode.ptVia)];

		if (m_stMinNode.ptVia.x == m_ptStart.x &&
			m_stMinNode.ptVia.y == m_ptStart.y)
			break;
	}
}