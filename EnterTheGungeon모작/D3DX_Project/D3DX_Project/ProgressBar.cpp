#include "pch.h"
#include "ProgressBar.h"

ProgressBar::ProgressBar(wstring backFile, wstring frontFile, int indexX)
{
	m_pBack = new Sprite(backFile);
	m_pFront = new Animation<ProgressState>;

	CreateClip(m_pFront, frontFile, ProgressState::Progress, indexX, 1, indexX, 20, 0);
	m_vPadding = { 0,0 };
	
}


ProgressBar::~ProgressBar()
{
	SAFE_DELETE(m_pBack);
	SAFE_DELETE(m_pFront);
}

void ProgressBar::Update()
{
	m_pBack->SetConstantScale(m_vSize);
	m_pBack->SetLBPosition(m_vPos);
	m_pBack->Update();

	m_pFront->Play(ProgressState::Progress);
	m_pFront->SetConstantSizeScale(m_vProgressSize.x - m_vPadding.x * 2.0f, m_vProgressSize.y - m_vPadding.y * 2.0f);
	m_pFront->SetLBPosition(m_vPos.x + m_vPadding.x, m_vPos.y + m_vPadding.y );
	m_pFront->Update();
}

void ProgressBar::Render()
{
	m_pBack->Render();
	m_pFront->Render();
}

void ProgressBar::SetProgress(float maxGauge, float currGauage, bool horizontal)
{
	if (horizontal)
		m_vProgressSize.x = m_pBack->GetWidth() * currGauage / maxGauge;
	else
		m_vProgressSize.y = m_pBack->GetHeight() * currGauage / maxGauge;
}