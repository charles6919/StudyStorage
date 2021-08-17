#pragma once
#include "iGameNode.h"
#include "stdafx.h"
#include "Player.h"
#include "Boss.h"

#define GAMEOVER_COUNTMAX (10.0f)

class MainGame : public iGameNode
{
private:
	ID3D11Buffer* m_pViewProjBuffer;	// ��, �������� ��Ʈ���� ����
	void SetViewProjectionMatrixes();	// ��, �������� ��Ʈ���� ���� �� ���� ����

	ID3D11BlendState*	m_pNormalBlendState;	// �⺻ ���� �ɼ�
	ID3D11BlendState*	m_pAlphaBlendState;		// ������ ���� �ɼ�
	void SetBlendStates();	// �ɼǺ� ���� ���°� ����

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

