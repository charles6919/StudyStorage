#pragma once
#include "ItemCode.h"

enum class ItemType {None, Life, Ammo, Armor, Blank, PassiveItem, ActiveItem};
enum class ItemState {READY, Idle};

struct ItemInfo
{
	ItemCode	itemCode;
	wstring		name;
	ItemType	type;
};

class Item
{
private:
	Animation<ItemState>* m_pAnimation;
	Sprite* m_pSprite;
	Transform2D m_transform2D;
	ItemState m_eState;

	ItemInfo m_stItemInfo;

	CircleCollider m_stCircleCollider;
	
	int m_nCool;				//��Ƽ�� ������ ��
	int m_nCurrCool;			//��Ƽ�� �������� ���� ��
	float m_fCoolTime;			//��Ƽ�� �������� ��Ÿ��
	float m_fCurrCoolTime;		//��Ƽ�� �������� ���� ��Ÿ��
	float m_fActiveDuration;	//��Ƽ�� �������� ��밡���� ���ӽð�
	float m_fCurrActiveTimer;	//��Ƽ�� �������� ���� ������� �ð�
	bool m_isActiveOn;			//��Ƽ�� �������� ��/���� ����
	 
	



public:
	Item();
	~Item();

	void Init();
	void Update();
	void PassiveUpdate();
	void Render();

	void SetAnimation(Animation<ItemState>* p) { m_pAnimation = p; }
	void SetSprite(Sprite* p) { m_pSprite = p; }
	void SetState(ItemState state) { m_eState = state; }
	void SetItemCode(ItemCode code) { m_stItemInfo.itemCode = code; }

	ItemInfo GetItemInfo() { return m_stItemInfo; }
	Transform2D& GetItemTransform2D() { return m_transform2D; }
	Transform2D& GetColliderTransform2D() { return m_stCircleCollider.transform2D; }

	void ItmeInfo_Init(ItemCode code);




};

