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
	g_pTextureManager->addTexture("selecteWin", "./select/selectWin.png", NULL, NULL);
	g_pTextureManager->addTexture("selectPlayerWin01", "./select/selectPlayerWin01.png", NULL, NULL);
	g_pTextureManager->addTexture("selectPlayerWin02", "./select/selectPlayerWin02.png", NULL, NULL);
	g_pTextureManager->addTexture("selectRect", "./select/selectRect.png", NULL, NULL);
	g_pTextureManager->addTexture("cIcon01", "./select/cIcon01.png", NULL, NULL);
	g_pTextureManager->addTexture("cIcon02", "./select/cIcon02.png", NULL, NULL);
	g_pTextureManager->addTexture("cIcon03", "./select/cIcon03.png", NULL, NULL);
	g_pTextureManager->addTexture("cIcon04", "./select/cIcon04.png", NULL, NULL);
	g_pTextureManager->addTexture("cIcon05", "./select/cIcon05.png", NULL, NULL);
	g_pTextureManager->addTexture("cIcon06", "./select/cIcon06.png", NULL, NULL);
	g_pTextureManager->addTexture("cIcon07", "./select/cIcon07.png", NULL, NULL);
	g_pTextureManager->addTexture("cIcon08", "./select/cIcon08.png", NULL, NULL);
	g_pTextureManager->addTexture("cIcon09", "./select/cIcon09.png", NULL, NULL);
	g_pTextureManager->addTexture("cIcon10", "./select/cIcon10.png", NULL, NULL);

	m_pMainSelectWin = g_pTextureManager->findTexture("selectWin");
	m_pMainSelectWin->setPosition(D3DXVECTOR3(0, 0, 0));
	m_pMainSelectWin->setScale(D3DXVECTOR3(0, 0, 0));

	m_pPlayerSelect = g_pTextureManager->findTexture("selectPlayerWin01");
	m_pMainSelectWin->setPosition(D3DXVECTOR3(22, 67, 0));
	m_pMainSelectWin->setScale(D3DXVECTOR3(0, 0, 0));

	

	return S_OK;
}

void cSelectScene::Update()
{
	
}

void cSelectScene::Render()
{
	if (m_pMainSelectWin)
		m_pMainSelectWin->Render();

	if (m_pPlayerSelect)
		m_pPlayerSelect->Render();

	if (m_pPlayerChamp)
		m_pPlayerChamp->Render();

	if (m_pEnemyChamp)
		m_pEnemyChamp->Render();

	if (m_pSelect)
		m_pSelect->Render();
}

void cSelectScene::Release()
{
	if (m_pMainSelectWin)
	m_pMainSelectWin->release();
}
