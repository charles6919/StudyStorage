#include "pch.h"

void stGunInfo::Init(GunCode code)
{
    eGunCode = code;
	switch (eGunCode)
	{
    case GunCode::Hand:
        sName               = L"Hand";
        nMaxAmmo            = 0;
        nAmmoByClip         = 0;
        nCurrAmmo           = 0;
        fShootSpeed         = 0;
        fReloadDelay        = 0;
        fBulletSpeed        = 0;
        fCaseShot           = 0;
        fKnockbackPower     = 0;
        nBulletType         = 0;
        nFire               = 0;
        nPower              = 0;
        break;
    case GunCode::Sword:
        sName               = L"Sword";
        nMaxAmmo            = INFINITE;
        nAmmoByClip         = INFINITE;
        nCurrAmmo           = nAmmoByClip;
        fShootSpeed         = 12;
        fReloadDelay        = 1.0f;
        fBulletSpeed        = 26.0f;
        nBulletType         = 0;
        nFire               = 1;
        nPower              = 14;
        break;
    case GunCode::AK_47:
        sName               = L"AK-47";
        nMaxAmmo            = 500;
        nAmmoByClip         = 30;
        nCurrAmmo           = nAmmoByClip;
        fShootSpeed         = 6.6f;
        fReloadDelay        = 0.6f;
        fBulletSpeed        = 23.0f;
        nBulletType         = 0;
        nFire               = 1;
        nPower              = 5.5;
        break;
    case GunCode::Winchster:
        sName               = L"Winchester";
        nMaxAmmo            = 100;
        nAmmoByClip         = 8;
        nCurrAmmo           = nAmmoByClip;
        fShootSpeed         = 3.6f;
        fReloadDelay        = 1.7f;
        fBulletSpeed        = 23.0f;
        nBulletType         = 0;
        nFire               = 6;
        nPower              = 4;
        break;
    case GunCode::Enemy_Weapon_01:
        sName               = L"Enemy_Weapon01";
        nMaxAmmo            = INFINITE;
        nAmmoByClip         = INFINITE;
        nCurrAmmo           = nAmmoByClip;
        fShootSpeed         = 1.0f;
        fReloadDelay        = 1.7f;
        fBulletSpeed        = 20.0f;
        nBulletType         = 0;
        nFire               = 1;
        nPower              = 1;
        break;

	}
}
