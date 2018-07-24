#include "stdafx.h"
#include "cLoadingScene.h"
#include "cPlayer.h"
#include "cShop.h"
#include "cStatus.h"

cLoadingScene::cLoadingScene()
	:m_bLoadingCompletion(false)
{
}


cLoadingScene::~cLoadingScene()
{
}

HRESULT cLoadingScene::Setup()
{
	return S_OK;
}

void cLoadingScene::Release()
{
}

void cLoadingScene::Update()
{

}

void cLoadingScene::Render()
{
}

void cLoadingScene::LoadingData()
{
	if (m_bLoadingCompletion) return;

	// 플레이어
	m_pPlayer = new cPlayer;
	m_pPlayer->Setup("Teemo");

	// UI
	m_pShop = new cShop;
	m_pStatus = new cStatus;

	m_bLoadingCompletion = true;

}
