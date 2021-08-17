#pragma once

class MapTool;

/* ���ͽ�Ʈ��(Dijstra) �˰��� (��ã�� �˰���)
��� : ���, ���� �Ǵ� ������ ���� ����
���� : �ϳ��� ��忡�� �ٸ� ���� ���� �Ǿ� �ִ� ���
������� : Ư�� ��忡�� ������ ���ؼ� �� �� �ִ� ���

��尡 ������ ����
Closed : ��忡 ���� ��� �˻� �Ϸ� ���� (Open : �˻簡 �� ����, Closed : ����)
Via : ���� ��忡 �����ϱ� ���� ���� ���
Cost : ��� ������ ���� ������ �����ϴµ� ��� '��' ���

EdgeCost : �ϳ��� ������ ������ ���� ���

0. ���۳�� ã�� (Ÿ�ϸ��� �ƴ� ��� ��� �̿��� ��ġ���� ��� �� ��)
1. ���� ��� ���� ����(�ڽ�Ʈ: 0, ���: �ڱ��ڽ� �Ǵ� NULL, Closed)
2. ���� �� ��� �߿��� ����� ���� ���� ��带 ã�´�.
3. ���� �� ��带 Ŭ����, ��Ƽ���, �ڽ�Ʈ ��� �ϰ� �ֺ� ��带 �����Ѵ�.
4. ������尡 ���� �� ������ 2, 3���� �ݺ��Ѵ�.
5. ������尡 Ŭ���� �Ǹ� ��� ���� ������ �����Ͽ� ��θ� ã�´�.
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

	map<int, tagNode>	m_mapUpdatedNode; // <��� �ε���, ��� �ε���>

private:
	// 2. ���� �� ��� �߿��� ����� ���� ���� ��带 ã�´�.
	tagNode GetMinCostNode();
	// 3. ���� �� ��带 Ŭ����, ��Ƽ���, �ڽ�Ʈ ��� �ϰ� �ֺ� ��带 �����Ѵ�.
	// 4. ������� ���� Ȯ��
	void UpdateEdgeNode(int dirX, int dirY);
	void UpdateMinNode();
	// 5. ������尡 Ŭ���� �Ǹ� ��� ���� ������ �����Ͽ� ��θ� ã�´�.
	void MakeARoute(vector<POINT>& moveVec);

public:
	Dijkstra(MapTool* map);
	~Dijkstra();

	// 1. ���� ��� ���� ����(�ڽ�Ʈ: 0, ��� : �ڱ��ڽ� �Ǵ� NULL, Closed)
	void StartFindARoute(POINT start, POINT dest, vector<POINT>& moveVec);
};