#include "stdafx.h"
#include "cStatus.h"
#include "Bitmap.h"
#include "cUIButton.h"
#include "cInventory.h"
#include "citem.h"
#include "cUiSkill.h"
cStatus::cStatus()
{
}


cStatus::~cStatus()
{

}
void cStatus::setup()
{

	g_pTextureManager->addTexture("shopButtonDown", "./status/shopButtonDown.dds", BUTTON, 1, 1);
	g_pTextureManager->addTexture("shopButtonOver", "./status/shopButtonOver.dds", BUTTON, 1, 1);
	g_pTextureManager->addTexture("shopButtonUP", "./status/shopButtonUP.dds", BUTTON, 1, 1);

	m_pRect = new RECT[6];


	m_pPlayerInfo = new tagPlayerInfo;



	m_bIsHit = false;
	m_bCheckBar = false;


	m_pShopOpend = false;
	m_pShopButton = new cUIButton;
	m_pShopButton->setTexture("shopButtonUP", "shopButtonOver", "shopButtonDown");
	m_pShopButton->setPosition(D3DXVECTOR3(815, 700, 0));

	m_pStatusHealthBar = new Bitmap;
	m_pStatusHealthBar = g_pTextureManager->addTexture("HealthBar", "./status/hpBar.dds", PROGRESSBAR, 1, 1);
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
	m_pStatusInventory = g_pTextureManager->addTexture("InventoryTexture", "./status/statusInventory.dds", UI, NULL);
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


	m_pStatusGold.Gold_huans = new Bitmap;
	m_pStatusGold.Gold_tens = new Bitmap;
	m_pStatusGold.Gold_thous = new Bitmap;
	m_pStatusGold.Gold_units = new Bitmap;
	m_pStatusGold.Gold_huans = g_pTextureManager->addTexture("Gold_units", "./item/GoldNum.dds", ANIMATION, 10.0f, 1.0f);
	m_pStatusGold.Gold_tens = g_pTextureManager->addTexture("Gold_tens", "./item/GoldNum.dds", ANIMATION, 10.0f, 1.0f);
	m_pStatusGold.Gold_thous = g_pTextureManager->addTexture("Gold_huans", "./item/GoldNum.dds", ANIMATION, 10.0f, 1.0f);
	m_pStatusGold.Gold_units = g_pTextureManager->addTexture("Gold_thous", "./item/GoldNum.dds", ANIMATION, 10.0f, 1.0f);

	m_pStatusGold.Gold_huans->setScale(D3DXVECTOR3(0.8f, 0.8f, 0));
	m_pStatusGold.Gold_tens->setScale(D3DXVECTOR3(0.8f, 0.8f, 0));
	m_pStatusGold.Gold_thous->setScale(D3DXVECTOR3(0.8f, 0.8f, 0));
	m_pStatusGold.Gold_units->setScale(D3DXVECTOR3(0.8f, 0.8f, 0));

	m_pPlayerInfo->SkillInfo.Skill_Q = g_pTextureManager->addTexture("Teemo_Q", "./status/Teemo_Q.dds", UI, NULL);
	m_pPlayerInfo->SkillInfo.Skill_W = g_pTextureManager->addTexture("Teemo_W", "./status/Teemo_W.dds", UI, NULL);
	m_pPlayerInfo->SkillInfo.Skill_E = g_pTextureManager->addTexture("Teemo_E", "./status/Teemo_E.dds", UI, NULL);
	m_pPlayerInfo->SkillInfo.Skill_R = g_pTextureManager->addTexture("Teemo_R", "./status/Teemo_R.dds", UI, NULL);
	m_pPlayerInfo->SkillInfo.Skill_Passive = g_pTextureManager->addTexture("Teemo_E", "./status/Teemo_P.dds", UI, NULL);

	m_pPlayerInfo->SkillInfo.Skill_Q->setPosition(D3DXVECTOR3(m_pStatusScreen->GetPosition().x + 110, m_pStatusScreen->GetPosition().y + 24, 0));
	m_pPlayerInfo->SkillInfo.Skill_W->setPosition(D3DXVECTOR3(m_pStatusScreen->GetPosition().x + 185, m_pStatusScreen->GetPosition().y + 24, 0));
	m_pPlayerInfo->SkillInfo.Skill_E->setPosition(D3DXVECTOR3(m_pStatusScreen->GetPosition().x + 260, m_pStatusScreen->GetPosition().y + 24, 0));
	m_pPlayerInfo->SkillInfo.Skill_R->setPosition(D3DXVECTOR3(m_pStatusScreen->GetPosition().x + 335, m_pStatusScreen->GetPosition().y + 24, 0));
	m_pPlayerInfo->SkillInfo.Skill_Passive->setPosition(D3DXVECTOR3(m_pStatusScreen->GetPosition().x + 110, m_pStatusScreen->GetPosition().y - 35, 0));

	m_pPlayerInfo->SkillInfo.Skill_Passive->setScale(D3DXVECTOR3(0.55f, 0.55f, 0));


	m_pStatusSkillInfo.reserve(10);



	m_pSkillInfo = new cUiSkill;
	m_pSkillInfo->SetChosen(false);
	m_pSkillInfo->SetskillInfo(m_pPlayerInfo->SkillInfo.Skill_Q);
	m_pSkillInfo->SetvSkillPos(m_pPlayerInfo->SkillInfo.Skill_Q->GetPosition());
	m_pStatusSkillInfo.push_back(m_pSkillInfo);

	m_pSkillInfo = new cUiSkill;
	m_pSkillInfo->SetChosen(false);
	m_pSkillInfo->SetskillInfo(m_pPlayerInfo->SkillInfo.Skill_W);
	m_pSkillInfo->SetvSkillPos(m_pPlayerInfo->SkillInfo.Skill_W->GetPosition());
	m_pStatusSkillInfo.push_back(m_pSkillInfo);

	m_pSkillInfo = new cUiSkill;
	m_pSkillInfo->SetChosen(false);
	m_pSkillInfo->SetskillInfo(m_pPlayerInfo->SkillInfo.Skill_E);
	m_pSkillInfo->SetvSkillPos(m_pPlayerInfo->SkillInfo.Skill_E->GetPosition());
	m_pStatusSkillInfo.push_back(m_pSkillInfo);

	m_pSkillInfo = new cUiSkill;
	m_pSkillInfo->SetChosen(false);
	m_pSkillInfo->SetskillInfo(m_pPlayerInfo->SkillInfo.Skill_R);
	m_pSkillInfo->SetvSkillPos(m_pPlayerInfo->SkillInfo.Skill_R->GetPosition());
	m_pStatusSkillInfo.push_back(m_pSkillInfo);

	m_pSkillInfo = new cUiSkill;
	m_pSkillInfo->SetChosen(false);
	m_pSkillInfo->SetskillInfo(m_pPlayerInfo->SkillInfo.Skill_Passive);
	m_pSkillInfo->SetvSkillPos(m_pPlayerInfo->SkillInfo.Skill_Passive->GetPosition());
	m_pStatusSkillInfo.push_back(m_pSkillInfo);



	setInventoryInfo();

	MaxHp = 3000;
	CurrentHp = 0;
	m_pPlayerInfo->HealthInfo.Hp = MaxHp;
	hit = 30;

	rcRight = m_pStatusHealthBar->GetrectFrameSize()->right;
	rcBottom = m_pStatusHealthBar->GetrectFrameSize()->bottom;

	SetRect(&rc, 0, 0, MaxHp, rcBottom);
	rcSize = rcRight / MaxHp;
	m_pStatusHealthBar->SetRectFrameSize(rc);
	m_pStatusHealthBar->setScale(D3DXVECTOR3(rcSize, 1.1f, 0));

	cMainUI::setup();
}

