#pragma once
class Interface
{
private:
	//왼쪽 위 인터페이스
	Sprite*		m_pFullHpSprite;
	Sprite*		m_pHalfHpSprite;
	Sprite*		m_pEmptyHpSprite;
	Sprite*		m_pBlankSprite;
	Sprite*		m_pArmorSprite;
	Sprite*		m_pCoinSprite;

	bool		m_isRenderInterface;

	int			m_nPlayerHp;
	int			m_nPlayerMaxHp;
	int			m_nPlayerBlank;
	int			m_nPlayerArmor;
	int			m_nPlayerCoin;


public:
	Interface();
	~Interface();

	void Init();
	void Update();
	void Render();

	void SetPlayerValues(int hp, int maxHp, int blank, int armor, int coin);

	bool GetIsRenderInterface() { return m_isRenderInterface; }

};

