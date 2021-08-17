#pragma once
#include "Character.h"
#include "ProgressBar.h"

#define SHOTDOWNDELAY	(0.5f )
#define SHOTRANDOMDELAY (0.25f)
#define SHOTTARGETDELAY (0.3f )
#define BOSS_BULLETSIZE (30.0f)

#define BULLETSPOTNUM 3
#define LAZERSPOTNUM 2
#define FLOATUP (WINSIZEY-100)
#define FLOATDOWN (FLOATUP-75)
#define FLOATDURATION (3.0f)

enum class Boss_State
{
	READY = -1,
	Flying,
	Die,
	Max
};

enum class AttackPattern
{
	Start,
	ShotBullet,
	Lazer_R,
	Lazer_L
};

enum class ShotPattern
{
	ShotDown,
	ShotRandom,
	ShotTarget,
	Max
};

class Boss :
	public Character
{
private:
	Animation<Boss_State>*		m_pAniCharacter;
	Boss_State					m_eBossState;
	AttackPattern				m_eAttackPattern;
	ShotPattern					m_eShotPattern;
	RectCollider2D*				m_pHitCollider;

	ProgressBar*				m_pHpBar;
	D3DXVECTOR2					m_vBulletSpot[3];
	D3DXVECTOR2					m_vLaserSpot[2];

	D3DXVECTOR2					m_vVia;
	D3DXVECTOR2					m_vTarget;
	Player*						m_pPlayer;

	D3DXCOLOR					m_vColor;

	float						m_fShotTimer;
	float						m_fShotDelay;

	float						m_fFlyPatternTimer;
	float						m_fFlyPatternDuration;

	float						m_fShotPatternTimer;
	float						m_fShotPatternDuration;

	bool						m_isFlyUp;
	float						m_fFloatSpeed;
	float						m_fFloatTimer;

	bool						m_isTwinkleOn;
	bool						m_isColorOff;
	float						m_fTwinkleChangeTimer;
	float						m_fTwinkleChangeDuration;
	float						m_fTwinkleTimer;
	float						m_fTwinkleDuration;

	bool m_isHit;
	bool m_isGameClear;



public:
	Boss();
	~Boss();

	virtual void Init()		override;
	virtual void Update()	override;
	virtual void Render()	override;

	void SetAnimation(Animation<Boss_State>* ani) { m_pAniCharacter = ani; }
	void SetHitCollider(RectCollider2D* col) { m_pHitCollider = col; }
	void SetPlayer(Player* p) { m_pPlayer = p; }
	void SetHpBar(ProgressBar* p) { m_pHpBar = p; }
	void SetIsHit(bool b) { m_isHit = b; }

	RectCollider2D* GetHitCollider() { return m_pHitCollider; }

	void Shot();
	void Float();

	void SettingAttackPattern(AttackPattern pattern);
	void SettingShotPattern(ShotPattern pattern);

	void SetIsGameClear(bool b) { m_isGameClear = b; }
	bool GetIsGameClear() { return m_isGameClear; }

	void Targeting(D3DXVECTOR2 pos);

};

