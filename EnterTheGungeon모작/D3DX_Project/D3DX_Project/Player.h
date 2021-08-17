#pragma once
#include "Unit.h"
#include "Gun.h"
#include "Item.h"

#define EVADE_SPEED 350
#define GUN_DISTANCE 16

enum class Player_State{ READY, Idle, Run, Evade, Die};
enum class Player_AniState{	READY, 
							Idle_R, Idle_T, Idle_L, Idle_B,
							Run_RT, Run_RB,Run_LT, Run_LB, Run_T, Run_B,
							Evade_RT, Evade_T, Evade_LT, Evade_LB, Evade_B, Evade_RB,
							Die_R, Die_L,
							Max};

class Player :
	public Unit<Player_AniState>
{
private:
	Player_State					m_ePState;
	CircleCollider					m_HitCollider;
	CircleCollider					m_AttackCollider;
	bool m_isAttack;
	int m_nAttack;


	float							m_fElapsedEvadeTimer;
	float							m_fEvadeDuration;
	float							m_fEvadeSpeed;

	float m_fElapsedCloudTimer;
	float m_fCloudCoolTime;

	int								m_nMaxHp;			//�ִ�ü��
	int								m_nArmor;			//�Ƹ�
	int								m_nBlank;			//����ź

	vector<Item*>					m_vecPassiveItem; 
	vector<Item*>					m_vecActiveItem;
	int								m_nSlotActiveItem;	//��Ƽ�� ������ ���� ����
	int								m_nCurrIndexSlot;	//���� ��Ƽ�꽽���� ��ȣ
	vector<Gun*>					m_vecGun;			//�� ����
	int								m_nGunIndex;
	Transform2D						m_transform2DGun;	//���� Ʈ������

	bool							m_enableToHit;
	float							m_fHitTimer;
	float							m_fElapsedHitTimer;

	float							m_fElapsedShotTimer;
	float							m_fElapsedReloadTimer;

	bool m_enableToControl;
	bool m_isHit;
	bool m_isControlPause;
	bool m_enableToMove;
	bool m_isEvading;
	bool m_isShooting;
	bool m_isReloading;


	D3DXVECTOR2						m_vMoveDir;
	tagTileInfo						m_stTileInfo[NUM_TILE_Y][NUM_TILE_X];

private:
	void AngleUpdate();
	void ItemUpdate(int code);
	void GunUpdate(GunCode code);
	void KeyboardUpdate();
	void AttackColliderUpdate();
	void MouseUpdate();
	void StateUpdate();

public:
	Player();
	~Player();

	virtual void Init();
	virtual void Update();
	virtual void Render();

	void Move();										//�̵�
	void Rotate();										//ȸ��
	void Evade();										//ȸ��
	void UseBlank();									//����ź ���
	void UseActiveItem();								//��Ƽ�� ������ ���
	void Dead();										//����
	void Shot();										//���
	void Reload();										//������
	void Hit();											//�ǰ�
	void Falling();										//����
	void KnockBack(float power, D3DXVECTOR2 dir);		//�˹�

	void SetTileInfo(tagTileInfo tileInfo[NUM_TILE_Y][NUM_TILE_X]);
	void SetRectCollider(CircleCollider CircleCollider);
	void SetPositionHitCollider(D3DXVECTOR2 pos) { m_HitCollider.transform2D.position = pos; }
	void SetRotationHitCollider(D3DXVECTOR3 rot) { m_HitCollider.transform2D.rotation = rot; }
	void SetScaleHitCollider(D3DXVECTOR2 scale) { m_HitCollider.transform2D.scale = scale; }
	void SetPositionGun(D3DXVECTOR2 pos) { m_transform2DGun.position = pos; }
	void SetRotationGun(D3DXVECTOR3 rot) { m_transform2DGun.rotation = rot;}
	void SetScaleGun(D3DXVECTOR2 scale) { m_transform2DGun.scale = scale; }

	D3DXVECTOR2* GetPosition() { return &m_transform2D.position; }
	CircleCollider GetHitCollider() { return m_HitCollider; }
	CircleCollider GetAttackCollider() { return m_AttackCollider; }
	bool GetEnableToHit() { return m_enableToHit; }
	bool GetIsAttack() { return m_isAttack; }
	int GetMaxHp() { return m_nMaxHp; }
	int GetNumBlank() { return m_nBlank; }
	int GetNumArmor() { return m_nArmor; }
};

