#include "pch.h"

void CircleCollider::CreateCircle()
{
	pCircle = new Circle;
	pCircle->SetDraw(false);
	pCircle->SetBorder(true);
}

void CircleCollider::Update()
{
	if (pCircle)
	{
		pCircle->SetSize(transform2D.scale);
		pCircle->SetPosition(transform2D.position);
		pCircle->SetRotation(transform2D.rotation);
		pCircle->Update();
	}
}

void CircleCollider::Render()
{
	if (pCircle)
	{
		pCircle->Render();
	}
}

void CircleCollider::Release()
{
	SAFE_DELETE(pCircle);
}

void RectCollider::CreateRect()
{
	pRect = new Rect;
	pRect->SetDraw(false);
	pRect->SetBorder(true);
}

void RectCollider::Update()
{
	if (pRect)
	{
		pRect->SetSize(transform2D.scale);
		pRect->SetPosition(transform2D.position);
		pRect->SetRotation(transform2D.rotation);
		pRect->Update();
	}
}

void RectCollider::Render()
{
	if (pRect)
	{
		pRect->Render();
	}
}

void RectCollider::Release()
{
	SAFE_DELETE(pRect);
}
