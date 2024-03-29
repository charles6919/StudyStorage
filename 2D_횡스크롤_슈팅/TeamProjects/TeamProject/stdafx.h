// stdafx.h : 자주 사용하지만 자주 변경되지는 않는
// 표준 시스템 포함 파일 또는 프로젝트 관련 포함 파일이
// 들어 있는 포함 파일입니다.
//

#pragma once

#include "targetver.h"

#define WIN32_LEAN_AND_MEAN             // 거의 사용되지 않는 내용은 Windows 헤더에서 제외합니다.
// Windows 헤더 파일:
#include <windows.h>

// C 런타임 헤더 파일입니다.
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>


// TODO: 프로그램에 필요한 추가 헤더는 여기에서 참조합니다.
#include <assert.h>
#include <string>
#include <vector>
#include <map>
#include <math.h>
#include <time.h>
#include <string>
 
////Component========================================================================================================================================
//#include <memory>
//#include <algorithm>
//#include <bitset>
//#include <array>
//
//class Component;
//class Entity;
//
//using namespace std;
//using ComponentID = size_t;  //std::size_t -> x86 에서는 32bit, x64 에서는 64bit
//
//inline ComponentID GetComponentTypeID()
//{
//	static ComponentID lastID = 0;
//	return lastID++;
//}
//
//template <typename T>
//inline ComponentID GetComponentTypeID() noexcept
//{
//	static ComponentID typeID = GetComponentTypeID();
//	return typeID();
//}
//
//constexpr size_t maxComponents = 32;
//
//using ComponentBitSet = std::bitset<maxComponents>;
//using ComponentArray = std::array<Component*, maxComponents>;
//
//class Component
//{
//public:
//	Entity* entity;
//
//	virtual void Init()		{ }
//	virtual void Update()	{ }
//	virtual void Render()	{ }
//
//	virtual ~Component()	{ }
//
//};
//
//class Entity
//{
//private:
//	bool active = true;
//	vector<std::unique_ptr<Component>> components;
//
//	ComponentArray componentArray;
//	ComponentBitSet componentBitSet;
//
//public:
//	void Update()
//	{
//		for (auto& c : components) c->Update();
//		for (auto& c : components) c->Render();
//	}
//	void Render() {}
//	bool IsActive() { return active; }
//	void Destroy() { active = false; }	
//
//	template <typename T> bool hasComponet() const
//	{
//		return componentBitSet[GetComponentTypeID<T>];
//	}
//
//	template <typename T, typename... TArgs>
//	T& addComponent(TArgs&& ... mArgs)
//	{
//		T* c(new T(std::forward<TArgs>(mArgs)...));
//		c->entity = this;
//		std::unique_ptr<Component> uPtr{ c };
//		components.emplace_back(std::move(uPtr));
//
//		componentArray[GetComponentTypeID<T>()] = c;
//		componentBitSet[GetComponentTypeID<T>()] = true;
//
//		c->Init();
//		return *c;
//	}
//
//	template <typename T> T& GetComponent() const
//	{
//		auto ptr(componentArray[GetComponentTypeID<T>()]);
//		return *static_cast<T*>(ptr);
//	}
//};
//
//class Manager
//{
//private:
//	std::vector<std::unique_ptr<Entity>> entities;
//
//public:
//	void Update()
//	{
//		for (auto& e : entities) e->Update();
//	}
//	void Render()
//	{
//		for (auto& e : entities) e->Render();
//	}
//	
//	void Refresh()
//	{
//		entities.erase(std::remove_if(std::begin(entities), std::end(entities),
//			[](const std::unique_ptr<Entity>& mEntity)
//		{
//			return !mEntity->IsActive();
//		}),
//			std::end(entities));
//	}
//
//	Entity& addEntity()
//	{
//		Entity* e = new Entity();
//		std::unique_ptr<Entity> uPtr{ e };
//		entities.emplace_back(std::move(uPtr));
//		return *e;
//	}
//
//	
//};
//
////==================================================================================================================================================



