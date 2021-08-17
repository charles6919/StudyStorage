#pragma once
#include "GunInfo.h"

enum class Gun_State { READY, Idle, Reload, Shot, Idle_L, Reload_L, Shot_L };


class Gun
{
private:
	Animation<Gun_State>* m_pGAnimation;
	Gun_State m_eState;
	stGunInfo m_stGunInfo;

public:
	Gun();
	~Gun();

	void Init(GunCode code);
	void Update(Transform2D transform);
	void Render();

	void SetGunAnimation(Animation<Gun_State>* p) { m_pGAnimation = p; }
	void SetState(Gun_State state) { m_eState = state; }
	
	stGunInfo& GetGunInfo() { return m_stGunInfo; }
};

