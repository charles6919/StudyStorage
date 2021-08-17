#include "pch.h"
#include "BulletManager.h"



void BulletManager::Init()
{
	if (!m_circleCollider.pCircle)
		m_circleCollider.CreateCircle();

	if (!m_pAnimation)
	{
		m_pAnimation = new Animation<BulletAniState>;
		CreateClip(m_pAnimation, L"Bullets", BulletAniState::Default_Idle, 4, 4, 1, 1, 0 * 4);
		CreateClip(m_pAnimation, L"Bullets", BulletAniState::Default_Destroy, 4, 4, 4, 8, 1 * 4);
		CreateClip(m_pAnimation, L"Bullets", BulletAniState::Sword_Idle, 4, 4, 3, 8, 2 * 4);
		CreateClip(m_pAnimation, L"Bullets", BulletAniState::Sword_Destroy, 4, 4, 4, 8, 3 * 4);
	}


}

void BulletManager::Update()
{
	for (int i = m_vecBullet.size() - 1; i >= 0; i--)
	{
		m_vecBullet[i]->Update();
		D3DXVECTOR2 pos = m_vecBullet[i]->m_stInfo.colTransform.position;
		if (pos.x < 0.0f ||
			pos.x > TILE_SIZE* (NUM_TILE_X + 1) ||
			pos.y < 0.0f ||
			pos.y > TILE_SIZE * (NUM_TILE_Y + 1))
		{
			Effect* effect = new Effect;
			effect->Init();
			effect->m_fDurationTime = 0.33f;
			effect->m_eType = EffectType::DestroyBullet;
			D3DXVECTOR2 v = m_vecBullet[i]->m_stInfo.transform.position;
			effect->m_transform2D.position.x = v.x;
			effect->m_transform2D.position.y = v.y;
			effect->m_transform2D.scale = { 50, 50 };
			g_pEffectManager->GetVecEffect()->push_back(effect);

			m_vecBullet.erase(m_vecBullet.begin() + i);
		}
	}
}

void BulletManager::UpdateRender()
{
	for (int i = m_vecBullet.size() - 1; i >= 0; i--)
	{
		m_pAnimation->Play(m_vecBullet[i]->m_eAniState);
		m_pAnimation->SetConstantSizeScale(m_vecBullet[i]->m_stInfo.transform.scale);
		m_pAnimation->SetRotation(m_vecBullet[i]->m_stInfo.transform.rotation);
		m_pAnimation->SetPosition(m_vecBullet[i]->m_stInfo.transform.position);
		m_vecBullet[i]->UpdateAniState();
		m_pAnimation->SetCurrFrame(m_vecBullet[i]->m_eAniState, m_vecBullet[i]->m_stInfo.currFrame);
		m_pAnimation->SetElapsedTime(m_vecBullet[i]->m_stInfo.ElapsedTime);
		m_pAnimation->Update();
		m_pAnimation->Render();
		m_vecBullet[i]->m_stInfo.currFrame = m_pAnimation->GetCurrFrame();
		m_vecBullet[i]->m_stInfo.ElapsedTime = m_pAnimation->GetElapsedTime();

		m_vecBullet[i]->m_stInfo.colTransform.position = m_vecBullet[i]->m_stInfo.transform.position;
		m_circleCollider.transform2D = m_vecBullet[i]->m_stInfo.colTransform;
		m_circleCollider.Update();
		m_circleCollider.Render();
	}
}

void BulletManager::Render()
{
	UpdateRender();
}

void BulletManager::Release()
{
	for (int i = 0; i < m_vecBullet.size(); i++)
	{
		SAFE_DELETE(m_vecBullet[i]);
	}
	m_vecBullet.clear();

	m_circleCollider.Release();
	SAFE_DELETE(m_pAnimation);
}


