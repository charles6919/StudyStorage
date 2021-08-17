#pragma once
#include "Components.h"

class GameObject2D
{
protected:
	Transform2D*			m_pTransform2D;  //모든 오브젝트는 transform정보를 가지고 있어야 한다.
	Physics2D_RigidBody*	m_pRigidBody;	 //rigidbody는 있을수도 있고 없을수도 있다. 따라서 없을때는 NULL초기화가 되어있어야한다.

	bool					m_isPrefab;		//프리팹오브젝트인지 아닌지의 bool
											//true면 프리팹으로 여겨 최초 생성후 update, render등을 하지 않는다.
											//그리고 오브젝트의 정보를 담은 구조체로부터 정보를 가져와 해당 정보로 업데이트후 랜더해준다.(오브젝트를 생성을 한번만 하기위함.)

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

	void SetIsPrefab(bool b) { m_isPrefab = b; }
	bool GetIsPrefab() { return m_isPrefab; }


};

