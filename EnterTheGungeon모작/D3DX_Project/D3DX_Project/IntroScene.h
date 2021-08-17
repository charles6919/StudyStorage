#pragma once
#include "iGameNode.h"

enum IntroState {READY, INTRO1, INTRO2};

class IntroScene : public iGameNode
{
private:
	Animation<IntroState>* m_pAnimation;


public:
	virtual void Init();
	virtual void Update();
	virtual void Render();
	virtual void Release();
};

