#include "stdafx.h"
#include "cPlayScene.h"
#include "cPlayer.h"
#include "cSphere.h"
#include "cShop.h"
#include "cStatus.h"
#include "cHealthProgress.h"
#include "cMinimap.h"
#include "cObjectManager.h"
#include "cAshe.h"

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
	g_pCameraManager->UsingMoveWindow();

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
	g_pTextureManager->addTexture("Dead", "./status/Dead.dds", 0, 0);

	//g_pXfileManager->AddXfile("Map", "summoner rift", "summoner_rift.x");

	g_pTextureManager->findTexture("Dead")->Setalphavalue(0);
	m_pPlayer = new cPlayer;
	m_pPlayer->Setup("Teemo");

	shop = new cShop;
	status = new cStatus;
	m_pMinimap = new cMinimap;
	m_pMinimap->setup();

	m_pMainUi = status;
	m_pMainUi->AddChild(shop, "SHOP");
	m_pMainUi->setup();

	changed = false;

	cHealthProgress* PlayerProgress = new cHealthProgress;
	Bitmap* Container; Bitmap* HpBar; Bitmap* MpBar;
	Container = g_pTextureManager->addTexture("Container...", "./status/playerHpContainer.dds", NULL, NULL);
	HpBar = g_pTextureManager->addTexture("PlayerHpBar...", "./status/playerHpBar.dds", PROGRESSBAR, 1, 1);
	MpBar = g_pTextureManager->addTexture("PlayerMpBar...", "./status/playerMpBar.dds", PROGRESSBAR, 1, 1);
	PlayerProgress->SetContainer(Container);
	PlayerProgress->SetHpBar(HpBar);
	PlayerProgress->SetMpBar(MpBar);
	PlayerProgress->setup();
	
	m_vecHealthProgress.push_back(PlayerProgress);

	
	status->SetMAXHP(m_pPlayer->GetMAXHP());
	status->SetMAXMP(m_pPlayer->GetMAXMP());
	status->SetCURRENTHP(m_pPlayer->GetHP());
	status->SetCURRENTMP(m_pPlayer->GetMP());
	status->SetMoveSpeed(m_pPlayer->GetSpeed());
	status->SetDefense(m_pPlayer->GetDEF());
	status->SetAtk(m_pPlayer->GetATK());
	status->SetAttackSpeed(m_pPlayer->GetATKSpeed());
	
	status->SetRecorrect(true);

	status->setAddressLinkWithHealthProgress(m_vecHealthProgress[0]);

	status->setAddressLinkWithPlayer(m_pPlayer);

	m_pEnemyManager = new cObjectManager;
	m_pEnemyManager->Setup();
	m_pEnemyManager->setLinkPlayer(m_pPlayer);
	m_pPlayer->SetVecEnemy(m_pEnemyManager->getAllEnemy());
	m_pPlayer->SkillRegisterTarget();


	m_pAshe = new cAshe;
	m_pAshe->Setup("Ashe");
	m_pAshe->SetVecEnemey(m_pEnemyManager->getAllBlue());

	m_pPlayer->SetAshe(m_pAshe);

	return S_OK;

}

void cPlayScene::Release()
{
	if(m_pPlayer)
		m_pPlayer->Release();

	if (m_pAshe)
		m_pAshe->Release();
}

void cPlayScene::Update()
{
	g_pTextureManager->findTexture("Dead")->update();

	if (m_pEnemyManager)
		m_pEnemyManager->Update();

	if (m_pMinimap)
		m_pMinimap->update();

	shop->GoldUpdate();
	if (m_pMainUi)
	{
		m_pMainUi->update();
	}

	if (m_pPlayer)
	{
		m_pPlayer->Update();
	}

	if (m_pMainUi->GetNodeName() == "SHOP")
	{
		if (shop->isClickUi())m_pPlayer->SetIsClickUI(true);
		else m_pPlayer->SetIsClickUI(false);
	}
	else
	{
		m_pPlayer->SetIsClickUI(false);
	}
	
	if (status->isClickUi())m_pPlayer->SetIsClickUI(true);

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

	D3DXVECTOR3 tempposition(0, 0, 0);
	D3DXMATRIX WorldMatrix, matProj, matViewPort, matView;
	D3DXMatrixTranslation(&WorldMatrix, m_pPlayer->getPosition().x, m_pPlayer->getPosition().y, m_pPlayer->getPosition().z);
	D3DVIEWPORT9 tempViewPort;
	g_pD3DDevice->GetViewport(&tempViewPort); //
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

	//스탯설정
	m_vecHealthProgress[0]->setBarPosition(tempposition, tempposition);

	m_vecHealthProgress[0]->SetMaxHp(m_pPlayer->GetMAXHP());
	m_vecHealthProgress[0]->SetCurrentHp(m_pPlayer->GetHP());
	m_vecHealthProgress[0]->SetHitValue(status->GetHitValue());
	m_vecHealthProgress[0]->SetHpBarSize(status->GetCheckHpBar());

	

	m_vecHealthProgress[0]->GetHpBar()->GetrectFrameSize()->right = m_pPlayer->GetHP();
	
	m_vecHealthProgress[0]->SetisHit(status->GetIsHit());

	m_vecHealthProgress[0]->SetMaxMp(status->GetMAXMP());
	m_vecHealthProgress[0]->SetCurrentMp(status->GetCURRENTMP());
	m_vecHealthProgress[0]->SetMpUsed(status->GetUSEDMP());
	m_vecHealthProgress[0]->SetMpBarSize(status->GetCheckMpBar());

	m_vecHealthProgress[0]->update();

	if (g_pKeyManager->IsOnceKeyDown('P')) //스탯이 재조정된다면, 재조정되었다 알림.
	{
		m_vecHealthProgress[0]->SetReCorret(true);
		//status->SetRecorrect(true);
	}

	if (m_pPlayer->GetHP() <= 0)
		g_pTextureManager->findTexture("Dead")->Setalphavalue(150);
	else g_pTextureManager->findTexture("Dead")->Setalphavalue(0);
	// 애쉬
	if (m_pAshe)
		m_pAshe->Update();


	if (m_vecHealthProgress[0]->GetHpBar()->GetrectFrameSize()->right <= 0)
	{
		m_vecHealthProgress[0]->GetHpBar()->GetrectFrameSize()->right = 0;
	}
}

void cPlayScene::Render()
{
	if (m_pEnemyManager)
		m_pEnemyManager->Render();

	//status->InvenRender();
	m_vecHealthProgress[0]->render();

	if (m_pMainUi)
		m_pMainUi->render();

	if (m_pMinimap)
		m_pMinimap->Render();

	if (m_pPlayer)
		m_pPlayer->Render();

	{//맵추가
		g_pD3DDevice->SetRenderState(D3DRS_LIGHTING, false);
		g_pD3DDevice->SetRenderState(D3DRS_ALPHATESTENABLE, true);
		g_pD3DDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);
		D3DXMATRIX mat, matS;
		D3DXMatrixIdentity(&mat);
		D3DXMatrixIdentity(&matS);
		D3DXMatrixScaling(&matS, 300.0f, 300.0f, 300.0f);
		mat = matS;
		g_pD3DDevice->SetTransform(D3DTS_WORLD, &mat);
		if(g_pXfileManager->FindXfile("summoner_rift"))
			g_pXfileManager->FindXfile("summoner_rift")->Render(NULL);
	}

	if (m_pAshe)
		m_pAshe->Render();

	g_pTextureManager->findTexture("Dead")->Render();
}
