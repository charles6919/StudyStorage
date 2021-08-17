#pragma once
#include "Components.h"

enum class Particle_Type
{
	PlayerShooting,
	RocketExplosion,
	Bleeding
};

class Particle
{
private:
	Transform2D		m_Transform;
	Particle_Type	m_eType;
	int				m_nCurrFrameIndex;
	


public:


};

