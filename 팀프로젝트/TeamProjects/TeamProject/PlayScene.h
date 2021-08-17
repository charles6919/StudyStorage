#pragma once
#include "iGameNode.h"

class PlayScene : public iGameNode
{

public:
	virtual void Init()		override;
	virtual void Update()	override;
	virtual void Render()	override;
	virtual void Release()	override;
};

