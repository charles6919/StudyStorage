#pragma once

template <typename T>
class Animation
{
private:
	D3DXVECTOR2		m_vPosition;
	float			m_fAniSpeed;
	T				m_eCurrState;

	// ¸Ê<Å°°ª, µ¥ÀÌÅÍ°ª>
	map<T, Clip*>	m_mapClip;

public:
	Animation<T>();
	~Animation<T>();

	void AddClip(T state, Clip* clip);
	void Play(T state);
	void PlayReverse(T state);
	void SetStartFrame(T state, int start);

	D3DXMATRIX& GetWMatrix() { return m_mapClip[m_eCurrState]->GetWMatrix(); }

	void SetPosition(float x, float y) { m_vPosition.x = x; m_vPosition.y = y; }
	void SetPosition(D3DXVECTOR2 p) { m_vPosition.x = p.x; m_vPosition.y = p.y; }
	D3DXVECTOR2 GetPosition() { return m_vPosition; }

	void SetLBPosition(float x, float y);
	void SetLBPosition(D3DXVECTOR2 v);

	void SetRotation(float x, float y, float z);
	void SetRotation(D3DXVECTOR3 r);

	void SetScale(float x, float y);
	void SetScale(D3DXVECTOR2 v) { SetScale(v.x, v.y); }
	void SetConstantSizeScale(float x, float y);
	void SetConstantSizeScale(D3DXVECTOR2 v) { SetConstantSizeScale(v.x, v.y); }

	void SetAniSpeed(float s) { m_fAniSpeed = s; }
	void SetBorder(bool b) { m_mapClip[m_eCurrState]->SetBorder(b); }

	void Update();
	void Render();

	float GetWidth() { return m_mapClip[m_eCurrState]->GetWidth(); }
	float GetHeight() { return m_mapClip[m_eCurrState]->GetHeight(); }

	Clip* GetClip(T t) { return m_mapClip[t]; }//Ãß°¡µÊ
	int	  GetCurrFrameIndex(){ return m_mapClip[m_eCurrState]->GetCurrFrameIndex(); }
	void  SetColor(D3DXCOLOR color) { m_mapClip[m_eCurrState]->SetColor(color); }
	void  SetColorAllClip(D3DXCOLOR color)
	{
		for (auto p : m_mapClip)
		{
			p.second->SetColor(color);
		}
	}


};

template <typename T>
inline Animation<T>::Animation()
	: m_vPosition(0, 0)
	, m_fAniSpeed(1.0f)
	, m_eCurrState(T::READY)
{
}

template <typename T>
inline Animation<T>::~Animation()
{
	for (auto p : m_mapClip)
		SAFE_DELETE(p.second);
	m_mapClip.clear();
}

template <typename T>
inline void Animation<T>::AddClip(T state, Clip * clip)
{
	m_mapClip.insert(make_pair(state, clip));
}

template <typename T>
inline void Animation<T>::Play(T state)
{
	if (m_eCurrState == state) return;

	m_eCurrState = state;

	m_mapClip[m_eCurrState]->Play();
}

template <typename T>
inline void Animation<T>::PlayReverse(T state)
{
	m_mapClip[state]->PlayReverse();
}

template <typename T>
inline void Animation<T>::SetStartFrame(T state, int start)
{
	m_mapClip[state]->SetStartFrame(start);
}

template<typename T>
inline void Animation<T>::SetLBPosition(float x, float y)
{
	this->SetPosition(x + GetWidth() * 0.5f, y + GetHeight() * 0.5f);
}

template<typename T>
inline void Animation<T>::SetLBPosition(D3DXVECTOR2 v)
{
	this->SetLBPosition(v.x, v.y);
}

template<typename T>
inline void Animation<T>::SetRotation(float x, float y, float z)
{
	for (auto p : m_mapClip)
		p.second->SetRotation(x, y, z);
}

template<typename T>
inline void Animation<T>::SetRotation(D3DXVECTOR3 r)
{
	this->SetRotation(r.x, r.y, r.z);
}

template <typename T>
inline void Animation<T>::SetScale(float x, float y)
{
	for (auto p : m_mapClip)
		p.second->SetScale(x, y);
}

template <typename T>
inline void Animation<T>::SetConstantSizeScale(float x, float y)
{
	for (auto p : m_mapClip)
		p.second->SetConstantScale(x, y);
}

template <typename T>
inline void Animation<T>::Update()
{
	if (m_mapClip.find(m_eCurrState) == m_mapClip.end()) return;

	m_mapClip[m_eCurrState]->SetSpeed(m_fAniSpeed);
	m_mapClip[m_eCurrState]->SetPosition(m_vPosition);
	m_mapClip[m_eCurrState]->Update();
}

template <typename T>
inline void Animation<T>::Render()
{
	if (m_mapClip.find(m_eCurrState) == m_mapClip.end()) return;

	m_mapClip[m_eCurrState]->Render();
}