// 전역 변수:
extern HINSTANCE	g_hInst;                    // 현재 인스턴스입니다.
extern HWND			g_hWnd;						// 윈도우 핸들
extern POINT		g_ptMouse;
extern bool			g_isBorder;
extern float		g_fTimeControl;


// 전역 디파인
#define WINSIZEX 1280
#define WINSIZEY 720

#define OBJECT_DEFAULTX (-99999)
#define OBJECT_DEFAULTY (-99999)
#define OBJECT_DEFAULTV D3DXVECTOR2(OBJECT_DEFAULTX, OBJECT_DEFAULTY)

#define SAFE_DELETE(p)			{ if(p) { delete(p); (p) = NULL; } }
#define SAFE_DELETE_ARRAY(p)	{ if(p) { delete[] (p); (p) = NULL; } }
#define SAFE_RELEASE(p)			{ if(p) { p->Release(); (p) = NULL; } }

#define SAFE_INIT(p)			{ if(p) p->Init(); }
#define SAFE_UPDATE(p)			{ if(p) p->Update(); }
#define SAFE_RENDER(p)			{ if(p) p->Render(); }

#define GRAVITY (9.8f * 60.0f)
#define DEFAULT_X 200

#define DEFAULT_TILE_SIZE 48

enum class CharacterDir
{ RIGHT, RIGHT_TOP, TOP, LEFT_TOP, LEFT, LEFT_BOTTOM, BOTTOM, RIGHT_BOTTOM, MAX };

enum STATE
{
	READY=-1,
	IDLE,
	RUN,
	ATTACK,
	KNOCK,
	JumpUp,
	Fall,
	Hit,
	Crouch,
	DIE
};

/*
속성 -> C/C++ -> 추가 포함 디렉터리 : ../../_Libraries
속성 -> 링커 -> 추가 라이브러리 디렉터리 : ../../_Libraries
*/

// Dx 라이브러리
#include <D3D11.h>
#include <D3DX11.h>
#include <D3DX10.h>
#include <D3DX10math.h>

#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "d3dx11.lib")
#pragma comment(lib, "d3dx10.lib")

// IMGui : Immediate Mode GUI
#include <IMGui/IMGui.h>
#include <IMGui/IMGuiDx11.h>
#pragma comment(lib, "IMGui/IMGui.lib")

// 매니져 클래스
#include "KeyManager.h"
#include "TimeManager.h"
#include "TextureManager.h"
#include "SoundManager.h"
#include "FileManager.h"

// 전역 헤더파일
#include "DxComponent.h"
#include "Shader.h"
#include "Rect.h"
#include "Circle.h"
#include "Utility.h"
#include "Sprite.h"
#include "Clip.h"
#include "Animation.h"

// 매니져 클래스
#include "TextManager.h"
#include "BulletManager.h"

//함수
template<typename T>
inline void CreateSprites(Animation<T>* ani, wstring Sp_name, T state, int Sizex, int Sizey, float framerate, int indexnum)
{
	Sprite* sprite;
	Clip* clip;
	clip = new Clip();
	for (int i = 0; i < (int)framerate; i++)
	{
		int index = i + indexnum;
		sprite = new Sprite(Sp_name, Sizex, Sizey, index);
		clip->AddFrame(sprite, 1 / framerate);
	}
	ani->AddClip(state, clip);
}

template<typename T>
inline void CreateSpritesOnce(Animation<T>* ani, wstring Sp_name, T state, int Sizex, int Sizey, float framerate, int indexnum)
{
	Sprite* sprite;
	Clip* clip;
	clip = new Clip(PlayMode::Once, 1.0f);
	for (int i = 0; i < (int)framerate; i++)
	{
		int index = i + indexnum;
		sprite = new Sprite(Sp_name, Sizex, Sizey, index);
		clip->AddFrame(sprite, 1 / framerate);
	}
	ani->AddClip(state, clip);
}
