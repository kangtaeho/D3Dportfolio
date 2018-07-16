#include "stdafx.h"
#include "cStatus.h"
#include "Bitmap.h"
#include "cUIButton.h"

cStatus::cStatus()
{
}


cStatus::~cStatus()
{
}
void cStatus::setup()  
{
	m_pPlayerInfo = new tagPlayerInfo;


	m_pPlayerInfo->SkillInfo.Skill_Q = g_pTextureManager->addTexture("Teemo_Q", "./status/Teemo_Q.dds", UI, NULL);
	m_pPlayerInfo->SkillInfo.Skill_W = g_pTextureManager->addTexture("Teemo_W", "./status/Teemo_W.dds", UI, NULL);
	m_pPlayerInfo->SkillInfo.Skill_E = g_pTextureManager->addTexture("Teemo_E", "./status/Teemo_E.dds", UI, NULL);
	m_pPlayerInfo->SkillInfo.Skill_R = g_pTextureManager->addTexture("Teemo_R", "./status/Teemo_R.dds", UI, NULL);
	m_pPlayerInfo->SkillInfo.Skill_Passive = g_pTextureManager->addTexture("Teemo_E", "./status/Teemo_E.dds", UI, NULL);

	abc = false;


	m_pShopButton = new cUIButton;
	m_pShopButton->setTexture("shopButtonUP", "shopButtonOver", "shopButtonDown");
	m_pShopButton->setPosition(D3DXVECTOR3(815, 700, 0));

	m_pStatusHealthBar = new Bitmap;
	m_pStatusHealthBar = g_pTextureManager->addTexture("HealthBar", "./status/hpBar.dds", PROGRESSBAR,1,1);
	m_pStatusHealthBar->setPosition(D3DXVECTOR3(311, 683, 0));
	m_pStatusHealthBar->setScale(D3DXVECTOR3(1.018f, 1.1f, 0));

	m_pStatusMpBar = new Bitmap;
	m_pStatusMpBar = g_pTextureManager->addTexture("MpBar", "./status/MpBar.dds", PROGRESSBAR, 1, 1);
	m_pStatusMpBar->setPosition(D3DXVECTOR3(311, 705, 0));
	m_pStatusMpBar->setScale(D3DXVECTOR3(1.018f, 1.1f, 0));

	m_pCharacterBar = new Bitmap;
	m_pCharacterBar = g_pTextureManager->addTexture("CharacterIcon", "./status/CharacterIcon.dds", UI, NULL);
	m_pCharacterBar->setPosition(D3DXVECTOR3(145, 580, 0));
	m_pStatusInventory = new Bitmap;
	m_pStatusInventory = g_pTextureManager->addTexture("InventoryTexture", "./status/statusInventory.dds", UI,NULL);
	m_pStatusInventory->setPosition(D3DXVECTOR3(800, 570, 0));

	m_pStatusScreen = new Bitmap;
	m_pStatusScreen = g_pTextureManager->addTexture("StatusScreen", "./status/statusScreen.dds", UI, NULL);
	m_pStatusScreen->setPosition(D3DXVECTOR3(260, 570, 0));

	m_pCharacterIcon = new Bitmap;
	m_pCharacterIcon = g_pTextureManager->addTexture("CharacterIcon", "./status/Teemo_Circle_0.dds", UI, NULL);
	m_pCharacterIcon->setPosition(D3DXVECTOR3(167, 600, 0));
	m_pCharacterIcon->setScale(D3DXVECTOR3(0.9f, 0.9f, 0));

	m_pBuffInfo = new Bitmap;
	m_pBuffInfo = g_pTextureManager->addTexture("BuffInfo", "./status/BuffInfo.dds", UI, NULL);
	m_pBuffInfo->setPosition(D3DXVECTOR3(164, 687, 0));

	m_pStatusPlayerInfoIcon = new Bitmap;
	m_pStatusPlayerInfoIcon = g_pTextureManager->addTexture("PlayerInfoIcon", "./status/playerInfo.dds", UI, NULL);
	m_pStatusPlayerInfoIcon->setPosition(D3DXVECTOR3(147, 673, 0));

	m_pTeleport = new Bitmap;
	m_pTeleport = g_pTextureManager->addTexture("TeleportHome", "./status/TeleportHome.dds", UI, NULL);
	m_pTeleport->setPosition(D3DXVECTOR3(975, 650, 0));
	//m_pSkillButton = new cUIButton;
	RECT rc;
	float MaxHp = 100000;
	m_pPlayerInfo->HealthInfo.Hp = MaxHp;
	float hit = m_pPlayerInfo->HealthInfo.Hp -= 30;

	hit = MaxHp / hit;


	if (!abc)
	{
		a = m_pStatusHealthBar->GetrectFrameSize()->right;
		b = m_pStatusHealthBar->GetrectFrameSize()->bottom;
		abc = true;
	}
	SetRect(&rc, 0, 0, MaxHp, b);
	float c = a / MaxHp;
	m_pStatusHealthBar->SetRectFrameSize(rc);
	m_pStatusHealthBar->setScale(D3DXVECTOR3(c, 1.1f, 0));


	
	cMainUI::setup();
}
void cStatus::update()	
{
	if (m_pStatusInventory)
		m_pStatusInventory->update();
	if (m_pStatusScreen)
		m_pStatusScreen->update();
	if (m_pCharacterIcon)
		m_pCharacterIcon->update();
	if (m_pBuffInfo)
		m_pBuffInfo->update();
	if (m_pStatusPlayerInfoIcon)
		m_pStatusPlayerInfoIcon->update();
	if (m_pTeleport)
		m_pTeleport->update();
	if (m_pCharacterBar)
		m_pCharacterBar->update();

	if (m_pStatusHealthBar)
	{
		m_pStatusHealthBar->update(0);
		
		//m_pStatusHealthBar->GetrectFrameSize()->right -= 1000;
	}


	if (m_pShopButton->GetButttonState() == 2)
		m_pNodeName = "SHOP";

	if (m_pStatusMpBar)
	{
		m_pStatusMpBar->update(0);
	}

	if (m_pPlayerInfo != NULL)
	{
		m_pPlayerInfo->SkillInfo.Skill_Q->update();
		m_pPlayerInfo->SkillInfo.Skill_W->update();
		m_pPlayerInfo->SkillInfo.Skill_E->update();
		m_pPlayerInfo->SkillInfo.Skill_R->update();
		m_pPlayerInfo->SkillInfo.Skill_Passive->update();
	}
	

	

	m_mapiter = m_mapChild.find("SHOP");
	if (m_mapiter != m_mapChild.end())
	{
		m_pStatusGold.amount = m_mapiter->second->GetGold().amount;
		m_pStatusGold.count = m_mapiter->second->GetGold().count;
		m_pStatusGold.goldIncreaseTime = m_mapiter->second->GetGold().goldIncreaseTime;
		m_pStatusGold.Gold_huans = m_mapiter->second->GetGold().Gold_huans;
		m_pStatusGold.Gold_tens = m_mapiter->second->GetGold().Gold_tens;
		m_pStatusGold.Gold_thous = m_mapiter->second->GetGold().Gold_thous;
		m_pStatusGold.Gold_units = m_mapiter->second->GetGold().Gold_units;
	}
	if (m_pStatusGold.amount <= 9999)
	{
		m_pStatusGold.Gold_units->update(0);
		m_pStatusGold.Gold_tens->update(0);
		m_pStatusGold.Gold_huans->update(0);
		m_pStatusGold.Gold_thous->update(0);
	}

	m_pStatusGold.Gold_units->setCurrentFrame((m_pStatusGold.amount % 10) / 1);
	m_pStatusGold.Gold_tens->setCurrentFrame((m_pStatusGold.amount % 100) / 10);
	m_pStatusGold.Gold_huans->setCurrentFrame((m_pStatusGold.amount % 1000) / 100);
	m_pStatusGold.Gold_thous->setCurrentFrame(m_pStatusGold.amount / 1000);

	m_pStatusGold.Gold_units->setPosition(D3DXVECTOR3(400,0,0));
	m_pStatusGold.Gold_tens->setPosition(D3DXVECTOR3(300,0,0));
	m_pStatusGold.Gold_huans->setPosition(D3DXVECTOR3(200,0,0));
	m_pStatusGold.Gold_thous->setPosition(D3DXVECTOR3(100,0,0));




	
	if (m_pShopButton)
		m_pShopButton->update();

	cMainUI::update();
}
void cStatus::release()
{
	cMainUI::Destroy();
}
void cStatus::render()	
{
	if (m_pStatusInventory)
		m_pStatusInventory->Render();
	if (m_pStatusScreen)
		m_pStatusScreen->Render();
	if (m_pTeleport)
		m_pTeleport->Render();
	if (m_pSkillButton)
		m_pSkillButton->Render();
	
	if (m_pCharacterBar)
		m_pCharacterBar->Render();
	if (m_pCharacterIcon)
		m_pCharacterIcon->Render();
	if (m_pStatusPlayerInfoIcon)
		m_pStatusPlayerInfoIcon->Render();
	if (m_pBuffInfo)
		m_pBuffInfo->Render();

	if (m_pStatusHealthBar)
		m_pStatusHealthBar->aniRender();
	if (m_pStatusMpBar)
		m_pStatusMpBar->aniRender();

	if (m_pShopButton)
		m_pShopButton->Render();



	if (m_pPlayerInfo != NULL)
	{
		m_pPlayerInfo->SkillInfo.Skill_Q->Render();
		m_pPlayerInfo->SkillInfo.Skill_W->Render();
		m_pPlayerInfo->SkillInfo.Skill_E->Render();
		m_pPlayerInfo->SkillInfo.Skill_R->Render();
		m_pPlayerInfo->SkillInfo.Skill_Passive->Render();
	}
	
	if (m_pStatusGold.amount != 0)
		m_pStatusGold.Gold_units->aniRender();
	if (m_pStatusGold.amount > 10)
		m_pStatusGold.Gold_tens->aniRender();
	if (m_pStatusGold.amount >= 100)
		m_pStatusGold.Gold_huans->aniRender();
	if (m_pStatusGold.amount >= 1000)
		m_pStatusGold.Gold_thous->aniRender();
	cMainUI::render();
	//g_pFontManager->TextFont(10, 200 + 20, "¿Í½ç");
	
}