void cStatus::setInventoryInfo()
{
	float x = 600; float y = 600;
	float xdistance = 40; float ydistance = 40;

	for (int i = 0; i < 2; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			m_vecInvenPos.push_back(D3DXVECTOR3(x + xdistance * j, y + ydistance * i, 0));
		}
	}
	D3DXVECTOR3 vtemp = m_vecInvenPos.back();
	m_vecInvenPos.push_back(D3DXVECTOR3(vtemp.x + 37, vtemp.y - 20, 0));
	for (int i = 0; i < m_vecInvenPos.size(); i++)
	{
		m_pInvenInfo = new cInventory;
		citem* itemInfo = new citem;
		m_pInvenInfo->SetinvitemInfo(itemInfo);
		m_pInvenInfo->SethadItem(false);
		m_pInvenInfo->SetvInvenPos(m_vecInvenPos[i]);
		m_pStatusInvenInfo.push_back(*m_pInvenInfo);
	}
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

	HitProgress();

	if (g_pKeyManager->IsOnceKeyDown('V'))
	{
		m_bIsHit = true;
		m_bCheckBar = true;
	}
	if (m_pStatusHealthBar)
	{
		m_pStatusHealthBar->update(0);



		if (m_pStatusHealthBar->GetrectFrameSize()->left <= m_pStatusHealthBar->GetrectFrameSize()->right &&
			m_bIsHit)
		{
			m_pStatusHealthBar->GetrectFrameSize()->right -= hit;
			m_bIsHit = false;
		}
	}
	for (int i = 0; i < m_pStatusSkillInfo.size(); i++)
	{
		m_pStatusSkillInfo[i]->update();
	}

	if (m_pShopButton->GetButttonState() == 2)
	{
		m_pShopOpend = true;
	}

	if (m_pShopOpend)
		m_pNodeName = "SHOP";

	if (g_pKeyManager->IsOnceKeyDown(VK_ESCAPE))m_pShopOpend = false;


	if (m_pStatusMpBar)
	{
		m_pStatusMpBar->update(0);
	}



	m_mapiter = m_mapChild.find("SHOP");
	if (m_mapiter != m_mapChild.end())
	{
		m_pStatusGold.amount = m_mapiter->second->GetGold().amount;
		m_pStatusGold.count = m_mapiter->second->GetGold().count;
		m_pStatusGold.goldIncreaseTime = m_mapiter->second->GetGold().goldIncreaseTime;


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

	m_pStatusGold.Gold_units->setPosition(D3DXVECTOR3(m_pStatusScreen->GetPosition().x + 695, m_pStatusScreen->GetPosition().y + 136, 0));
	m_pStatusGold.Gold_tens->setPosition(D3DXVECTOR3(m_pStatusScreen->GetPosition().x + 680, m_pStatusScreen->GetPosition().y + 136, 0));
	m_pStatusGold.Gold_huans->setPosition(D3DXVECTOR3(m_pStatusScreen->GetPosition().x + 665, m_pStatusScreen->GetPosition().y + 136, 0));
	m_pStatusGold.Gold_thous->setPosition(D3DXVECTOR3(m_pStatusScreen->GetPosition().x + 650, m_pStatusScreen->GetPosition().y + 136, 0));

	if (m_pShopButton)
		m_pShopButton->update();


	for (int i = 0; i < m_pStatusSkillInfo.size(); i++)
	{
		if (isClickedSkill(m_pRect, i))
		{
			switch (i) //qwer순
			{
			case 0:
				m_pStatusSkillInfo[i]->SetChosen(true); // 발쓰아
				break;
			case 1:
				m_pStatusSkillInfo[i]->SetChosen(true);
				break;
			case 2:
				m_pStatusSkillInfo[i]->SetChosen(true);
				break;
			case 3:
				m_pStatusSkillInfo[i]->SetChosen(true);
				break;
			}
		}
	}
	if (g_pKeyManager->IsOnceKeyDown('Q'))
	{
		m_pStatusSkillInfo[0]->SetChosen(true);
	}
	if (g_pKeyManager->IsOnceKeyDown('W'))
	{
		m_pStatusSkillInfo[1]->SetChosen(true);
	}
	if (g_pKeyManager->IsOnceKeyDown('E'))
	{
		m_pStatusSkillInfo[2]->SetChosen(true);
	}
	if (g_pKeyManager->IsOnceKeyDown('R'))
	{
		m_pStatusSkillInfo[3]->SetChosen(true);
	}


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




	for (int i = 0; i < m_pStatusSkillInfo.size(); i++)
	{
		m_pStatusSkillInfo[i]->render();
	}

	if (m_pShopButton)
		m_pShopButton->Render();

	if (m_pStatusGold.amount != 0)
		m_pStatusGold.Gold_units->aniRender();
	if (m_pStatusGold.amount > 10)
		m_pStatusGold.Gold_tens->aniRender();
	if (m_pStatusGold.amount >= 100)
		m_pStatusGold.Gold_huans->aniRender();
	if (m_pStatusGold.amount >= 1000)
		m_pStatusGold.Gold_thous->aniRender();


	cMainUI::render();
	//g_pFontManager->TextFont(10, 200 + 20, "와썹");
}

