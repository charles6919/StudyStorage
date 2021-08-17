#pragma once
enum class Character_Dir{R,RT,T,LT,L,LB,B,RB, MAX};

template <typename T>
class Unit
{
protected:
	Transform2D			m_transform2D;

	float				m_fAngle; //바라보는 각도.
	Character_Dir		m_eCharacterDir;

	Animation<T>*		m_pCAnimation;
	T					m_eCState;

	float				m_fMoveSpeed;
	int					m_nHp;
	bool				m_isAlive;
	bool				m_isFalling;
	bool				m_isFlying;
	
public:
	Unit();
	~Unit();

	virtual void Init();
	virtual void Update();
	virtual void Render();

	void SetPosition(float x, float y) { m_transform2D.position = { x,y }; }
	void SetPosition(D3DXVECTOR2 v) { SetPosition(v.x, v.y); }
	void SetScale(float x, float y) { m_transform2D.scale = { x,y }; }
	void SetScale(D3DXVECTOR2 v) { SetScale(v.x, v.y); }
	void SetRotation(float x, float y, float z) { m_transform2D.rotation = {x,y,z}; }
	void SetRotation(D3DXVECTOR3 v) { SetRotation(v.x, v.y, v.z); }
	void SetIsFalling(bool b) { m_isFalling = b; }
	void SetIsFlying(bool b) { m_isFlying = b; }
	void SetIsAlive(bool b) { m_isAlive = b; }

	int GetCurrHp() { return m_nHp; }
	bool GetIsAlive() { return m_isAlive; }
};



template<typename T>
inline Unit<T>::Unit()
	:
	m_pCAnimation(NULL)
{
}

template<typename T>
inline Unit<T>::~Unit()
{
	SAFE_DELETE(m_pCAnimation);
}

template<typename T>
inline void Unit<T>::Init()
{
	m_eCState = T::READY;
	m_fAngle = 0.0f;
	m_fMoveSpeed = 200.0f;
	m_nHp = 10;
	m_isAlive = true;
	m_transform2D;
}


template<typename T>
inline void Unit<T>::Update()
{

	if (m_pCAnimation)
	{
		m_pCAnimation->SetPosition(m_transform2D.position);
		m_pCAnimation->SetConstantSizeScale(m_transform2D.scale);
		m_pCAnimation->SetRotation(m_transform2D.rotation);
		m_pCAnimation->Play(m_eCState);
		m_pCAnimation->Update();
	}
}

template<typename T>
inline void Unit<T>::Render()
{
	if (m_pCAnimation)
		m_pCAnimation->Render();
}
