#include "stdafx.h"
#include "GameObject2D.h"

GameObject2D::GameObject2D()
{
	m_pTransform2D = new Transform2D;
	m_pRigidBody = NULL;
}

GameObject2D::~GameObject2D()
{
	SAFE_DELETE(m_pTransform2D);
	SAFE_DELETE(m_pRigidBody);
}
void GameObject2D::Init()
{
	m_pTransform2D->Init();
	if (m_pRigidBody)
	{
		m_pRigidBody->Init();
		m_pRigidBody->SetTransform2D(m_pTransform2D);
	}
}

void GameObject2D::Update()
{
	if (m_pRigidBody)
		m_pRigidBody->Update();
}

void GameObject2D::Render()
{

}
