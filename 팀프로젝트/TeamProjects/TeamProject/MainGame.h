#pragma once
#include "iGameNode.h"
#include "stdafx.h"



class MainGame : public iGameNode
{
private:
	ID3D11BlendState*	m_pNormalBlendState;	// �⺻ ���� �ɼ�
	ID3D11BlendState*	m_pAlphaBlendState;		// ������ ���� �ɼ�
	void SetBlendStates();	// �ɼǺ� ���� ���°� ����

private:


public:
	MainGame();
	~MainGame();

	virtual void Update() override;
	virtual void Render() override;



};

