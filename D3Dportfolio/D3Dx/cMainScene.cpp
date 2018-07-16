#include "stdafx.h"
#include "cMainScene.h"
#include "cShop.h"

cMainScene::cMainScene()
	: m_pshop(NULL)
{
}


cMainScene::~cMainScene()
{
	// 사용하지말자
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
	// 0번 누르면 플레이씬으로 간다(나중에 삭제 요망)
	if (g_pKeyManager->IsOnceKeyDown('0'))
	{
		g_pSceneManager->ChangeScene("플레이씬");
	}
}

void cMainScene::Render()
{

}
