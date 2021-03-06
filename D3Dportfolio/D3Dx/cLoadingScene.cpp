#include "stdafx.h"
#include "cLoadingScene.h"
#include "cPlayer.h"
#include "cShop.h"
#include "cStatus.h"

cLoadingScene::cLoadingScene()
	:m_fCurrentData(0.0f)
{
}


cLoadingScene::~cLoadingScene()
{
}

HRESULT cLoadingScene::Setup()
{
	m_pLoadingScreen= g_pTextureManager->addTexture("loadingScreen", "./select/loadingScreen.png", NULL, NULL);
	m_pLoadingScreen->setPosition(D3DXVECTOR3(0, 0, 0));
	m_pLoadingScreen->setScale(D3DXVECTOR3(1, 1, 1));
	return S_OK;
}

void cLoadingScene::Release()
{
	if (m_pLoadingScreen)
		m_pLoadingScreen->release();
}

void cLoadingScene::Update()
{
	LoadingData();
}

void cLoadingScene::Render()
{
	if (m_pLoadingScreen)
		m_pLoadingScreen->Render();

	g_pFontManager->TextFont(688, 341, D3DXVECTOR3(255, 255, 255), "%0.0f", m_fCurrentData);
}

void cLoadingScene::LoadingData()
{

	int fullFath, loadFath;
	int fullFath1, loadFath1;

	for(int i=0; i<100; i++) g_pCollisionManager->Setup(fullFath, loadFath);
	
	g_pXfileManager->Setup(fullFath1, loadFath1);
	m_fCurrentData = ((float)(loadFath + loadFath1) / (float)(fullFath + fullFath1)) * 100.0;
	
	if (m_fCurrentData >= 100.0f)
	{
		g_pSceneManager->ChangeScene("�÷��̾�");
	}

	if (g_pKeyManager->IsOnceKeyDown('0'))
	{
		g_pSceneManager->ChangeScene("�÷��̾�");
	}
}
