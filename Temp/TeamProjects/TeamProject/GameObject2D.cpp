#include "stdafx.h"
#include "GameObject2D.h"

GameObject2D::GameObject2D()
{
	m_pTransform2D = NULL;
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
	m_pRigidBody->Init();
	m_pRigidBody->SetTransform2D(m_pTransform2D);
	m_isPrefab = false;
}

void GameObject2D::Update()
{
	SAFE_UPDATE(m_pRigidBody);
}

void GameObject2D::Render()
{

}
