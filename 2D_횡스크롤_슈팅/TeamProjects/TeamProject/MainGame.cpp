#include "stdafx.h"
#include "MainGame.h"

MainGame::MainGame()
{
	srand(time(NULL));

	SetViewProjectionMatrixes();
	SetBlendStates();

	m_pPlayer		= NULL;
	m_pBoss			= NULL;
	m_pGameOver		= NULL;
	m_pGameClear	= NULL;

	{
		g_pTextureManager->AddTexture(L"progressBarBack", L"progressBarBack.png");
		g_pTextureManager->AddTexture(L"progressBarFront", L"progressBarFront.png");
		g_pTextureManager->AddTexture(L"GameOver", L"GameOver.png");
	}

	CreateGameClasses();
	this->Init();
}

void MainGame::SetViewProjectionMatrixes()
{
	ViewProjectionDesc VPDesc;

	// 뷰 매트릭스 셋팅
	D3DXVECTOR3 eye(0, 0, -1);
	D3DXVECTOR3 lookAt(0, 0, 0);
	D3DXVECTOR3 up(0, 1, 0);
	D3DXMatrixLookAtLH(&VPDesc.View, &eye, &lookAt, &up);
	D3DXMatrixTranspose(&VPDesc.View, &VPDesc.View);
	// 셰이더에서 매트릭스의 행과 열의 방향이 바껴있기 때문에 트랜스포즈를 해주어야 한다.

	// 프로젝션 매트릭스 셋팅
	D3DXMatrixOrthoOffCenterLH(&VPDesc.Projection, 0, (float)WINSIZEX, 0, (float)WINSIZEY, -1, 1);
	D3DXMatrixTranspose(&VPDesc.Projection, &VPDesc.Projection);

	// 버퍼 생성
	D3D11_BUFFER_DESC desc = { 0, };
	desc.Usage = D3D11_USAGE_DEFAULT;
	desc.ByteWidth = sizeof(ViewProjectionDesc);
	desc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;

	// 버퍼에 담을 데이터
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
	m_pPlayer = new Player;
	
	{
		Transform2D* transform = new Transform2D;
		Physics2D_RigidBody* rb = new Physics2D_RigidBody;

		transform->Init();
		rb->SetTransform2D(transform);
		rb->Init();

		m_pPlayer->SetTransform2D(transform);
		m_pPlayer->SetRigidBody2D(rb);
	}

	//Player Animation
	{
		Animation<Player_State>* ani = new Animation<Player_State>;
		Animation<Gun_State>* gAni = new Animation<Gun_State>;

		//Idle
		CreateSprites<Player_State>(ani, L"Player", Player_State::Idle_R, 8, 10, 5, 8 * 0);
		CreateSprites<Player_State>(ani, L"Player", Player_State::Idle_L, 8, 10, 5, 8 * 1);

		//Run
		CreateSprites<Player_State>(ani, L"Player", Player_State::Run_R, 8, 10, 8, 8 * 2);
		CreateSprites<Player_State>(ani, L"Player", Player_State::Run_L, 8, 10, 8, 8 * 3);

		//JumpUp
		CreateSpritesOnce<Player_State>(ani, L"Player", Player_State::JumpUp_R, 8, 10, 2, 8 * 4);
		CreateSpritesOnce<Player_State>(ani, L"Player", Player_State::JumpUp_L, 8, 10, 2, 8 * 6);

		//Fall
		CreateSpritesOnce<Player_State>(ani, L"Player", Player_State::Fall_R, 8, 10, 2, 8 * 5);
		CreateSpritesOnce<Player_State>(ani, L"Player", Player_State::Fall_L, 8, 10, 2, 8 * 7);

		//Hit
		CreateSpritesOnce<Player_State>(ani, L"Player", Player_State::Hit_R, 8, 10, 3, 8 * 8);
		CreateSpritesOnce<Player_State>(ani, L"Player", Player_State::Hit_L, 8, 10, 3, 8 * 9);

		//HandGun_Idle
		CreateSprites<Gun_State>(gAni, L"Player_Gun_R", Gun_State::Idle_R, 1, 1, 1, 0);
		CreateSprites<Gun_State>(gAni, L"Player_Gun_L", Gun_State::Idle_L, 1, 1, 1, 0);

		m_pPlayer->SetCharacterAni(ani);
		m_pPlayer->SetGunAni(gAni);
	}

	//Player Colliders
	{
		RectCollider2D* col = new RectCollider2D;
		Rect* rt = new Rect;

		rt->SetSize(70,150);
		rt->SetDraw(false);
		rt->SetBorder(true);
		col->SetRectCollider2D(rt);
		m_pPlayer->SetHitCol(col);

		col = new RectCollider2D;
		rt = new Rect;

		rt->SetSize(70, 30);
		rt->SetDraw(false);
		rt->SetBorder(true);
		col->SetRectCollider2D(rt);
		m_pPlayer->SetFootCol(col);
	}

	m_pBoss = new Boss;

	{
		Transform2D* transform = new Transform2D;

		transform->Init();

		m_pBoss->SetTransform2D(transform);
	}

	//Boss Colliders
	{
		RectCollider2D* col = new RectCollider2D;
		Rect* rt = new Rect;

		rt->SetSize(70, 150);
		rt->SetDraw(false);
		rt->SetBorder(true);
		col->SetRectCollider2D(rt);
		m_pBoss->SetHitCollider(col);
	}

	{
		ProgressBar* bar = new ProgressBar(L"progressBarBack", L"progressBarFront");
		m_pBoss->SetHpBar(bar);
	}
	//Boss Animation
	{
		Animation<Boss_State>* ani = new Animation<Boss_State>;

		//Idle
		CreateSprites<Boss_State>(ani, L"Boss", Boss_State::Flying, 4, 1, 4, 0);

		//Die
		CreateSprites<Boss_State>(ani, L"Boss_Die", Boss_State::Die, 1, 1, 1, 0);

		m_pBoss->SetAnimation(ani);
	}

	
	m_pGameOver = new Sprite(L"GameOver");
	m_pGameClear = new Sprite(L"GameOver");
	
	m_pGameClear->SetPosition(WINSIZEX, WINSIZEY);
	m_pGameClear->SetConstantScale(WINSIZEX, WINSIZEY);

	g_pBulletManager->SetPlayer(m_pPlayer);
	g_pBulletManager->SetBoss(m_pBoss);
	m_pBoss->SetPlayer(m_pPlayer);

}

