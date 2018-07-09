#include "stdafx.h"
#include "cTestPlay.h"
#include "cCube.h"

cTestPlay::cTestPlay()
	:m_fRotY(0)
{
}


cTestPlay::~cTestPlay()
{
	delete m_pCube;
}

HRESULT cTestPlay::Setup()
{
	m_pCube = new cCube;
	m_pCube->Setup(D3DXVECTOR3(100, 100, 100), NULL);
	return S_OK;
}

void cTestPlay::Update()
{
	if (g_pKeyManager->IsStayKeyDown(VK_LEFT))
	{
		m_fRotY += 0.05;
	}

	if (g_pKeyManager->IsStayKeyDown(VK_RIGHT))
	{
		m_fRotY += 0.05;
	}

	if (g_pKeyManager->IsOnceKeyDown(VK_SPACE))
	{

	}
	D3DXMATRIX matT;
	D3DXMatrixTranslation(&matT, 100, 5127, 100);
	m_pCube->SetMatWorld(matT);
}

void cTestPlay::Render()
{
	m_pCube->Render();
}
