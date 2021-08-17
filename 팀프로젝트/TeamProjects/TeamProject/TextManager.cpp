#include "stdafx.h"
#include "TextManager.h"


TextManager::TextManager()
{
}


TextManager::~TextManager()
{
	this->Release();
}

void TextManager::Init()
{
	g_pTextureManager->AddTexture(L"GoldNumber",  L"GoldNumber.png", L"../../_Images/UIImages/");
	g_pTextureManager->AddTexture(L"BlueNumber",  L"BlueNumber.png", L"../../_Images/UIImages/");
	g_pTextureManager->AddTexture(L"WhiteNumber", L"WhiteNumber.png", L"../../_Images/UIImages/");
	g_pTextureManager->AddTexture(L"UpperLetter", L"UpperLetter.png", L"../../_Images/UIImages/");
	g_pTextureManager->AddTexture(L"LowerLetter", L"UpperLetter.png", L"../../_Images/UIImages/");
	g_pTextureManager->AddTexture(L"BitText", L"BitFont_White.png", L"../../_Images/UIImages/");

	for (int i = 0; i < 10; i++)
	{
		m_pGoldNumber[i] = new Sprite(L"GoldNumber", 10, 1, i);
		m_pBlueNumber[i] = new Sprite(L"BlueNumber", 10, 1, i);
		m_pWhiteNumber[i] = new Sprite(L"WhiteNumber", 10, 1, i);
	}

	for (int i = 0; i < 26; i++)
	{
		m_pUpperLetter[i] = new Sprite(L"UpperLetter", 26, 1, i);
		m_pLowerLetter[i] = new Sprite(L"UpperLetter", 26, 1, i);
	}
	//BitFontSprites
	{
		int index = 0;
		for (int i = 0; i < 16; i++)
		{
			m_pWhiteText[index] = new Sprite(L"BitText", 16, 8, i);
			index++;
		}

		for (int i = 0; i < 10; i++)
		{
			m_pWhiteText[index] = new Sprite(L"BitText", 16, 8, i + 16);
			index++;
		}

		for (int i = 0; i < 7; i++)
		{
			m_pWhiteText[index] = new Sprite(L"BitText", 16, 8, i + 32);
			index++;
		}

		for (int i = 0; i < 13; i++)
		{
			m_pWhiteText[index] = new Sprite(L"BitText", 16, 8, i + 48);
			index++;
		}

		for (int i = 0; i < 13; i++)
		{
			m_pWhiteText[index] = new Sprite(L"BitText", 16, 8, i + 64);
			index++;
		}

		for (int i = 0; i < 6; i++)
		{
			m_pWhiteText[index] = new Sprite(L"BitText", 16, 8, i + 80);
			index++;
		}

		for (int i = 0; i < 14; i++)
		{
			m_pWhiteText[index] = new Sprite(L"BitText", 16, 8, i + 96);
			index++;
		}

		for (int i = 0; i < 12; i++)
		{
			m_pWhiteText[index] = new Sprite(L"BitText", 16, 8, i + 112);
			index++;
		}
		m_pWhiteText[index] = new Sprite(L"BitText", 16, 8, 86 );
	}
}

void TextManager::Release()
{
	for (int i = 0; i < 10; i++)
	{
		SAFE_DELETE(m_pGoldNumber[i]);
		SAFE_DELETE(m_pBlueNumber[i]);
		SAFE_DELETE(m_pWhiteNumber[i]);
	}

	for (int i = 0; i < 26; i++)
	{
		SAFE_DELETE(m_pUpperLetter[i]);
		SAFE_DELETE(m_pLowerLetter[i]);
	}

	for (int i = 0; i < 92; i++)
	{
		SAFE_DELETE(m_pWhiteText[i]);
	}
}

