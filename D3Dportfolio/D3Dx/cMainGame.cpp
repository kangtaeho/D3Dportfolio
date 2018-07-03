#include "stdafx.h"
#include "cMainGame.h"
#include "cCamera.h"
#include "cCube.h"


cMainGame::cMainGame()
	: m_pCamera(NULL)
	, m_pCube(NULL)
{
}


cMainGame::~cMainGame()
{
	delete m_pCamera;
	delete m_pCube;
	delete m_pshop;
}

HRESULT cMainGame::Setup()
{
	cGameNode::Setup();

	addSprite();

	g_pD3DDevice->SetRenderState(D3DRS_LIGHTING, false);
	
	m_pCamera = new cCamera;
	m_pCamera->Setup();

	m_pCube = new cCube;
	m_pCube->Setup(D3DXVECTOR3(2.0f, 2.0f, 2.0f), NULL);

	m_pshop = new cShop;
	m_pshop->setup();
	return S_OK;
}

void cMainGame::Update()
{
	cGameNode::Update();

	if (m_pCamera)
		m_pCamera->Update();

	if (m_pCube)
		m_pCube->Update();

	if (m_pshop)
		m_pshop->update();
}

void cMainGame::Render()
{
	g_pD3DDevice->Clear(NULL, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER,
		D3DCOLOR_XRGB(0, 0, 200), 1.0f, 0);

	g_pD3DDevice->BeginScene();
	g_pTimeManager->Render();
/*------------------------------------------------------------------------*/

	if (m_pCube)
		m_pCube->Render();

	if (m_pshop)
		m_pshop->render();

/*------------------------------------------------------------------------*/
	g_pD3DDevice->EndScene();

	g_pD3DDevice->Present(NULL, NULL, NULL, NULL);
}

void cMainGame::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	if (m_pCamera)
		m_pCamera->WndProc(hWnd, message, wParam, lParam);
}
