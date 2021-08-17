#pragma once
#include "SingletonBase.h"
#include "Effect.h"

#define g_pEffectManager EffectManager::GetInstance()

class EffectManager : 
	public SingletonBase<EffectManager>
{
private:
	vector<Effect*> m_vecEffect;
	vector<Animation<EffectState>*> m_vecEffectAnimation;

public:
	void Init();
	void UpdateNRender();
	void Release();

	vector<Effect*>* GetVecEffect() { return &m_vecEffect; }

};

