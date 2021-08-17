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
	m_vForceDir = { 0, 0 };
}

void Physics2D_RigidBody::Update()
{
	if (!m_bKinematic)
	{
		m_pTransform->Translate2D(m_vForce.x * g_pTimeManager->GetDeltaTime() , m_vForce.y * g_pTimeManager->GetDeltaTime());

		if (m_vForce.x > 0.0f)
			m_vForce.x -= m_vForceDir.x * m_fDrag * g_pTimeManager->GetDeltaTime();
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
		else
		{
			if (m_vForce.y > 0.0f)
				m_vForce.y -= m_vForceDir.y * m_fDrag * g_pTimeManager->GetDeltaTime();
			else
				m_vForce.y = 0.0f;
		}
	}
}
// ============================================================================


// Collider2D======================================================================
Collider2D::Collider2D()
{
	//ZeroMemory(&transform, sizeof(transform));
	transform.Init();
	Init();
}

Collider2D::~Collider2D()
{
}

void Collider2D::Init()
{
	m_isActive	= true;
	m_isTrigger	= false;
}
// ================================================================================


// RectCollider2D======================================================================
void RectCollider2D::Init()
{
	Collider2D::Init();
	m_pRectCollider = new Rect;
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
	m_pCircleCollider = new Circle;
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
