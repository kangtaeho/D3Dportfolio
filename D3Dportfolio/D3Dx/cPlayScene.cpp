#include "stdafx.h"
#include "cPlayScene.h"
#include "cPlayer.h"

cPlayScene::cPlayScene()
	:m_pPlayer(NULL)
{
}


cPlayScene::~cPlayScene()
{
	// ����������� Release���� �޸� ������ ����
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
