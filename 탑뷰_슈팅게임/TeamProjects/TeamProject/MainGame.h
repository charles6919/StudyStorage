#pragma once

class MainGame
{
private:
	ID3D11BlendState*	m_pNormalBlendState;	// �⺻ ���� �ɼ�
	ID3D11BlendState*	m_pAlphaBlendState;		// ������ ���� �ɼ�
	void SetBlendStates();	// �ɼǺ� ���� ���°� ����

private:


public:
	MainGame();
	~MainGame();

	void Update();
	void Render();

};

