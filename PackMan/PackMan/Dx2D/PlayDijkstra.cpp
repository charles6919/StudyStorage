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

	// 1. ���� ��� ������ �����ϰ� ���� ���� ����
	tagNode node(start, start, 0);
	m_vecOpenNode.push_back(node);

	// ���� �Ǵ� ��� ��带 �ִ´�.
	m_mapUpdatedNode.insert(make_pair(MAP_INDEX(node.ptMapIndex), node));

	while (true) // 5. �������� ã�� ������ �ݺ�
	{
		// 2. ���� �� ��� �߿� ����� ���� ���� ��� ã��
		m_stMinNode = GetMinCostNode();

		// !. ���� ���� ��� ���� ó��
		if (m_stMinNode.ptMapIndex.x == -1)
			break;

		// 3. ã�� ��尡 ���������� Ȯ�� : �������� ��� ��ã�� �Ϸ�
		if (m_stMinNode.ptMapIndex.x == dest.x &&
			m_stMinNode.ptMapIndex.y == dest.y)
			break;

		// 4. ã�� ��尡 �������� �ƴ� ��� ã�� ����� ���� ��� ����
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

	if (nIndex == -1) // ���� ���� ���
		minNode.ptMapIndex.x = -1;
	else
	{
		minNode = m_vecOpenNode[nIndex]; // ã�� ��带 ��ȯ���� �����ϰ� Ŭ����� ����
		minNode.isClosed = true;
		m_vecOpenNode.erase(m_vecOpenNode.begin() + nIndex); // ã�� ���� ���� ��忡�� ����
	}

	return minNode;
}

void PlayDijkstra::UpdateEdgeNode(int dirX, int dirY)
{
	POINT pt = { m_stMinNode.ptMapIndex.x + dirX, m_stMinNode.ptMapIndex.y + dirY };

	// �̵��� �� �ִ� ������ Ȯ��
	if (m_pMap->GetTileInfo(pt.x, pt.y).eTType != TERRAIN_TYPE::Unwalkable &&
		m_pMap->GetTileInfo(pt.x, pt.y).eOType == OBJECT_TYPE::None)
	{
		map<int, tagNode>::iterator iter = m_mapUpdatedNode.find(MAP_INDEX(pt));

		// ������ ������Ʈ�� ������ �ְ� ���� Ŭ��� ���� ���� ���
		if (iter != m_mapUpdatedNode.end() && iter->second.isClosed == false)
		{
			if (iter->second.fCost > m_stMinNode.fCost + 1) // ���� ���
			{
				iter->second.fCost = m_stMinNode.fCost + 1;
				iter->second.ptVia = m_stMinNode.ptMapIndex;
			}
		}
		else
		{
			// ���� ������Ʈ �Ǵ� ��Ʈ�� ���� �� ����
			tagNode updateNode(pt, m_stMinNode.ptMapIndex, m_stMinNode.fCost + 1);

			// ������Ʈ �� ���ʰ� ���³�� ���Ϳ� ����ش�.
			m_mapUpdatedNode.insert(make_pair(MAP_INDEX(pt), updateNode));
			m_vecOpenNode.push_back(updateNode);
		}
	}
}

void PlayDijkstra::UpdateMinNode()
{
	// 4���� �̵��� ��� �¿���� �˻�
	if (m_stMinNode.ptMapIndex.x > 0) // ������ ������ ��
		UpdateEdgeNode(-1, 0);

	if (m_stMinNode.ptMapIndex.x < NUM_TILE_X - 1) // ������ ������ ��
		UpdateEdgeNode(1, 0);

	if (m_stMinNode.ptMapIndex.y < NUM_TILE_Y - 1) // ������ ������ ��
		UpdateEdgeNode(0, 1);

	if (m_stMinNode.ptMapIndex.y > 0) // ������ ������ ��
		UpdateEdgeNode(0, -1);
}

void PlayDijkstra::MakeARoute(vector<POINT>& moveVec)
{
	moveVec.push_back(m_stMinNode.ptMapIndex); // ���� ������

	while (true)
	{
		moveVec.push_back(m_stMinNode.ptVia);
		m_stMinNode = m_mapUpdatedNode[MAP_INDEX(m_stMinNode.ptVia)];

		if (m_stMinNode.ptVia.x == m_ptStart.x &&
			m_stMinNode.ptVia.y == m_ptStart.y)
			break;
	}
}