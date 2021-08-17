#include "stdafx.h"
#include "MainGame.h"
MainGame::MainGame()
{
	srand(time(NULL));

	SetViewProjectionMatrixes();
	SetBlendStates();

	CreateGameClasses();
	this->Init();
}

void MainGame::SetViewProjectionMatrixes()
{
	ViewProjectionDesc VPDesc;

	// �� ��Ʈ���� ����
	D3DXVECTOR3 eye(0, 0, -1);
	D3DXVECTOR3 lookAt(0, 0, 0);
	D3DXVECTOR3 up(0, 1, 0);
	D3DXMatrixLookAtLH(&VPDesc.View, &eye, &lookAt, &up);
	D3DXMatrixTranspose(&VPDesc.View, &VPDesc.View);
	// ���̴����� ��Ʈ������ ��� ���� ������ �ٲ��ֱ� ������ Ʈ������� ���־�� �Ѵ�.

	// �������� ��Ʈ���� ����
	D3DXMatrixOrthoOffCenterLH(&VPDesc.Projection, 0, (float)WINSIZEX, 0, (float)WINSIZEY, -1, 1);
	D3DXMatrixTranspose(&VPDesc.Projection, &VPDesc.Projection);

	// ���� ����
	D3D11_BUFFER_DESC desc = { 0, };
	desc.Usage = D3D11_USAGE_DEFAULT;
	desc.ByteWidth = sizeof(ViewProjectionDesc);
	desc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;

	// ���ۿ� ���� ������
	D3D11_SUBRESOURCE_DATA data = { 0, };
	data.pSysMem = &VPDesc;

	HRESULT hr = Device->CreateBuffer(&desc, &data, &m_pViewProjBuffer);
}

void MainGame::SetBlendStates()
{
	D3D11_BLEND_DESC desc = { 0, };

	desc.RenderTarget[0].BlendEnable = false;
	desc.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;
	Device->CreateBlendState(&desc, &m_pNormalBlendState);

	desc.RenderTarget[0].BlendEnable = true;
	desc.RenderTarget[0].DestBlend = D3D11_BLEND_INV_SRC_ALPHA;
	desc.RenderTarget[0].SrcBlend = D3D11_BLEND_SRC_ALPHA;
	desc.RenderTarget[0].BlendOp = D3D11_BLEND_OP_ADD;
	desc.RenderTarget[0].DestBlendAlpha = D3D11_BLEND_ZERO;
	desc.RenderTarget[0].SrcBlendAlpha = D3D11_BLEND_ZERO;
	desc.RenderTarget[0].BlendOpAlpha = D3D11_BLEND_OP_ADD;
	Device->CreateBlendState(&desc, &m_pAlphaBlendState);
}

MainGame::~MainGame()
{
	DeleteGameClasses();

	SAFE_RELEASE(m_pNormalBlendState);
	SAFE_RELEASE(m_pAlphaBlendState);

	SAFE_RELEASE(m_pViewProjBuffer);


}

void MainGame::CreateGameClasses()
{

}

void MainGame::DeleteGameClasses()
{

}

void MainGame::Init()
{

}

void MainGame::Update()
{
	if (g_pKeyManager->isOnceKeyDown(VK_F2)) // ���� �ʱ�ȭ
		this->Init();


}

void MainGame::Render()
{
	D3DXCOLOR Map = D3DXCOLOR(0, 0, 0, 1);
	DeviceContext->ClearRenderTargetView(RTV, (float*)Map);
	DeviceContext->VSSetConstantBuffers(0, 1, &m_pViewProjBuffer);

	DeviceContext->OMSetBlendState(m_pAlphaBlendState, NULL, 0xFF);

	DeviceContext->OMSetBlendState(m_pNormalBlendState, NULL, 0xFF);

	ImGui::Render();

	SwapChain->Present(0, 0);
}

