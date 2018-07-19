#include "stdafx.h"
#include "cLoadingScene.h"
#include "cPlayer.h"
#include "cCollisionMap.h"
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
	shop = new cShop;
	status = new cStatus;

	m_bLoadingCompletion = true;

}
