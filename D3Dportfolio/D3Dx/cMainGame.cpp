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

	g_pDeviceManager->Destroy();
}

void cMainGame::Setup()
{
	g_pD3DDevice->SetRenderState(D3DRS_LIGHTING, false);
	g_pFontManager->Setup();

	m_pCamera = new cCamera;
	m_pCamera->Setup();

	m_pCube = new cCube;
	m_pCube->Setup(D3DXVECTOR3(2.0f, 2.0f, 2.0f), NULL);

}

void cMainGame::Update()
{
	g_pTimeManager->Update();

	if (m_pCamera)
		m_pCamera->Update();

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


/*------------------------------------------------------------------------*/
	g_pD3DDevice->EndScene();

	g_pD3DDevice->Present(NULL, NULL, NULL, NULL);
}

void cMainGame::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	if (m_pCamera)
		m_pCamera->WndProc(hWnd, message, wParam, lParam);
}
