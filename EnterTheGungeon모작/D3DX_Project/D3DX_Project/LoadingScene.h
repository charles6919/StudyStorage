#pragma once
#include "iGameNode.h"

class LoadingScene : public iGameNode
{
	enum LoadState{READY, Loading};

private:
	Animation<LoadState>* m_pAnimation;

public:
	LoadingScene() {};
	~LoadingScene() {};

	virtual void Init() override;
	virtual void Update() override;
	virtual void Render() override;
	virtual void Release() override;
};