void cStatus::HitProgress()
{
	CurrentHp = MaxHp - hit;
	if (m_bCheckBar)
	{
		rcRight = m_pStatusHealthBar->GetrectFrameSize()->right;
		rcBottom = m_pStatusHealthBar->GetrectFrameSize()->bottom;
		m_bCheckBar = false;
	}

	//SetRect(&rc, 0, 0, CurrentHp, rcBottom);
	//rcSize = rcRight / MaxHp;
	//m_pStatusHealthBar->SetRectFrameSize(rc);
	//m_pStatusHealthBar->setScale(D3DXVECTOR3(rcSize, 1.1f, 0));
}
void cStatus::InvenUpdate()
{
	for (int i = 0; i < m_pStatusInvenInfo.size(); i++)
	{
		if (m_vecInven.size() == 0) continue;

		if (m_vecInven[i]->GetinvitemInfo()->GetItemInfo() != NULL)
		{
			m_pStatusInvenInfo[i].SetinvitemInfo(m_vecInven[i]->GetinvitemInfo());

			m_pStatusInvenInfo[i].GetinvitemInfo()->GetItemInfo()->Itemtexture->setPosition(m_pStatusInvenInfo[i].GetvInvenPos());
		}
	}
}
void cStatus::InvenRender()
{
	for (int i = 0; i < m_pStatusInvenInfo.size(); i++)
	{
		if (m_pStatusInvenInfo[i].GetinvitemInfo()->GetItemInfo() != NULL)
			m_pStatusInvenInfo[i].render();
	}
}