void TextManager::IntRender(int num, int x, int y, int size, NumberType type)
{
	vector<int> vecNumber;
	vecNumber.push_back(num % 10);

	while (num > 9)
	{
		num /= 10;
		vecNumber.push_back(num % 10);
	}

	int j = 0;
	for (int i = vecNumber.size() - 1; i >= 0; i--)
	{
		switch (type)
		{
		case NumberType::Gold:
			m_pGoldNumber[vecNumber[i]]->SetConstantScale(size, size);
			m_pGoldNumber[vecNumber[i]]->SetLBPosition(x + size * j * 0.7f, y);
			m_pGoldNumber[vecNumber[i]]->Update();
			m_pGoldNumber[vecNumber[i]]->Render();
			break;
		case NumberType::Blue:
			m_pBlueNumber[vecNumber[i]]->SetConstantScale(size, size);
			m_pBlueNumber[vecNumber[i]]->SetLBPosition(x + size * j * 0.7f, y);
			m_pBlueNumber[vecNumber[i]]->Update();
			m_pBlueNumber[vecNumber[i]]->Render();
			break;
		case NumberType::White:
			m_pWhiteNumber[vecNumber[i]]->SetConstantScale(size, size);
			m_pWhiteNumber[vecNumber[i]]->SetLBPosition(x + size * j , y);
			m_pWhiteNumber[vecNumber[i]]->Update();
			m_pWhiteNumber[vecNumber[i]]->Render();
			break;
		}

		j++;
	}
}

void TextManager::AlphabetRender(const char * str, int x, int y, int size)
{
	int posX = 0;

	for (int i = 0; i < strlen(str); i++)
	{
		int index = str[i] - 65;

		if (index <= 25)
		{
			m_pUpperLetter[index]->SetConstantScale(size, size);
			m_pUpperLetter[index]->SetLBPosition(x + posX, y);
			m_pUpperLetter[index]->Update();
			m_pUpperLetter[index]->Render();

			posX += size * 0.9f;
		}
		else
		{
			index -= 32;

			m_pLowerLetter[index]->SetConstantScale(size * 0.7f, size * 0.7f);
			m_pLowerLetter[index]->SetLBPosition(x + posX, y);
			m_pLowerLetter[index]->Update();
			m_pLowerLetter[index]->Render();

			posX += size * 0.6f;
		}
	}
}

void TextManager::WhiteTextRender(const char * str, int x, int y, int size)
{
	int posX = 0;

	for (int i = 0; i < strlen(str); i++)
	{
		int index = str[i] - 32;

		if (index <= 15)
		{
			m_pWhiteText[index]->SetConstantScale(size, size);
			m_pWhiteText[index]->SetLBPosition(x + posX, y);
			m_pWhiteText[index]->Update();
			m_pWhiteText[index]->Render();

			posX += size * 0.9f;
		}
		else if (index <= 25)
		{
			m_pWhiteText[index]->SetConstantScale(size, size);
			m_pWhiteText[index]->SetLBPosition(x + posX, y);
			m_pWhiteText[index]->Update();
			m_pWhiteText[index]->Render();

			posX += size * 0.9f;
		}
		else if(index <= 58)
		{

			m_pWhiteText[index]->SetConstantScale(size, size);
			m_pWhiteText[index]->SetLBPosition(x + posX, y);
			m_pWhiteText[index]->Update();
			m_pWhiteText[index]->Render();

			posX += size * 0.9f;
		}
		else if (index <= 64)
		{
			m_pWhiteText[index]->SetConstantScale(size, size);
			m_pWhiteText[index]->SetLBPosition(x + posX, y);
			m_pWhiteText[index]->Update();
			m_pWhiteText[index]->Render();

			posX += size * 0.9f;
		}
		else if (index <= 90)
		{
			m_pWhiteText[index]->SetConstantScale(size, size);
			m_pWhiteText[index]->SetLBPosition(x + posX, y);
			m_pWhiteText[index]->Update();
			m_pWhiteText[index]->Render();

			posX += size * 0.9f;
		}
		else
		{
			m_pWhiteText[91]->SetConstantScale(size, size);
			m_pWhiteText[91]->SetLBPosition(x + posX, y);
			m_pWhiteText[91]->Update();
			m_pWhiteText[91]->Render();

			posX += size * 0.9f;
		}
	}
}
