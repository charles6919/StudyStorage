#pragma once
#include "Character.h"

#define STAND_SCALE D3DXVECTOR2(48, 48)
#define CROUCH_SCALE D3DXVECTOR2(24, 16)
#define GroundY (100)

enum class Player_State
{
	READY = -1,
	Idle_R,
	Idle_L,
	Run_R,
	Run_L,
	JumpUp_R,
	Fall_R,
	JumpUp_L,
	Fall_L,
	Hit_R,
	Hit_L,
	Max
};

enum class Gun_State
{
	READY = -1,
	Idle_R,
	Idle_L
};

class Player :
	public Character
{

	

private:
	Animation<Player_State>*		m_pAniCharacter;	//플레이어의 애니메이션
	Animation<Gun_State>*			m_pAniGun;			//들고있는 총의 애니메이션
	Player_State					m_ePlayerState;
	STATE							m_eState;			//캐릭터 애니메이션의 상태
	Gun_State						m_eGunState;		//총 애니메이션의 상태


	RectCollider2D*					m_pHitCollider;
	RectCollider2D*					m_pFootCollider;

	int								m_numLife;
	
	bool							m_isJumping;		
	bool							m_isShooting;
	bool							m_isSitting;
	bool							m_isRunning;
	bool							m_isHit;

	float							m_fJumpPower;		

	float							m_fGunAngle;
	bool							m_enableToShot;
	float							m_fShotTimer;
	float							m_fShotDelay;

	float							m_fInvinvibleTimer;
	float							m_fInvincibleDuration;
	bool							m_isInvincible;
	bool							m_isTwinkleOn;
	float							m_fTwinkleTimer;
	float							m_fTwinkleDuration;

public:
	Player();
	~Player();

	virtual void Init() override;
	virtual void Update() override;
	virtual void Render() override;

	void SetCharacterAni(Animation<Player_State>* ani) { m_pAniCharacter = ani; }
	void SetGunAni(Animation<Gun_State>* ani) { m_pAniGun = ani; }

	void SetHitCol(RectCollider2D* col) { m_pHitCollider = col; }
	void SetFootCol(RectCollider2D* col) { m_pFootCollider = col; }

	RectCollider2D* GetHitCollider() { return m_pHitCollider; }
	RectCollider2D* GetFootCollider() { return m_pFootCollider; }

	void SetIsHit(bool b) { m_isHit = b; }

public:
	void Jump();
	void Shot();







};

