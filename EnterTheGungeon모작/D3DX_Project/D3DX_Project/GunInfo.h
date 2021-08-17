#pragma once
enum class GunCode{ Hand, Sword, AK_47, Winchster, Enemy_Weapon_01, MAX};

struct stGunInfo
{
	GunCode eGunCode;			//�ѱ� �ڵ�
	wstring sName;				//�ѱ� �̸�

	int nMaxAmmo;				//�ִ� �Ѿ� ����
	int nAmmoByClip;			//źâ�� �Ѿ� ����
	int nCurrAmmo;				//���� ������ �Ѿ� ����

	float fShootSpeed;			//����ӵ�
	float fReloadDelay;			//�����ӵ�
	float fBulletSpeed;			//źȯ�ӵ�
	float fCaseShot;			//��ź��
	float fKnockbackPower;		//�˹� �Ŀ�

	int nFire;					//1ȸ ��ݽ� ������ �Ѿ˼�
	int nPower;					//�Ѱ��� źȯ�� ������ ������

	int nBulletType;

	void Init(GunCode code);
};