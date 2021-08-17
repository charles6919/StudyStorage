#pragma once
enum class GunCode{ Hand, Sword, AK_47, Winchster, Enemy_Weapon_01, MAX};

struct stGunInfo
{
	GunCode eGunCode;			//총기 코드
	wstring sName;				//총기 이름

	int nMaxAmmo;				//최대 총알 개수
	int nAmmoByClip;			//탄창당 총알 개수
	int nCurrAmmo;				//현재 장전된 총알 개수

	float fShootSpeed;			//연사속도
	float fReloadDelay;			//장전속도
	float fBulletSpeed;			//탄환속도
	float fCaseShot;			//산탄도
	float fKnockbackPower;		//넉백 파워

	int nFire;					//1회 사격시 나가는 총알수
	int nPower;					//한개의 탄환이 가지는 데미지

	int nBulletType;

	void Init(GunCode code);
};