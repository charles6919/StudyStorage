#pragma once
enum class ProgressState { READY, Progress};
class ProgressBar
{
private:
	D3DXVECTOR2		m_vPos;
	D3DXVECTOR2		m_vSize;
	D3DXVECTOR2		m_vProgressSize;

	D3DXVECTOR2 m_vPadding;


	Sprite* m_pBack;
	Animation<ProgressState>* m_pFront;

public:
	ProgressBar(wstring backFile, wstring frontFile, int indexX = 1);
	~ProgressBar();

	void Update();
	void Render();

	void SetPos(float x, float y) { m_vPos = D3DXVECTOR2(x, y); }
	void SetSize(float x, float y) { m_vProgressSize = m_vSize = D3DXVECTOR2(x, y); }
	void SetProgress(float maxGauge, float currGauage, bool horizontal);
	void SetPaddingXY(float x, float y) { m_vPadding = D3DXVECTOR2(x,y); }
};

