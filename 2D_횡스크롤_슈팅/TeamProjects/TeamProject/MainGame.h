#pragma once
#include "iGameNode.h"
#include "stdafx.h"
#include "Player.h"
#include "Boss.h"

#define GAMEOVER_COUNTMAX (10.0f)

class MainGame : public iGameNode
{
private:
	ID3D11Buffer* m_pViewProjBuffer;	// 뷰, 프로젝션 매트릭스 버퍼
	void SetViewProjectionMatrixes();	// 뷰, 프로젝션 매트릭스 셋팅 및 버퍼 생성

	ID3D11BlendState*	m_pNormalBlendState;	// 기본 블렌드 옵션
	ID3D11BlendState*	m_pAlphaBlendState;		// 반투명 블렌드 옵션
	void SetBlendStates();	// 옵션별 블렌드 상태값 생성

private:
	Player* m_pPlayer;
	Boss* m_pBoss;
	Sprite* m_pGameOver;
	Sprite* m_pGameClear;

	float		m_fCount;
	D3DXCOLOR	m_vColorT;


public:
	MainGame();
	~MainGame();

	void CreateGameClasses();
	void DeleteGameClasses();
	virtual void Init() override;
	virtual void Update() override;
	virtual void Render() override;



};

