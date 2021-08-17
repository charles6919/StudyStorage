#include "stdafx.h"
#include "Components.h"


// ====Physics2D=============================================================
Physics2D_RigidBody::Physics2D_RigidBody()
{
	m_pTransform = NULL;
	Init();
}

Physics2D_RigidBody::~Physics2D_RigidBody()
{
}

void Physics2D_RigidBody::Init()
{
	m_bUseGravity = false;
	m_bKinematic = false;
	m_isFalling = false;
	m_fDrag = 0.0f;
	m_vForce = { 0, 0 };
}

void Physics2D_RigidBody::Update()
{
	if (!m_bKinematic)
	{
		if (m_vForce.x > 0.0f)
			m_vForce.x -= m_fDrag * g_pTimeManager->GetDeltaTime();
		else
			m_vForce.x = 0.0f;

		if (m_bUseGravity)
		{
			if (m_isFalling)
			{
				m_vForce.y -= GRAVITY * g_pTimeManager->GetDeltaTime();
			}
			else
			{
				m_vForce.y = 0.0f;
			}
		}
	}
}
// ============================================================================


// Collider2D======================================================================
Collider2D::Collider2D()
{
	ZeroMemory(&transform, sizeof(transform));
	Init();
}

Collider2D::~Collider2D()
{
}

void Collider2D::Init()
{
	transform.Init();
	m_isActive	= true;
	m_isTrigger	= false;
}
// ================================================================================


// RectCollider2D======================================================================
void RectCollider2D::Init()
{
	Collider2D::Init();
}

void RectCollider2D::Update()
{
	m_pRectCollider->SetSize(transform.GetScale());
	m_pRectCollider->SetRotation(transform.GetRotation());
	m_pRectCollider->SetPosition(transform.GetPosition());
	m_pRectCollider->Update();
}

void RectCollider2D::Render()
{
	m_pRectCollider->Render();
}
// ====================================================================================

void CircleCollider2D::Init()
{
	Collider2D::Init();
}

void CircleCollider2D::Update()
{
	m_pCircleCollider->SetRadius(transform.GetScale().x * 0.5f);
	m_pCircleCollider->SetRotation(transform.GetRotation());
	m_pCircleCollider->SetPosition(transform.GetPosition());
	m_pCircleCollider->Update();
}

void CircleCollider2D::Render()
{
	m_pCircleCollider->Render();
}
