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


	return S_OK;
}

void cMainScene::Release()
{
	
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

}
