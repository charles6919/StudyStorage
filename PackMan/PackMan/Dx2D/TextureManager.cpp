#include "stdafx.h"
#include "TextureManager.h"


TextureManager::TextureManager()
{
}


TextureManager::~TextureManager()
{
	for (auto p : m_mapTexture)
		SAFE_RELEASE(p.second.pSRV);
	m_mapTexture.clear();
}

void TextureManager::AddTexture(wstring key, wstring file, wstring path)
{
	if (m_mapTexture.find(key) != m_mapTexture.end()) return;

	wstring fullPath = path + file;

	Texture texture;

	// ���� ���� �б� (������ �� ���)
	{
		HRESULT hr;

		D3DX11GetImageInfoFromFile(fullPath.c_str(), NULL, &texture.stInfo, &hr);
		assert(SUCCEEDED(hr) && "������ �о� �� �� �����ϴ�.");
	}

	// �̹��� �ε�
	{
		HRESULT hr;

		D3DX11CreateShaderResourceViewFromFile(Device, fullPath.c_str(), NULL, NULL, &texture.pSRV, &hr);
		assert(SUCCEEDED(hr) && "������ �о� �� �� �����ϴ�.");
	}

	m_mapTexture[key] = texture;
}

const Texture* TextureManager::GetTexture(wstring key)
{
	if (m_mapTexture.find(key) == m_mapTexture.end()) return NULL;

	return &m_mapTexture[key];
}

void TextureManager::Release(wstring key)
{
	map<wstring, Texture>::iterator iter;
	iter = m_mapTexture.find(key);

	if (iter == m_mapTexture.end()) return;

	SAFE_RELEASE(iter->second.pSRV);	// �̹��� �Ҵ� ����
	m_mapTexture.erase(iter);
}