#pragma once
#include "Unit.h"
#include "PlayDijkstra.h"

enum class ENEMY_STATE
{
	READY = -1,
	Move,
	Move_R, Move_T, Move_L, Move_B,
	Scared,
	Jailed_R, Jailed_T, Jailed_L, Jailed_B,
	MAX
};

enum class Pattern
{
	Move,
	Scared,
	Jailed
};

class Map;
class Player;


class Enemy : public Unit<ENEMY_STATE>
{
private:
	Pattern m_ePattern;
	POINT m_ptDest;
	POINT m_ptNext;
	POINT m_ptCurr;
	bool m_isTrackingPlayer;
	bool m_enableChangeDest;
	Map* m_pMap;
	Player* m_pPlayer;
	PlayDijkstra* m_pDijkstra;
	vector<POINT> m_vecRoute;
	D3DXVECTOR2 m_vMoveDir;

	Circle* m_pHitCollider;
	float m_fHitRange;

	float m_fChangeDestDelay;
	float m_fElapsedTime;
	bool  m_isJailed;


private:
	void SetMoveDir();

public:
	Enemy();
	~Enemy();

	void Init() override;
	void Update() override;
	void Render() override;

	void StageInit();

	void SetMap(Map* p) { m_pMap = p; }
	void SetPlayer(Player* p) { m_pPlayer = p; }
	void SetDijkstra(PlayDijkstra* p) { m_pDijkstra = p; }
	void SetIsTracking(bool b) { m_isTrackingPlayer = b; }

	void Move();
	void SetNextPt();
	void SetRoute(POINT pt);
	void SetIsJailed(bool b) { m_isJailed = b;}
	bool GetIsJailed() { return m_isJailed; }

	Circle* GetHitCollider() { return m_pHitCollider; }
};

