#include "stdafx.h"
#include "cPlayScene.h"
#include "cPlayer.h"
#include "cSphere.h"
#include "cCollisionMap.h"
#include "cShop.h"
#include "cStatus.h"
cPlayScene::cPlayScene()
	: m_pPlayer(NULL)
{
}


cPlayScene::~cPlayScene()
{
	// 사용하지말고 Release에서 메모리 해제를 하자
}

HRESULT cPlayScene::Setup()
{
	g_pTextureManager->addTexture("selecteButton", "./testFile/selected2.dds", BUTTON, NULL);
	g_pTextureManager->addTexture("purchaseButton", "./testFile/purchase.dds", BUTTON, NULL);
	g_pTextureManager->addTexture("purchaseButtonDown", "./testFile/purchaseButtonDown.dds", BUTTON, NULL);
	g_pTextureManager->addTexture("purchaseButtonOver", "./testFile/purchaseButtonOver.dds", BUTTON, NULL);
	g_pTextureManager->addTexture("saleButtonDown", "./testFile/saleButtonDown.dds", BUTTON, NULL);
	g_pTextureManager->addTexture("saleButtonOver", "./testFile/saleButtonOver.dds", BUTTON, NULL);
	g_pTextureManager->addTexture("saleButtonUp", "./testFile/saleButtonUp.dds", BUTTON, NULL);
	g_pTextureManager->addTexture("returnButtonUp", "./testFile/returnButtonUp.dds", BUTTON, NULL);
	g_pTextureManager->addTexture("returnButtonOver", "./testFile/returnButtonOver.dds", BUTTON, NULL);
	g_pTextureManager->addTexture("returnButtonDown", "./testFile/returnButtonDown.dds", BUTTON, NULL);
	g_pTextureManager->addTexture("wholeButtonDown", "./testFile/wholeButtonDown.dds", BUTTON, NULL);
	g_pTextureManager->addTexture("wholeButtonOver", "./testFile/wholeButtonOver.dds", BUTTON, NULL);
	g_pTextureManager->addTexture("wholeButtonUp", "./testFile/wholeButtonUp.dds", BUTTON, NULL);
	g_pTextureManager->addTexture("recommandButtonUp", "./testFile/recommandButtonUp.dds", BUTTON, NULL);
	g_pTextureManager->addTexture("recommandButtonOver", "./testFile/recommandButtonOver.dds", BUTTON, NULL);
	g_pTextureManager->addTexture("recommandButtonDown", "./testFile/recommandButtonDown.dds", BUTTON, NULL);
	g_pTextureManager->addTexture("ListBoxTrue", "./testFile/ListBoxTrue.dds", BUTTON, NULL);
	g_pTextureManager->addTexture("ListBoxFalse", "./testFile/ListBoxFalse.dds", BUTTON, NULL);
	g_pTextureManager->addTexture("shopButtonDown", "./status/shopButtonDown.dds", BUTTON, 1, 1);
	g_pTextureManager->addTexture("shopButtonOver", "./status/shopButtonOver.dds", BUTTON, 1, 1);
	g_pTextureManager->addTexture("shopButtonUP", "./status/shopButtonUP.dds", BUTTON, 1, 1);
	//g_pXfileManager->AddXfile("Map", "summoner rift", "summoner_rift.x");

	D3DXMATRIX matWorld, matT, matS, matR;
	D3DXMatrixRotationY(&matR, D3DX_PI);
	D3DXMatrixScaling(&matS, 300.0f, 300.0f, 300.0f);
	matWorld = matR * matS;
	std::vector<D3DXVECTOR3> vMapGround;
	std::vector<D3DXVECTOR3> vMapObject;
	
	colMap = new cCollisionMap;
	//colMap->LoadSurface(vMapGround, "map collision", "map_skp_sample.obj", &matWorld);		// 바닥
	//colMap->LoadSurface(vMapObject, "map collision", "map_collision.obj", &matWorld);

	m_pPlayer = new cPlayer;
	m_pPlayer->Setup("Teemo");
	m_pPlayer->setMap(colMap->getMap());						// 바닥
	m_pPlayer->setCollisionMap(colMap->getCollisionMap());		// 벽충돌인듯


	cShop* shop = new cShop;
	cStatus* status = new cStatus;

	m_pMainUi = status;
	m_pMainUi->AddChild(shop, "SHOP");
	m_pMainUi->setup();
	return S_OK;
}

void cPlayScene::Release()
{
	if(m_pPlayer)
		m_pPlayer->Release();
}

void cPlayScene::Update()
{
	if (m_pPlayer)
		m_pPlayer->Update();


	if (g_pKeyManager->IsOnceKeyDown('O'))
	{
		m_pMainUi->SetNodeName("SHOP");
	}
	if (g_pKeyManager->IsOnceKeyDown(VK_ESCAPE))
	{
		m_pMainUi->SetNodeName("");
	}

	if (m_pMainUi)
	{
		m_pMainUi->update();

	}
}

void cPlayScene::Render()
{
	if (m_pPlayer)
		m_pPlayer->Render();

	if (m_pMainUi)
		m_pMainUi->render();

	{//맵추가
		g_pD3DDevice->SetRenderState(D3DRS_LIGHTING, false);
		g_pD3DDevice->SetRenderState(D3DRS_ALPHATESTENABLE, true);
		g_pD3DDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);
		D3DXMATRIX mat, matS;
		D3DXMatrixIdentity(&mat);
		D3DXMatrixIdentity(&matS);
		D3DXMatrixScaling(&matS, 300.0f, 300.0f, 300.0f);
		mat = matS;
	}

	 colMap->Render();

}
