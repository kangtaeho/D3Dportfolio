#include "stdafx.h"
#include "cPlayScene.h"
#include "cPlayer.h"
#include "cSphere.h"
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
	g_pTextureManager->addTexture("potion", "./item/potion.dds", START_ITEM, CONSUME);
	g_pTextureManager->addTexture("shoes", "./item/1001_Boots_of_Speed.dds", START_ITEM, EQUIPABLE);
	g_pTextureManager->addTexture("LongSword", "./item/1036_Long_Sword.dds", EARLY_ITEM, EQUIPABLE);
	g_pTextureManager->addTexture("Dagger", "./item/1042_Dagger.dds", EARLY_ITEM, EQUIPABLE);
	g_pTextureManager->addTexture("phage", "./item/3044_Phage.dds", CORE_ITEM, EQUIPABLE);
	g_pTextureManager->addTexture("Sheen", "./item/3057_Sheen.dds", CORE_ITEM, EQUIPABLE);
	g_pTextureManager->addTexture("Red_Orb", "./item/3095_Orb_of_Valor.dds", BASIC_ITEM, EQUIPABLE);
	g_pTextureManager->addTexture("Trinity_Force", "./item/3078_Trinity_Force.dds", CORE_ITEM, EQUIPABLE);
	g_pTextureManager->addTexture("Ward", "./item/3350_GreaterYellowTrinket.dds", START_ITEM, ACCESSORY);
	g_pTextureManager->addTexture("Blue_Orb", "./item/1027_Sapphire_Sphere.dds", START_ITEM, EQUIPABLE);
	g_pTextureManager->addTexture("sp", "./item/3058_Sheen_and_Phage.dds", START_ITEM, EQUIPABLE);



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

	m_pPlayer->Setup("Teemo");


	shop = new cShop;
	status = new cStatus;

	m_pMainUi = status;
	m_pMainUi->AddChild(shop, "SHOP");
	m_pMainUi->setup();

	changed = false;

	return S_OK;
}

void cPlayScene::Release()
{
	if(m_pPlayer)
		m_pPlayer->Release();
}

void cPlayScene::Update()
{
	g_pProgreesBar->update();

	D3DXVECTOR3 tempposition(0, 0, 0);
	D3DXMATRIX WorldMatrix, matProj, matViewPort, matView;
	D3DXMatrixTranslation(&WorldMatrix, m_pPlayer->getPosition().x, m_pPlayer->getPosition().y, m_pPlayer->getPosition().y);
	D3DVIEWPORT9 tempViewPort;
	g_pD3DDevice->GetViewport(&tempViewPort);
	D3DXMatrixIdentity(&matViewPort);
	matViewPort._11 = tempViewPort.Width / (float)2;
	matViewPort._22 = -(int)tempViewPort.Height / (float)2;
	matViewPort._33 = tempViewPort.MaxZ - tempViewPort.MinZ;
	matViewPort._41 = tempViewPort.X + tempViewPort.Width / (float)2;
	matViewPort._42 = tempViewPort.Y + tempViewPort.Height / (float)2;
	matViewPort._43 = tempViewPort.MinZ;
	g_pD3DDevice->GetTransform(D3DTS_PROJECTION, &matProj);
	g_pD3DDevice->GetTransform(D3DTS_VIEW, &matView);

	WorldMatrix = WorldMatrix * matView * matProj * matViewPort;
	D3DXVec3TransformCoord(&tempposition, &tempposition, &WorldMatrix);

	g_pProgreesBar->setBarPosition(tempposition, tempposition);





	if (m_pPlayer)
		m_pPlayer->Update();


	shop->GoldUpdate();
	if (m_pMainUi)
	{
		m_pMainUi->update();
	}

	if (g_pKeyManager->IsOnceKeyDown(VK_ESCAPE))
	{
		m_pMainUi->SetNodeName("");
	}

	status->SetvecInven(shop->GetvecInventory());
	status->InvenUpdate();


	if (g_pKeyManager->IsOnceKeyDown('0'))
	{
		g_pSceneManager->ChangeScene("선택창");
	}
}

void cPlayScene::Render()
{
	if (m_pPlayer)
		m_pPlayer->Render();
	

	//status->InvenRender();

	if (m_pMainUi)
		m_pMainUi->render();

	g_pProgreesBar->render();

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

}
