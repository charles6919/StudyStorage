#pragma once
#include "Components.h"

class GameObject2D
{
protected:
	Transform2D*			m_pTransform2D;  //��� ������Ʈ�� transform������ ������ �־�� �Ѵ�.
	Physics2D_RigidBody*	m_pRigidBody;	 //rigidbody�� �������� �ְ� �������� �ִ�. ���� �������� NULL�ʱ�ȭ�� �Ǿ��־���Ѵ�.

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

