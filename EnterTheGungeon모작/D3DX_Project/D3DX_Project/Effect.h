#pragma once
enum class EffectType { SwordAttack1, Cloud1, Summon, DestroyBullet, Explosion, MAX};
//enum class EffectState {READY, Play_SwordAttack1, Play_Destroy_Bullet, Play_Boom1, Play_Boom2, Play_Boom3,  Play_SwordAttack2};
enum class EffectState {READY, Play};
class Effect
{
public:
	EffectType m_eType;
	EffectState m_eState;
	int m_nCurrFrame;
	Transform2D m_transform2D;
	float m_fElapsedTimer;
	float m_fDurationTime;

	float m_fAniElapsedTime;


public:
	Effect();
	~Effect();

	void Init();
};

