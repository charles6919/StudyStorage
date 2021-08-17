#pragma once
#include "iGameNode.h"
#include "Components.h"

enum class TileType{ Normal, Floating, Obstacle, Max};


class Tile
	:public iGameNode
{
private:
	Transform2D*				m_pTransform;
	Physics2D_RigidBody*		m_pRigidBody;
	RectCollider2D*				m_pRtCollider;

	Sprite*						m_pSprite;
	TileType					m_eTileType;

public:
	Tile();
	~Tile();

	virtual void Init()	  override;
	virtual void Update() override;
	virtual void Render() override;

	void SetSprite(Sprite* sprite) { m_pSprite = sprite; }



};

