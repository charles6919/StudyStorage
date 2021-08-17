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
	
	int m_nCool;				//액티브 아이템 쿨
	int m_nCurrCool;			//액티브 아이템의 현재 쿨
	float m_fCoolTime;			//액티브 아이템의 쿨타임
	float m_fCurrCoolTime;		//액티브 아이템의 현재 쿨타임
	float m_fActiveDuration;	//액티브 아이템의 사용가능한 지속시간
	float m_fCurrActiveTimer;	//액티브 아이템의 현재 사용중인 시간
	bool m_isActiveOn;			//액티브 아이템의 온/오프 상태
	 
	



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

