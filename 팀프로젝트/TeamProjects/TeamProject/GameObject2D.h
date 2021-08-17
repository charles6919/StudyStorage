#pragma once
#include "Components.h"

class GameObject2D
{
protected:
	Transform2D*			m_pTransform2D;  //모든 오브젝트는 transform정보를 가지고 있어야 한다.
	Physics2D_RigidBody*	m_pRigidBody;	 //rigidbody는 있을수도 있고 없을수도 있다. 따라서 없을때는 NULL초기화가 되어있어야한다.

public:
	GameObject2D();
	~GameObject2D();

	virtual void Init()		;
	virtual void Update()	;
	virtual void Render()	;

public:
	void SetTransform2D(Transform2D* p) { m_pTransform2D = p; }
	Transform2D* GetTransform2D() { return m_pTransform2D; }

	void SetRigidBody2D(Physics2D_RigidBody* p) { m_pRigidBody = p; }
	Physics2D_RigidBody* GetRigidBody2D() { return m_pRigidBody; }



};

