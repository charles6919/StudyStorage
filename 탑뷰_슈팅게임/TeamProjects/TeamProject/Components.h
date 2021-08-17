#pragma once
class Transform2D
{
private:
	D3DXVECTOR2 position;
	D3DXVECTOR2 scale;
	D3DXVECTOR3	rotation;

public:

	Transform2D()	{ this->Init(); };
	~Transform2D()	{				};

	void Init() 
	{
		position	= {0, 0};
		scale		= {0, 0};
		rotation	= {0, 0, 0};
	};


	void SetPosition(D3DXVECTOR2 pos)						{ position = pos; }
	void SetPosition(float x, float y)						{ position = { x, y }; }
	void SetScale(D3DXVECTOR2 s)							{ scale = s; }
	void SetScale(float sizeX, float sizeY)					{ scale = { sizeX, sizeY }; }
	void SetRotation(D3DXVECTOR3 rot)						{ rotation = rot; }
	void SetRotation(float rotX, float rotY, float rotZ)	{ rotation = { rotX, rotY, rotZ }; }

	D3DXVECTOR2&	GetPosition()	{ return position;	}
	D3DXVECTOR2&	GetScale()		{ return scale;		}
	D3DXVECTOR3&	GetRotation()	{ return rotation;	}

	void Translate2D(float moveX, float moveY) { position.x += moveX;  position.y += moveY; }

};

class Physics2D_RigidBody
{
private:
	Transform2D* m_pTransform;	//rigidBody는 고유 Transform을 가지고 있지 않아 받아와야한다.

	bool		m_bUseGravity;	//중력의 영향을 받는지 bool
	bool		m_bKinematic;	//중력, 마찰같은 물리 엔진의 영향을 받게 할건지에 대한 bool ->true면 물리엔진 off
	bool		m_isFalling;	//낙하중인지 bool변수
	float		m_fDrag;		//마찰력
	D3DXVECTOR2 m_vForce;		//Transform에가하는 힘
	D3DXVECTOR2 m_vForceDir;	//Force의 방향

public:

	Physics2D_RigidBody();
	~Physics2D_RigidBody();

	void Init();
	void Update();

	void SetTransform2D(Transform2D* p) { m_pTransform = p; }
	void SetUseGravity(bool b) { m_bUseGravity = b; }
	void SetIsKinematic(bool b) { m_bKinematic = b; }
	void SetIsFalling(bool b) { m_isFalling = b; }
	void SetDrag(float f) { m_fDrag = f; }
	void SetForce(D3DXVECTOR2 v) { m_vForce = v; }
	void SetForceDirX(float dirX) { m_vForceDir.x = dirX; }
	void SetForceDirY(float dirY) { m_vForceDir.y = dirY; }
	void SetForceDir(D3DXVECTOR2 dir) { m_vForceDir = dir; }

	bool		GetUseGravity()	{ return m_bUseGravity; }
	bool		GetIsKinematic(){ return m_bKinematic; }
	bool		GetIsFalling()	{ return m_isFalling; }
	float		GetDrag()		{ return m_fDrag;  }
	D3DXVECTOR2	GetForce()		{ return m_vForce; }
	D3DXVECTOR2 GetForceDir()	{ return m_vForceDir; }
};

class Collider2D
{
protected:
	Transform2D transform;
	bool		m_isActive;		//콜리더 활성 여부 bool
	bool		m_isTrigger;	//트리거 콜리더 여부 ->true면 물리적인 콜리더가 아닌 트리거 콜리더가 된다.

public:
	Collider2D();
	~Collider2D();

	void Init();

	void SetTransform2D(Transform2D t) { transform = t; }
	void SetIsActive(bool b) { m_isActive = b; }
	void SetIsTrigger(bool b) { m_isTrigger = b; }

	Transform2D& GetTransform2D() { return transform; }
	bool GetIsActive() { return m_isActive; }
	bool GetIsTrigger() { return m_isTrigger; }

};

class RectCollider2D
	:public Collider2D
{
private:
	Rect* m_pRectCollider;

public:
	void Init();
	void Update();
	void Render();

	void SetRectCollider2D(Rect* rt) { m_pRectCollider = rt; }
	Rect* GetRectCollider2D() { return m_pRectCollider; }
};

class CircleCollider2D
	:public Collider2D
{
private:
	Circle* m_pCircleCollider;

public:
	void Init();
	void Update();
	void Render();

	void SetCircleCollider2D(Circle* c) { m_pCircleCollider = c; }
	Circle* GetCircleCollider2D() { return m_pCircleCollider; }
};