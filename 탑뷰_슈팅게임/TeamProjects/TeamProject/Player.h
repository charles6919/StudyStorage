#pragma once
#include "GameObject2D.h"

#define PLAYER_MAXHP (100)
#define HITCOLLIDER_R (40)
#define AGGROCOLLIDER_R (300)
#define GUNSOUND_R		(1500)
#define STEPSOUND_R		(500)

enum class PlayerState
{
	READY = -1,
	HIdle,
	HRun,
	HShot,
	HReload,
	RIdle,
	RRun,
	RShot,
	RReload
};

enum class GunType
{
	Pistol,
	Rifle
};

enum class Player_DefaultState
{
	Idle,
	Run,
	Shot,
	Reload,
};

struct stGun
{
	GunType _type;			//총의 종류
	int _numCurrAmmo;		//현재 탄창의 장전된 총알 개수
	int _numMagazineAmmo;	//한탄창의 최대 장전되는 총알 개수 
	int _numAmmo;			//보유한 총알 개수
};

class Player :
	public GameObject2D
{
private:
	//pointers
	Animation<PlayerState>* m_pAnimation;
	CircleCollider2D*		m_pHitCollider;
	CircleCollider2D*		m_pAggroCollider;
	ProgressBar*			m_pHpBar;

	//State
	Player_DefaultState		m_eState;
	PlayerState				m_eAniState;

	//Gun
	stGun*					m_pCurrGun;		//현재 사용중인 총
	stGun					m_stPistol;		//권총
	stGun					m_stRifle;		//라이플

	//Status
	int						m_nHp;

	float					m_fMoveSpeed;
	float					m_fRotSpeed;
	float					m_fShotTimer;
	float					m_fShotDelay;
	float					m_fReloadTimer;
	float					m_fReloadDelay;
	float					m_fSoundRadius;


	//Physics Values
	D3DXVECTOR2				m_vShotPos;
	D3DXVECTOR2				m_vShotDir;
	D3DXVECTOR2				m_vMoveDir;

	//Bools
	bool					m_enableShot;
	bool					m_isShoting;
	bool					m_isMovingX;
	bool					m_isMovingY;
	bool					m_isMoveing;
	bool					m_isReloading;
	bool					m_isDead;
	bool					m_isHit;


public:
	Player();
	~Player();

	void Init();
	void Update();
	void Render();

	void Rotate();
	void Move();
	void Shot(D3DXVECTOR2 dest);
	void TakeDamage(int dmg) { m_nHp -= dmg; }

	void SetAnimation(Animation<PlayerState>* ani) { m_pAnimation = ani; }
	void SetHitCollider(CircleCollider2D* col) { m_pHitCollider = col; }
	void SetAggroCollider(CircleCollider2D* col) { m_pAggroCollider = col; }
	void SetHpBar(ProgressBar* hpBar) { m_pHpBar = hpBar; }
	void AddAmmo(int n) { m_pCurrGun->_numAmmo += n; }
	void AddHp(int n)
	{
		m_nHp += n;
		if (m_nHp > 100)
			m_nHp = 100;
	}
	void IncreaseMoveSpeed(float f) { m_fMoveSpeed += f; }
	void IncreaseRotSpeed(float f) { m_fRotSpeed += f; }

	CircleCollider2D* GetHitCollider() { return m_pHitCollider; }
	CircleCollider2D* GetAggroCollider() { return m_pAggroCollider; }

};

