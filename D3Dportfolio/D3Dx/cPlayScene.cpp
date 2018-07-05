#include "stdafx.h"
#include "cPlayScene.h"
#include "cPlayer.h"

cPlayScene::cPlayScene()
	:m_pPlayer(NULL)
{
}


cPlayScene::~cPlayScene()
{
	// 사용하지말고 Release에서 메모리 해제를 하자
}

HRESULT cPlayScene::Setup()
{
	m_pPlayer = new cPlayer;
	m_pPlayer->Setup();
	return S_OK;
}

void cPlayScene::Release()
{
	delete m_pPlayer;
}

void cPlayScene::Update()
{
	if (m_pPlayer)
		m_pPlayer->Update();
}

void cPlayScene::Render()
{
	if (m_pPlayer)
		m_pPlayer->Render();
}
