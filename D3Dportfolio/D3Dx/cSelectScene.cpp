#include "stdafx.h"
#include "cSelectScene.h"
#include "Bitmap.h"

cSelectScene::cSelectScene()
{
}


cSelectScene::~cSelectScene()
{
}

HRESULT cSelectScene::Setup()
{
	m_pMainSelectWin= g_pTextureManager->addTexture("selecteWin", "./select/selectWin.png", NULL, NULL);
	m_pMainSelectWin->setPosition(D3DXVECTOR3(0, 0, 0));
	m_pMainSelectWin->setScale(D3DXVECTOR3(0, 0, 0));

	return S_OK;
}

void cSelectScene::Update()
{
	
}

void cSelectScene::Render()
{
	m_pMainSelectWin->Render();
}

void cSelectScene::Release()
{
	m_pMainSelectWin->release();
}