bool cStatus::isClickedSkill(OUT RECT* Outrc, int index)
{
	POINT pt;
	GetCursorPos(&pt);
	ScreenToClient(g_hWnd, &pt);

	int nSize = m_pStatusSkillInfo.size();

	RECT* rc = new RECT[nSize];
	D3DXMATRIX* matWorld = new D3DXMATRIX[nSize];
	ST_UI_SIZE* stSize = new ST_UI_SIZE[nSize];

	for (int i = 0; i < m_pStatusSkillInfo.size(); i++)
	{
		matWorld[index] = m_pStatusSkillInfo[index]->GetskillInfo()->GetWolrdMatrix();
		stSize[index] = m_pStatusSkillInfo[index]->GetskillInfo()->GetUiSize();
		SetRect(&rc[index],
			(int)matWorld[index]._41,
			(int)matWorld[index]._42,
			(int)matWorld[index]._41 + (stSize[index].nWidth * 0.7f),
			(int)matWorld[index]._42 + (stSize[index].nHeight * 0.7f));

		Outrc[index] = rc[index];

		SetRect(&Outrc[index],
			(int)matWorld[index]._41,
			(int)matWorld[index]._42,
			(int)matWorld[index]._41 + (stSize[index].nWidth * 0.7f),
			(int)matWorld[index]._42 + (stSize[index].nHeight * 0.7f));

		if (PtInRect(&rc[index], pt))
		{
			if (g_pKeyManager->IsOnceKeyDown(VK_LBUTTON))
			{
				return true;
			}
		}
	}
	return false;
}
void cStatus::GoldUpdate()
{

}
void cStatus::GoldRender()
{

}