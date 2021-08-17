#pragma once
#define DEFAULT_SIZE 32
enum class BulletState {Idle, Destroy};
enum class BulletType { Player, Enemy };
enum class BulletShape { Default, Sword };
enum class BulletAniState {	READY, Default_Idle, Default_Destroy,
							Sword_Idle, Sword_Destroy};

struct BulletInfo
{
	Transform2D		transform;
	Transform2D     colTransform;
	BulletState state;
	BulletShape shape;
	BulletType type;
	float moveSpeed;
	D3DXVECTOR2 moveDir;
	int currFrame;
	int damage;
	float ElapsedTime;
};

class Bullet
{
public:
	BulletInfo					m_stInfo;
	BulletAniState				m_eAniState;

public:
	Bullet();
	~Bullet();

	void Init();
	void Update();

	void Move();
	void UpdateAniState();
};

