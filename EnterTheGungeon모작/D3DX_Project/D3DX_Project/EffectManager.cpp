#include "pch.h"
#include "EffectManager.h"

void EffectManager::Init()
{
	for (int i = 0; i < (int)EffectType::MAX; i++)
	{
		Animation<EffectState>* ani = new Animation<EffectState>;
	
		switch ((EffectType)i)
		{
		case EffectType::SwordAttack1:
			CreateClipOnce(ani, L"SwordAttack1", EffectState::Play, 3, 1, 3, 10, 0);
			m_vecEffectAnimation.push_back(ani);
			break;
		case EffectType::Cloud1:
			CreateClipOnce(ani, L"Cloud1", EffectState::Play, 7, 1, 7, 7, 0);
			m_vecEffectAnimation.push_back(ani);
			break;
		case EffectType::Summon:
			CreateClipOnce(ani, L"Summon_Effect", EffectState::Play, 18, 1, 18, 18, 0);
			m_vecEffectAnimation.push_back(ani);
			break;
		case EffectType::DestroyBullet:
			CreateClipOnce(ani, L"Bullet_Destroy1", EffectState::Play, 6, 1, 6, 18, 0);
			m_vecEffectAnimation.push_back(ani);
			break;
		case EffectType::Explosion:
			CreateClipOnce(ani, L"Explsion_Effect", EffectState::Play, 8, 1, 8, 20, 0);
			m_vecEffectAnimation.push_back(ani);
			break;
		}
	}

}

void EffectManager::UpdateNRender()
{
	for (int i = m_vecEffect.size() - 1; i >= 0; i--)
	{
		int index = (int)m_vecEffect[i]->m_eType;
		m_vecEffectAnimation[index]->Play(m_vecEffect[i]->m_eState);
		if (m_vecEffect[i]->m_nCurrFrame == m_vecEffectAnimation[index]->GetmaxFrame())
		{
			SAFE_DELETE(m_vecEffect[i]);
			m_vecEffect.erase(m_vecEffect.begin() + i);
			continue;
		}
		m_vecEffectAnimation[index]->SetPosition(m_vecEffect[i]->m_transform2D.position);
		m_vecEffectAnimation[index]->SetConstantSizeScale(m_vecEffect[i]->m_transform2D.scale);
		m_vecEffectAnimation[index]->SetRotation(m_vecEffect[i]->m_transform2D.rotation);
		m_vecEffectAnimation[index]->SetCurrFrame(m_vecEffect[i]->m_eState ,m_vecEffect[i]->m_nCurrFrame);
		
		m_vecEffectAnimation[index]->SetElapsedTime(m_vecEffect[i]->m_fAniElapsedTime);
		m_vecEffectAnimation[index]->Update();
		m_vecEffectAnimation[index]->Render();
		m_vecEffect[i]->m_nCurrFrame = m_vecEffectAnimation[index]->GetCurrFrame();
		m_vecEffect[i]->m_fAniElapsedTime = m_vecEffectAnimation[index]->GetElapsedTime();
	}
}

void EffectManager::Release()
{

}
