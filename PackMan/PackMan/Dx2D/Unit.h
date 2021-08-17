#pragma once

enum class CharacterDir
{
	Right, Top, Left, Bottom , Max
};

template <typename T>
class Unit
{
protected:
	POINT				m_ptPosition;
	D3DXVECTOR2			m_vScale;
	D3DXVECTOR3			m_vRotation;
	CharacterDir		m_eCharacterDir;

	Animation<T>*		m_pAnimation;
	T					m_eState;

	float				m_fMoveSpeed;

	bool				m_isAlive;

public:
	Unit();
	~Unit();

	virtual void Init();
	virtual void Update();
	virtual void Render();

	void SetPosition(float x, float y) { m_ptPosition.x = x; m_ptPosition.y = y; }
	void SetPosition(POINT pt) { SetPosition(pt.x, pt.y); }
	void SetScale(float x, float y) { m_vScale = {x,y}; }
	void SetScale(D3DXVECTOR2 v) { SetScale(v.x, v.y); }

	POINT* GetPosition() { return &m_ptPosition; }
	D3DXVECTOR2 GetScale() { return m_vScale; }
	bool IsAlive() { return m_isAlive; }
	float GetMoveSpeed() { return m_fMoveSpeed; }
};

template<typename T>
inline Unit<T>::Unit()
{
	m_pAnimation = new Animation<T>;
}

template<typename T>
inline Unit<T>::~Unit()
{
	SAFE_DELETE(m_pAnimation);
}

template<typename T>
inline void Unit<T>::Init()
{
	m_eState = T::Move;
	m_ptPosition = { 0,0 };
	m_vScale = { 100,100 };
	m_vRotation = D3DXVECTOR3(0, 0, 0);
	m_pAnimation->Play(m_eState);
	m_pAnimation->SetConstantSizeScale(m_vScale);
	m_eCharacterDir = CharacterDir::Right;
	
	m_fMoveSpeed = 300.0f;	// 초당 이동 속도

	m_isAlive = true;
}

template<typename T>
inline void Unit<T>::Update()
{
	m_pAnimation->SetConstantSizeScale(m_vScale);
	m_pAnimation->SetPosition(m_ptPosition.x, m_ptPosition.y);
	m_pAnimation->SetRotation(m_vRotation.x, m_vRotation.y, m_vRotation.z);
	m_pAnimation->Play(m_eState);
	m_pAnimation->Update();
}

template<typename T>
inline void Unit<T>::Render()
{
	if (m_pAnimation)
		m_pAnimation->Render();
}