void MainGame::DeleteGameClasses()
{
	SAFE_DELETE(m_pPlayer);
}

void MainGame::Init()
{
	g_pBulletManager->Init();
	m_pBoss->Init();
	m_pPlayer->Init();
	m_fCount = GAMEOVER_COUNTMAX;
	m_vColorT = {1, 1, 1, 0};
}

void MainGame::Update()
{
	if (g_pKeyManager->isOnceKeyDown(VK_F2)) // 게임 초기화
		this->Init();

	

	if (m_pPlayer->GetIsDead())
	{
		//Game over Count
		if (m_fCount <= 0.0f)
		{	
			if (m_vColorT.a < 1.0f)
				m_vColorT.a += g_pTimeManager->GetDeltaTime();
			else
				m_vColorT.a = 1.0f;
		}
		else
		{
			m_fCount -= g_pTimeManager->GetDeltaTime();
		}

		if (g_pKeyManager->isOnceKeyDown(VK_LBUTTON))
		{
			m_fCount--;
		}

		if (g_pKeyManager->isOnceKeyDown(VK_F1))
		{
			Init();
		}

		m_pGameOver->SetPosition(WINSIZEX * 0.5f, WINSIZEY * 0.5f);
		m_pGameOver->SetConstantScale(WINSIZEX, WINSIZEY);
		m_pGameOver->SetColor(m_vColorT);
		m_pGameOver->Update();
	}
	else if (m_pBoss->GetIsGameClear())
	{
		//GameClear
		
	}
	else
	{
		g_pBulletManager->Update();
		m_pBoss->Update();
		m_pPlayer->Update();
	}


}

void MainGame::Render()
{
	D3DXCOLOR Map = D3DXCOLOR(0, 0, 0, 1);
	DeviceContext->ClearRenderTargetView(RTV, (float*)Map);
	DeviceContext->VSSetConstantBuffers(0, 1, &m_pViewProjBuffer);

	DeviceContext->OMSetBlendState(m_pAlphaBlendState, NULL, 0xFF);

	if (m_pPlayer->GetIsDead())
	{
		if (m_fCount > 0.0f)
		{
			g_pTextManager->IntRender((int)m_fCount, WINSIZEX * 0.5f - 100.0f, WINSIZEY * 0.5f, 200, NumberType::White);
		}
		else
		{
			m_pGameOver->Render();
		}
	
	}
	else if (m_pBoss->GetIsGameClear())
	{
		//GameClear

	}
	else
	{
		m_pBoss->Render();
		g_pBulletManager->Render();
		m_pPlayer->Render();
	}
	

	DeviceContext->OMSetBlendState(m_pNormalBlendState, NULL, 0xFF);

	ImGui::Render();

	SwapChain->Present(0, 0);
}

