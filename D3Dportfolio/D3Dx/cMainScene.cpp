#include "stdafx.h"
#include "cMainScene.h"
#include "cShop.h"

cMainScene::cMainScene()
	: m_pshop(NULL)
{
}


cMainScene::~cMainScene()
{
	// �����������
}

HRESULT cMainScene::Setup()
{

	m_pshop = new cShop;
	m_pshop->setup();

	return S_OK;
}

void cMainScene::Release()
{
	delete m_pshop;
}

void cMainScene::Update()
{
	// 0�� ������ �÷��̾����� ����(���߿� ���� ���)
	if (g_pKeyManager->IsOnceKeyDown('0'))
	{
		g_pSceneManager->ChangeScene("�÷��̾�");
	}
}

void cMainScene::Render()
{

	if (m_pshop)
		m_pshop->render();
}
