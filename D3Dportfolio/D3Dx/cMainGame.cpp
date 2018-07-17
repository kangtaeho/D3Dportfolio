#include "stdafx.h"
#include "cMainGame.h"
#include "cMainScene.h"
#include "cPlayScene.h"
#include "cSelectScene.h"


cMainGame::cMainGame()
{
}

cMainGame::~cMainGame()
{

}

HRESULT cMainGame::Setup()
{
	cGameNode::Setup();

	addSprite();

	g_pD3DDevice->SetRenderState(D3DRS_LIGHTING, false);
	
	g_pSceneManager->AddScene("�׽�Ʈ", new cMainScene);
	g_pSceneManager->AddScene("�÷��̾�", new cPlayScene);
	g_pSceneManager->AddScene("����â", new cSelectScene);

	g_pSceneManager->ChangeScene("�׽�Ʈ");

	return S_OK;
}

void cMainGame::Release()
{
	cGameNode::Release();
}

void cMainGame::Update()
{
	cGameNode::Update();

	g_pSceneManager->Update();

}

void cMainGame::Render()
{
	g_pD3DDevice->Clear(NULL, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER,
		D3DCOLOR_XRGB(0, 0, 200), 1.0f, 0);

	g_pD3DDevice->BeginScene();
/*------------------------------------------------------------------------*/

	g_pSceneManager->Render();

/*------------------------------------------------------------------------*/
	g_pTimeManager->Render();
	g_pD3DDevice->EndScene();

	g_pD3DDevice->Present(NULL, NULL, NULL, NULL);
}
