#pragma once
#include "pch.h"

struct Transform2D
{
	D3DXVECTOR2 position	= { 0,0 };
	D3DXVECTOR2 scale		= { 0,0 };
	D3DXVECTOR3 rotation	= { 0,0,0 };
};

struct CircleCollider
{
	Transform2D transform2D;
	Circle* pCircle;

	void CreateCircle();
	void Update();
	void Render();
	void Release();
};

struct RectCollider
{
	Transform2D transform2D;
	Rect* pRect;

	void CreateRect();
	void Update();
	void Render();
	void Release();
};


