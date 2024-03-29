#pragma once
#include "SingletonBase.h"

#define g_pTextManager TextManager::GetInstance()

enum class NumberType
{
	Gold,
	Blue,
	White
};

class TextManager :	public SingletonBase<TextManager>
{
private:
	Sprite*			m_pGoldNumber[10];
	Sprite*			m_pBlueNumber[10];
	Sprite*			m_pWhiteNumber[10];
	Sprite*			m_pUpperLetter[26];
	Sprite*			m_pLowerLetter[26];
	Sprite*			m_pWhiteText[92];

public:
	TextManager();
	~TextManager();

	void Init();
	void Release();

	void IntRender(int num, int x, int y, int size, NumberType type);
	void AlphabetRender(const char* str, int x, int y, int size);
	void WhiteTextRender(const char* str, int x, int y, int size);
};

