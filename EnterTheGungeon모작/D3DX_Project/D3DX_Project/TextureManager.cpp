#include "pch.h"
#include "TextureManager.h"


TextureManager::TextureManager()
	: m_pReadTexture(NULL)
{
}


TextureManager::~TextureManager()
{
	SAFE_RELEASE(m_pReadTexture);

	for (auto p : m_mapTexture)
		SAFE_RELEASE(p.second->pSRV);
	m_mapTexture.clear();
}

void TextureManager::AddTexture(wstring key, wstring file, wstring path)
{
	if (m_mapTexture.find(key) != m_mapTexture.end()) return;

	wstring fullPath = path + file;

	Texture* texture = new Texture;

	// ���� ���� �б� (������ �� ���)
	{
		HRESULT hr;

		D3DX11GetImageInfoFromFile(fullPath.c_str(), NULL, &texture->stInfo, &hr);
		assert(SUCCEEDED(hr) && "������ �о� �� �� �����ϴ�.");
	}

	// �̹��� �ε�
	{
		HRESULT hr;

		D3DX11CreateShaderResourceViewFromFile(Device, fullPath.c_str(), NULL, NULL, &texture->pSRV, &hr);
		assert(SUCCEEDED(hr) && "������ �о� �� �� �����ϴ�.");
	}

	m_mapTexture[key] = texture;
}

const Texture* TextureManager::GetTexture(wstring key)
{
	if (m_mapTexture.find(key) == m_mapTexture.end()) return NULL;

	return m_mapTexture[key];
}

void TextureManager::Release(wstring key)
{
	map<wstring, Texture*>::iterator iter;
	iter = m_mapTexture.find(key);

	if (iter == m_mapTexture.end()) return;

	SAFE_RELEASE(iter->second->pSRV);	// �̹��� �Ҵ� ����
	m_mapTexture.erase(iter);
}

void TextureManager::AddRenderTargetTexture(wstring key, UINT width, UINT height)
{
	if (m_mapTexture.find(key) != m_mapTexture.end()) return;

	RenderTexture* stRTexture = new RenderTexture;

	HRESULT hr;

	// ���� Ÿ�� �ؽ���  ����
	D3D11_TEXTURE2D_DESC stT2DDesc;
	stT2DDesc.Width = width;
	stT2DDesc.Height = height;
	stT2DDesc.MipLevels = 1;
	stT2DDesc.ArraySize = 1;
	stT2DDesc.Format = DXGI_FORMAT_R32G32B32A32_FLOAT;
	stT2DDesc.SampleDesc.Count = 1;
	stT2DDesc.SampleDesc.Quality = 0;
	stT2DDesc.Usage = D3D11_USAGE_DEFAULT;
	stT2DDesc.BindFlags = D3D11_BIND_RENDER_TARGET | D3D11_BIND_SHADER_RESOURCE;
	stT2DDesc.CPUAccessFlags = 0;
	stT2DDesc.MiscFlags = 0;

	hr = Device->CreateTexture2D(&stT2DDesc, NULL, &stRTexture->pT2D);
	assert(SUCCEEDED(hr));

	// ���� Ÿ�� �� ����
	D3D11_RENDER_TARGET_VIEW_DESC stRTVDesc;
	stRTVDesc.Format = stT2DDesc.Format;
	stRTVDesc.ViewDimension = D3D11_RTV_DIMENSION_TEXTURE2D;
	stRTVDesc.Texture2D.MipSlice = 0;

	hr = Device->CreateRenderTargetView(stRTexture->pT2D, &stRTVDesc, &stRTexture->pRTV);
	assert(SUCCEEDED(hr));

	// ���̴� ���ҽ� �� ����
	D3D11_SHADER_RESOURCE_VIEW_DESC stSRVDesc;
	stSRVDesc.Format = stT2DDesc.Format;
	stSRVDesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
	stSRVDesc.Texture2D.MostDetailedMip = 0;
	stSRVDesc.Texture2D.MipLevels = 1;

	hr = Device->CreateShaderResourceView(stRTexture->pT2D, &stSRVDesc, &stRTexture->pSRV);
	assert(SUCCEEDED(hr));

	stRTexture->stInfo.Width = width;
	stRTexture->stInfo.Height = height;

	m_mapTexture.insert(make_pair(key, stRTexture));
}

void TextureManager::SetRenderTargetToTexture(wstring key)
{
	if (m_mapTexture.find(key) == m_mapTexture.end()) return;

	RenderTexture* pRT = (RenderTexture*)m_mapTexture[key];
	DeviceContext->OMSetRenderTargets(1, &pRT->pRTV, NULL);
}

void TextureManager::ClearRenderTargetTexture(wstring key, D3DXCOLOR c)
{
	if (m_mapTexture.find(key) == m_mapTexture.end()) return;

	RenderTexture* pRT = (RenderTexture*)m_mapTexture[key];
	DeviceContext->ClearRenderTargetView(pRT->pRTV, c);
}

void TextureManager::SetRenderTargetToBackBuffer()
{
	DeviceContext->OMSetRenderTargets(1, &RTV, NULL);
}

void TextureManager::SetReadTexture(UINT width, UINT height)
{
	// ���� Ÿ�� �ؽ���  ����
	D3D11_TEXTURE2D_DESC stT2DDesc;
	stT2DDesc.Width = m_nWidth = width;
	stT2DDesc.Height = m_nHeight = height;
	stT2DDesc.MipLevels = 1;
	stT2DDesc.ArraySize = 1;
	stT2DDesc.Format = DXGI_FORMAT_R32G32B32A32_FLOAT;
	stT2DDesc.SampleDesc.Count = 1;
	stT2DDesc.SampleDesc.Quality = 0;
	stT2DDesc.Usage = D3D11_USAGE_STAGING;
	stT2DDesc.BindFlags = 0;
	stT2DDesc.CPUAccessFlags = D3D11_CPU_ACCESS_READ;
	stT2DDesc.MiscFlags = 0;

	SAFE_RELEASE(m_pReadTexture);
	HRESULT hr = Device->CreateTexture2D(&stT2DDesc, NULL, &m_pReadTexture);
	assert(SUCCEEDED(hr));
}

bool TextureManager::PixelCollision(wstring key, int x, int y)
{
	if (x < 0 || x > m_nWidth - 1 || y < 0 || y > m_nHeight - 1)
		return false;

	bool isCollision = true;

	// �ȼ� �浹 �� ���� �ؽ��ĸ� ����
	DeviceContext->CopyResource(m_pReadTexture, ((RenderTexture*)m_mapTexture[key])->pT2D);

	D3D11_MAPPED_SUBRESOURCE mapped;
	// Lock, Unlock (���, �ڱ�����) : Dx -> Map, Unmap
	DeviceContext->Map(m_pReadTexture, NULL, D3D11_MAP_READ, 0, &mapped);

	D3DXCOLOR* pTexels = (D3DXCOLOR*)mapped.pData;

	int index = x + (m_nHeight - 1 - y) * m_nWidth;
	// ����Ÿ ���
	//if (pTexels[index].r == 1.0f &&
	//	pTexels[index].g == 0.0f &&
	//	pTexels[index].b == 1.0f)
	//	isCollision = false;
	// ���İ� ���
	if (pTexels[index].a == 0.0f)
		isCollision = false;

	DeviceContext->Unmap(m_pReadTexture, NULL);

	return isCollision;
}
