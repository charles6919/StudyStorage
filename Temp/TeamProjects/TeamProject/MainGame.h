#pragma once
#include "iGameNode.h"
#include "stdafx.h"



class MainGame : public iGameNode
{
private:
	ID3D11Buffer* m_pViewProjBuffer;	// ��, �������� ��Ʈ���� ����
	void SetViewProjectionMatrixes();	// ��, �������� ��Ʈ���� ���� �� ���� ����

	ID3D11BlendState*	m_pNormalBlendState;	// �⺻ ���� �ɼ�
	ID3D11BlendState*	m_pAlphaBlendState;		// ������ ���� �ɼ�
	void SetBlendStates();	// �ɼǺ� ���� ���°� ����

private:
	const int a = 10;


public:
	MainGame();
	~MainGame();

	void CreateGameClasses();
	void DeleteGameClasses();
	virtual void Init() override;
	virtual void Update() override;
	virtual void Render() override;



};

