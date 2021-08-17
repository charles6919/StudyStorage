#include "pch.h"
#include "Effect.h"

Effect::Effect()
{
}

Effect::~Effect()
{
}

void Effect::Init()
{
	m_eType = EffectType::SwordAttack1;
	m_eState = EffectState::Play;
	m_nCurrFrame = 0;
	m_fElapsedTimer = 0.0f;
	m_fDurationTime = 1.0f;
	m_fAniElapsedTime = 0.0f;
}

