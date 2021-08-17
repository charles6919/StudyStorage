#pragma once

enum class Item_Type
{
	Normal_Item,
	Attack_Item,
	Fruite
};

class Item
{
private:
	
	Item_Type m_eType;
	int m_nScore;

	Sprite* m_pSprite;
	D3DXVECTOR2 m_vPosition;
	D3DXVECTOR3 m_vRotation;
	D3DXVECTOR2 m_vScale;

public:
	Item();
	~Item();

	void Init();
	void Update();
	void Render();

	void SetItemType(Item_Type type) { m_eType = type; }
	void SetScore(int score) { m_nScore = score; }
	void SetPosition(D3DXVECTOR2 v) { m_vPosition = v; }
	void SetScale(D3DXVECTOR2 v) { m_vScale = v; }
	
	Item_Type GetItemType() { return m_eType; }
	int GetScore() { return m_nScore; }
	D3DXVECTOR2 GetPosition() { return m_vPosition; }
	D3DXVECTOR2 GetScale() { return m_vScale; }

};

