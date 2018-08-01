#include "stdafx.h"
#include "cStatus.h"
#include "Bitmap.h"
#include "cUIButton.h"
#include "cInventory.h"
#include "cUiSkill.h"
#include "cstat.h"
#include "cPlayer.h"
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

	UsedMp = 0;
	m_bUsedSkill = false;
	m_bSelected = false;
	m_bIsHit = false;
	m_bIsUsed = false;
	m_bCheckHpBar = false;
	m_bCheckMpBar = false;
	m_pShopOpend = false;
	m_pPlayerInfo = new tagPlayerInfo;

	m_pStatInfo = new tagStatInfo;

	m_pStatusScreen = new Bitmap;
	m_pStatusScreen = g_pTextureManager->addTexture("StatusScreen", "./status/statusScreen.dds", UI, NULL);
	m_pStatusScreen->setPosition(D3DXVECTOR3(400, 640, 0));
	m_pStatusScreen->setScale(D3DXVECTOR3(0.8f, 0.8f, 0));

	m_pShopButton = new cUIButton;
	m_pShopButton->setTexture("shopButtonUP", "shopButtonOver", "shopButtonDown");
	m_pShopButton->setPosition(D3DXVECTOR3(845, m_pStatusScreen->GetPosition().y + 100, 0));
	m_pShopButton->setScale(D3DXVECTOR3(0.8f, 0.8f, 0));

	m_pStatusHealthBar = new Bitmap;
	m_pStatusHealthBar = g_pTextureManager->addTexture("HealthBar", "./status/hpBar.dds", PROGRESSBAR, 1, 1);
	m_pStatusHealthBar->setPosition(D3DXVECTOR3(441, m_pStatusScreen->GetPosition().y + 90, 0));
	m_pStatusHealthBar->setScale(D3DXVECTOR3(0.6f, 1.1f, 0));

	m_pStatusMpBar = new Bitmap;
	m_pStatusMpBar = g_pTextureManager->addTexture("MpBar", "./status/MpBar.dds", PROGRESSBAR, 1, 1);
	m_pStatusMpBar->setPosition(D3DXVECTOR3(441, m_pStatusScreen->GetPosition().y + 110, 0));
	m_pStatusMpBar->setScale(D3DXVECTOR3(1.018f, 1.1f, 0));

	m_pCharacterBar = new Bitmap;
	m_pCharacterBar = g_pTextureManager->addTexture("CharacterIcon", "./status/CharacterIcon.dds", UI, NULL);
	m_pCharacterBar->setPosition(D3DXVECTOR3(310, m_pStatusScreen->GetPosition().y + 10, 0));
	m_pCharacterBar->setScale(D3DXVECTOR3(0.8f, 0.8f, 0));

	m_pStatusInventory = new Bitmap;
	m_pStatusInventory = g_pTextureManager->addTexture("InventoryTexture", "./status/statusInventory.dds", UI, NULL);
	m_pStatusInventory->setPosition(D3DXVECTOR3(830, m_pStatusScreen->GetPosition().y, 0));
	m_pStatusInventory->setScale(D3DXVECTOR3(0.8f, 0.8f, 0));

	m_pCharacterIcon = new Bitmap;
	m_pCharacterIcon = g_pTextureManager->addTexture("CharacterIcon", "./status/Teemo_Circle_0.dds", UI, NULL);
	m_pCharacterIcon->setPosition(D3DXVECTOR3(m_pStatusScreen->GetPosition().x - 78, m_pStatusScreen->GetPosition().y + 21, 0));
	m_pCharacterIcon->setScale(D3DXVECTOR3(0.8f, 0.8f, 0));

	m_pStatusPlayerInfoIcon = new Bitmap;
	m_pStatusPlayerInfoIcon = g_pTextureManager->addTexture("PlayerInfoIcon", "./status/playerInfo.dds", UI, NULL);
	m_pStatusPlayerInfoIcon->setPosition(D3DXVECTOR3(m_pStatusScreen->GetPosition().x - 90, m_pStatusScreen->GetPosition().y + 85, 0));
	m_pStatusPlayerInfoIcon->setScale(D3DXVECTOR3(0.8f, 0.8f, 0));

	m_pBuffInfo = new Bitmap;
	m_pBuffInfo = g_pTextureManager->addTexture("BuffInfo", "./status/BuffInfo.dds", UI, NULL);
	m_pBuffInfo->setPosition(D3DXVECTOR3(m_pStatusScreen->GetPosition().x - 76, m_pStatusScreen->GetPosition().y + 95, 0));
	m_pBuffInfo->setScale(D3DXVECTOR3(0.8f, 0.8f, 0));



	m_pTeleport = new Bitmap;
	m_pTeleport = g_pTextureManager->addTexture("TeleportHome", "./status/TeleportHome.dds", UI, NULL);
	m_pTeleport->setPosition(D3DXVECTOR3(m_pStatusScreen->GetPosition().x + 565, m_pStatusScreen->GetPosition().y + 60, 0));
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
	m_pPlayerInfo->SkillInfo.Skill_Passive = g_pTextureManager->addTexture("Teemo_P", "./status/Teemo_P.dds", UI, NULL);

	m_pPlayerInfo->SkillInfo.Skill_Q->setPosition(D3DXVECTOR3(m_pStatusScreen->GetPosition().x + 86, m_pStatusScreen->GetPosition().y + 20, 0));
	m_pPlayerInfo->SkillInfo.Skill_W->setPosition(D3DXVECTOR3(m_pStatusScreen->GetPosition().x + 145, m_pStatusScreen->GetPosition().y + 20, 0));
	m_pPlayerInfo->SkillInfo.Skill_E->setPosition(D3DXVECTOR3(m_pStatusScreen->GetPosition().x + 205, m_pStatusScreen->GetPosition().y + 20, 0));
	m_pPlayerInfo->SkillInfo.Skill_R->setPosition(D3DXVECTOR3(m_pStatusScreen->GetPosition().x + 265, m_pStatusScreen->GetPosition().y + 20, 0));
	m_pPlayerInfo->SkillInfo.Skill_Passive->setPosition(D3DXVECTOR3(m_pStatusScreen->GetPosition().x + 110, m_pStatusScreen->GetPosition().y - 35, 0));


	m_pPlayerInfo->SkillInfo.Skill_Q->setScale(D3DXVECTOR3(0.8f, 0.8f, 0));
	m_pPlayerInfo->SkillInfo.Skill_W->setScale(D3DXVECTOR3(0.8f, 0.8f, 0));
	m_pPlayerInfo->SkillInfo.Skill_E->setScale(D3DXVECTOR3(0.8f, 0.8f, 0));
	m_pPlayerInfo->SkillInfo.Skill_R->setScale(D3DXVECTOR3(0.8f, 0.8f, 0));
	m_pPlayerInfo->SkillInfo.Skill_Passive->setScale(D3DXVECTOR3(0.55f, 0.55f, 0));



	m_pStatInfo->Screen->setPosition(D3DXVECTOR3(m_pStatusScreen->GetPosition().x - 230, m_pStatusScreen->GetPosition().y + 20, 0));
	m_pStatInfo->Screen->setScale(D3DXVECTOR3(1.2f, 0.7f, 0));

	m_pStatInfo->MoveSpeed->setPosition(D3DXVECTOR3(m_pStatInfo->Screen->GetPosition().x + 10, m_pStatInfo->Screen->GetPosition().y + 10, 0));
	m_pStatInfo->Defense->setPosition(D3DXVECTOR3(m_pStatInfo->Screen->GetPosition().x + 80, m_pStatInfo->Screen->GetPosition().y + 10, 0));
	m_pStatInfo->AttackSpeed->setPosition(D3DXVECTOR3(m_pStatInfo->Screen->GetPosition().x + 10, m_pStatInfo->Screen->GetPosition().y + 60, 0));
	m_pStatInfo->Atk->setPosition(D3DXVECTOR3(m_pStatInfo->Screen->GetPosition().x + 80, m_pStatInfo->Screen->GetPosition().y + 60, 0));

	m_pStatInfo->MoveSpeed->setScale(D3DXVECTOR3(0.8f, 0.8f, 0));
	m_pStatInfo->Defense->setScale(D3DXVECTOR3(0.8f, 0.8f, 0));
	m_pStatInfo->AttackSpeed->setScale(D3DXVECTOR3(0.8f, 0.8f, 0));
	m_pStatInfo->Atk->setScale(D3DXVECTOR3(0.8f, 0.8f, 0));


	m_pStatInfo->StatNum->MoveSpeedNum_unit->setPosition(D3DXVECTOR3(m_pStatInfo->MoveSpeed->GetPosition().x + 48, m_pStatInfo->MoveSpeed->GetPosition().y + 3, 0));
	m_pStatInfo->StatNum->MoveSpeedNum_ten->setPosition(D3DXVECTOR3(m_pStatInfo->MoveSpeed->GetPosition().x + 38, m_pStatInfo->MoveSpeed->GetPosition().y + 3, 0));
	m_pStatInfo->StatNum->MoveSpeedNum_huand->setPosition(D3DXVECTOR3(m_pStatInfo->MoveSpeed->GetPosition().x + 28, m_pStatInfo->MoveSpeed->GetPosition().y + 3, 0));

	m_pStatInfo->StatNum->DefenseNum_unit->setPosition(D3DXVECTOR3(m_pStatInfo->Defense->GetPosition().x + 48, m_pStatInfo->Defense->GetPosition().y + 3, 0));
	m_pStatInfo->StatNum->DefenseNum_ten->setPosition(D3DXVECTOR3(m_pStatInfo->Defense->GetPosition().x + 38, m_pStatInfo->Defense->GetPosition().y + 3, 0));
	m_pStatInfo->StatNum->DefenseNum_huand->setPosition(D3DXVECTOR3(m_pStatInfo->Defense->GetPosition().x + 28, m_pStatInfo->Defense->GetPosition().y + 3, 0));

	m_pStatInfo->StatNum->AttackSpeedNum_unit->setPosition(D3DXVECTOR3(m_pStatInfo->AttackSpeed->GetPosition().x + 48, m_pStatInfo->AttackSpeed->GetPosition().y + 3, 0));
	m_pStatInfo->StatNum->AttackSpeedNum_ten->setPosition(D3DXVECTOR3(m_pStatInfo->AttackSpeed->GetPosition().x + 38, m_pStatInfo->AttackSpeed->GetPosition().y + 3, 0));
	m_pStatInfo->StatNum->AttackSpeedNum_huand->setPosition(D3DXVECTOR3(m_pStatInfo->AttackSpeed->GetPosition().x + 28, m_pStatInfo->AttackSpeed->GetPosition().y + 3, 0));

	m_pStatInfo->StatNum->AtkNum_unit->setPosition(D3DXVECTOR3(m_pStatInfo->Atk->GetPosition().x + 48, m_pStatInfo->Atk->GetPosition().y + 3, 0));
	m_pStatInfo->StatNum->AtkNum_ten->setPosition(D3DXVECTOR3(m_pStatInfo->Atk->GetPosition().x + 38, m_pStatInfo->Atk->GetPosition().y + 3, 0));
	m_pStatInfo->StatNum->AtkNum_huand->setPosition(D3DXVECTOR3(m_pStatInfo->Atk->GetPosition().x + 28, m_pStatInfo->Atk->GetPosition().y + 3, 0));


	AttackSpeedValue = 100;
	AtkValue = 120;
	DefenseValue = 10;
	MoveSpeedValue = 50;

	m_pStatusSkillInfo.reserve(10);


	std::vector<std::string> vecSkillName;
	vecSkillName.push_back("q");
	vecSkillName.push_back("w");
	vecSkillName.push_back("e");
	vecSkillName.push_back("r");
	vecSkillName.push_back("p");

	m_pSkillInfo = new cUiSkill;
	m_pSkillInfo->SetChosen(false);
	m_pSkillInfo->SetskillInfo(m_pPlayerInfo->SkillInfo.Skill_Q);
	m_pSkillInfo->SetvSkillPos(m_pPlayerInfo->SkillInfo.Skill_Q->GetPosition());
	m_pStatusSkillInfo.push_back(m_pSkillInfo);

	m_mapStatusSkillInfo.insert(std::make_pair(vecSkillName[0], m_pSkillInfo));

	m_pSkillInfo = new cUiSkill;
	m_pSkillInfo->SetChosen(false);
	m_pSkillInfo->SetskillInfo(m_pPlayerInfo->SkillInfo.Skill_W);
	m_pSkillInfo->SetvSkillPos(m_pPlayerInfo->SkillInfo.Skill_W->GetPosition());
	m_pStatusSkillInfo.push_back(m_pSkillInfo);

	m_mapStatusSkillInfo.insert(std::make_pair(vecSkillName[1], m_pSkillInfo));

	m_pSkillInfo = new cUiSkill;
	m_pSkillInfo->SetChosen(false);
	m_pSkillInfo->SetskillInfo(m_pPlayerInfo->SkillInfo.Skill_E);
	m_pSkillInfo->SetvSkillPos(m_pPlayerInfo->SkillInfo.Skill_E->GetPosition());
	m_pStatusSkillInfo.push_back(m_pSkillInfo);

	m_mapStatusSkillInfo.insert(std::make_pair(vecSkillName[2], m_pSkillInfo));

	m_pSkillInfo = new cUiSkill;
	m_pSkillInfo->SetChosen(false);
	m_pSkillInfo->SetskillInfo(m_pPlayerInfo->SkillInfo.Skill_R);
	m_pSkillInfo->SetvSkillPos(m_pPlayerInfo->SkillInfo.Skill_R->GetPosition());
	m_pStatusSkillInfo.push_back(m_pSkillInfo);

	m_mapStatusSkillInfo.insert(std::make_pair(vecSkillName[3], m_pSkillInfo));

	m_pSkillInfo = new cUiSkill;
	m_pSkillInfo->SetChosen(false);
	m_pSkillInfo->SetskillInfo(m_pPlayerInfo->SkillInfo.Skill_Passive);
	m_pSkillInfo->SetvSkillPos(m_pPlayerInfo->SkillInfo.Skill_Passive->GetPosition());
	m_pStatusSkillInfo.push_back(m_pSkillInfo);

	m_mapStatusSkillInfo.insert(std::make_pair(vecSkillName[4], m_pSkillInfo));


	setInventoryInfo();

	MaxHp = 1000;
	CurrentHp = MaxHp;
	m_pPlayerInfo->HealthInfo.Hp = MaxHp;
	hit = 30;

	HprcRight = m_pStatusHealthBar->GetrectFrameSize()->right;
	HprcBottom = m_pStatusHealthBar->GetrectFrameSize()->bottom;

	SetRect(&HpRc, 0, 0, MaxHp, HprcBottom);
	HprcSize = HprcRight / MaxHp * 0.81f;
	m_pStatusHealthBar->SetRectFrameSize(HpRc);
	m_pStatusHealthBar->setScale(D3DXVECTOR3(HprcSize, 1.0f, 0));

	prevRectSize = HprcRight;
	//

	MaxMp = 500;
	CurrentMp = MaxMp;
	m_pPlayerInfo->HealthInfo.Mp = MaxMp;
	MpRcRight = m_pStatusMpBar->GetrectFrameSize()->right;
	MpRcBottom = m_pStatusMpBar->GetrectFrameSize()->bottom;

	SetRect(&MpRc, 0, 0, MaxMp, MpRcBottom);
	MpRcSize = MpRcRight / MaxMp * 0.81f;
	m_pStatusMpBar->SetRectFrameSize(MpRc);
	m_pStatusMpBar->setScale(D3DXVECTOR3(MpRcSize, 1.0f, 0));

	t = new D3DXVECTOR3[m_pStatusInvenInfo.size()];
	s = new D3DXVECTOR3[m_pStatusInvenInfo.size()];
	WorldMatrix = new D3DXMATRIX[m_pStatusInvenInfo.size()];
	matT = new D3DXMATRIX[m_pStatusInvenInfo.size()];
	matS = new D3DXMATRIX[m_pStatusInvenInfo.size()];

	cMainUI::setup();
}

void cStatus::setInventoryInfo()
{
	float x = 844; float y = 660;
	float xdistance = 42; float ydistance = 42;

	for (int i = 0; i < 2; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			m_vecInvenPos.push_back(D3DXVECTOR3(x + xdistance * j, y + ydistance * i, 0));
		}
	}
	D3DXVECTOR3 vtemp = m_vecInvenPos.back();
	m_vecInvenPos.push_back(D3DXVECTOR3(vtemp.x + 54, vtemp.y - 45, 0));
	for (int i = 0; i < m_vecInvenPos.size(); i++)
	{
		m_pInvenInfo = new cInventory;
		citem* itemInfo = new citem;
		m_pInvenInfo->SetinvitemInfo(itemInfo);
		m_pInvenInfo->SethadItem(false);
		m_pInvenInfo->SetvInvenPos(m_vecInvenPos[i]);
		m_pStatusInvenInfo.push_back(m_pInvenInfo);
	}
}
void cStatus::update()
{
	m_pStatInfo->StatNum->MoveSpeedNum_unit->update(0);
	m_pStatInfo->StatNum->MoveSpeedNum_ten->update(0);
	m_pStatInfo->StatNum->MoveSpeedNum_huand->update(0);

	m_pStatInfo->StatNum->MoveSpeedNum_unit->setCurrentFrame((MoveSpeedValue % 10) / 1);
	m_pStatInfo->StatNum->MoveSpeedNum_ten->setCurrentFrame((MoveSpeedValue % 100) / 10);
	m_pStatInfo->StatNum->MoveSpeedNum_huand->setCurrentFrame((MoveSpeedValue % 1000) / 100);

	m_pStatInfo->StatNum->DefenseNum_unit->update(0);
	m_pStatInfo->StatNum->DefenseNum_ten->update(0);
	m_pStatInfo->StatNum->DefenseNum_huand->update(0);

	m_pStatInfo->StatNum->DefenseNum_unit->setCurrentFrame((DefenseValue % 10) / 1);
	m_pStatInfo->StatNum->DefenseNum_ten->setCurrentFrame((DefenseValue % 100) / 10);
	m_pStatInfo->StatNum->DefenseNum_huand->setCurrentFrame((DefenseValue % 1000) / 100);

	m_pStatInfo->StatNum->AttackSpeedNum_unit->update(0);
	m_pStatInfo->StatNum->AttackSpeedNum_ten->update(0);
	m_pStatInfo->StatNum->AttackSpeedNum_huand->update(0);

	m_pStatInfo->StatNum->AttackSpeedNum_unit->setCurrentFrame((AttackSpeedValue % 10) / 1);
	m_pStatInfo->StatNum->AttackSpeedNum_ten->setCurrentFrame((AttackSpeedValue % 100) / 10);
	m_pStatInfo->StatNum->AttackSpeedNum_huand->setCurrentFrame((AttackSpeedValue % 1000) / 100);

	m_pStatInfo->StatNum->AtkNum_unit->update(0);
	m_pStatInfo->StatNum->AtkNum_ten->update(0);
	m_pStatInfo->StatNum->AtkNum_huand->update(0);

	m_pStatInfo->StatNum->AtkNum_unit->setCurrentFrame((AtkValue % 10) / 1);
	m_pStatInfo->StatNum->AtkNum_ten->setCurrentFrame((AtkValue % 100) / 10);
	m_pStatInfo->StatNum->AtkNum_huand->setCurrentFrame((AtkValue % 1000) / 100);


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

	for (auto p : m_pStatusInvenInfo)
	{
		if (p->GetinvitemInfo()->GetItemInfo() != NULL)
		{
			p->GetinvitemInfo()->GetItemInfo()->Itemtexture->update();
		}
	}

	for (int i = 0; i < m_pStatusInvenInfo.size(); i++)
	{
		if (m_pStatusInvenInfo[i]->GetinvitemInfo()->GetItemInfo() != NULL)
		{
			if (m_pStatusInvenInfo[i]->GetinvitemInfo()->GetItemInfo()->ReGainHp != NULL &&
				m_pStatusInvenInfo[i]->GetinvitemInfo()->GetItemInfo()->GetEffected() == false)
			{
				m_pPlayer->SetRegainHP(m_pStatusInvenInfo[i]->GetinvitemInfo()->GetItemInfo()->ReGainHp);
			}

			if (m_pStatusInvenInfo[i]->GetinvitemInfo()->GetItemInfo()->Mp != NULL &&
				m_pStatusInvenInfo[i]->GetinvitemInfo()->GetItemInfo()->GetEffected() == false)
			{
				MaxMp += m_pStatusInvenInfo[i]->GetinvitemInfo()->GetItemInfo()->Mp;
				CurrentMp = MaxMp;
				reSizeProgressBar();
				m_pHealthProgress->SetReCorret(true);
				m_pPlayer->SetMP(MaxMp);
			}

			if (m_pStatusInvenInfo[i]->GetinvitemInfo()->GetItemInfo()->Hp != NULL &&
				m_pStatusInvenInfo[i]->GetinvitemInfo()->GetItemInfo()->GetEffected() == false)
			{
				MaxHp += m_pStatusInvenInfo[i]->GetinvitemInfo()->GetItemInfo()->Hp;
				CurrentHp = MaxHp;
				m_pStatusInvenInfo[i]->GetinvitemInfo()->GetItemInfo()->SetEffected(true);
				reSizeProgressBar();
				m_pHealthProgress->SetReCorret(true);

				m_pPlayer->SetMAXHP(MaxHp);
				m_pPlayer->SetHP(CurrentHp);
				if (m_pStatusInvenInfo[i]->GetinvitemInfo()->GetItemInfo()->Mp != NULL)
				{
					MaxMp += m_pStatusInvenInfo[i]->GetinvitemInfo()->GetItemInfo()->Mp;
					CurrentMp = MaxMp;
					reSizeProgressBar();
					m_pHealthProgress->SetReCorret(true);

					m_pPlayer->SetMP(MaxMp);
				}
				if (m_pStatusInvenInfo[i]->GetinvitemInfo()->GetItemInfo()->Attack != NULL)
				{
					AtkValue += m_pStatusInvenInfo[i]->GetinvitemInfo()->GetItemInfo()->Attack;

					m_pPlayer->SetATK(AtkValue);
					g_pSkillManager->GetSkill("평타")->SetDamage(AtkValue);
				}
				if (m_pStatusInvenInfo[i]->GetinvitemInfo()->GetItemInfo()->AttackSpeed != NULL)
				{
					AttackSpeedValue += m_pStatusInvenInfo[i]->GetinvitemInfo()->GetItemInfo()->AttackSpeed;

					m_pPlayer->SetATKSpeed(AttackSpeedValue);
				}
				if (m_pStatusInvenInfo[i]->GetinvitemInfo()->GetItemInfo()->Defence != NULL)
				{
					DefenseValue += m_pStatusInvenInfo[i]->GetinvitemInfo()->GetItemInfo()->Defence;

					m_pPlayer->SetDEF(DefenseValue);
				}
			}
			if (m_pStatusInvenInfo[i]->GetinvitemInfo()->GetItemInfo()->Attack != NULL &&
				m_pStatusInvenInfo[i]->GetinvitemInfo()->GetItemInfo()->GetEffected() == false)
			{
				AtkValue += m_pStatusInvenInfo[i]->GetinvitemInfo()->GetItemInfo()->Attack;
				m_pStatusInvenInfo[i]->GetinvitemInfo()->GetItemInfo()->SetEffected(true);
				m_pPlayer->SetATK(AtkValue);
				g_pSkillManager->GetSkill("평타")->SetDamage(AtkValue);
			}
			if (m_pStatusInvenInfo[i]->GetinvitemInfo()->GetItemInfo()->AttackSpeed != NULL &&
				m_pStatusInvenInfo[i]->GetinvitemInfo()->GetItemInfo()->GetEffected() == false)
			{
				AttackSpeedValue += m_pStatusInvenInfo[i]->GetinvitemInfo()->GetItemInfo()->AttackSpeed;
				m_pStatusInvenInfo[i]->GetinvitemInfo()->GetItemInfo()->SetEffected(true);
				m_pPlayer->SetATK(AttackSpeedValue);
			}
			if (m_pStatusInvenInfo[i]->GetinvitemInfo()->GetItemInfo()->Defence != NULL &&
				m_pStatusInvenInfo[i]->GetinvitemInfo()->GetItemInfo()->GetEffected() == false)
			{
				DefenseValue += m_pStatusInvenInfo[i]->GetinvitemInfo()->GetItemInfo()->Defence;
				m_pStatusInvenInfo[i]->GetinvitemInfo()->GetItemInfo()->SetEffected(true);
				m_pPlayer->SetATK(DefenseValue);
			}

			if (tempItemInfo.GetItemInfo() != NULL)
			{

			}
		}
	}

	HitProgress();

	m_pStatusHealthBar->GetrectFrameSize()->right = m_pPlayer->GetHP();

	if (g_pKeyManager->IsOnceKeyDown('V')) // 맞았는가 확인 .
	{
		m_bIsHit = true;
		m_bCheckHpBar = true;
	}

	if (m_pStatusHealthBar)
	{
		m_pStatusHealthBar->update(0);

		if (m_pStatusHealthBar->GetrectFrameSize()->right <= 0) m_pStatusHealthBar->GetrectFrameSize()->right = 0;

		if (m_pStatusHealthBar->GetrectFrameSize()->left < m_pStatusHealthBar->GetrectFrameSize()->right &&
			m_bIsHit)
		{
			m_pStatusHealthBar->GetrectFrameSize()->right = m_pPlayer->GetHP();
			m_bIsHit = false;
		}
	}
	if (m_pStatusMpBar)
	{
		m_pStatusMpBar->update(0);

		if (m_pStatusMpBar->GetrectFrameSize()->right <= 0) m_pStatusMpBar->GetrectFrameSize()->right = 0;

		if (m_pStatusMpBar->GetrectFrameSize()->left < m_pStatusMpBar->GetrectFrameSize()->right &&
			m_bIsUsed)
		{
			m_pStatusMpBar->GetrectFrameSize()->right -= UsedMp;
			m_bIsUsed = false;
		}
	}
	/*for (int i = 0; i < m_pStatusSkillInfo.size(); i++)
	{
	m_pStatusSkillInfo[i]->update();
	}*/

	for (auto p : m_mapStatusSkillInfo)
	{
		p.second->update();
	}

	if (m_pShopButton->GetButttonState() == 2)
	{
		m_pShopOpend = true;
	}

	if (m_pShopOpend)
		m_pNodeName = "SHOP";

	if (g_pKeyManager->IsOnceKeyDown(VK_ESCAPE))m_pShopOpend = false;






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

	m_pStatusGold.Gold_units->setPosition(D3DXVECTOR3(m_pStatusInventory->GetPosition().x + 135, m_pStatusInventory->GetPosition().y + 105, 0));
	m_pStatusGold.Gold_tens->setPosition(D3DXVECTOR3(m_pStatusInventory->GetPosition().x + 115, m_pStatusInventory->GetPosition().y + 105, 0));
	m_pStatusGold.Gold_huans->setPosition(D3DXVECTOR3(m_pStatusInventory->GetPosition().x + 95, m_pStatusInventory->GetPosition().y + 105, 0));
	m_pStatusGold.Gold_thous->setPosition(D3DXVECTOR3(m_pStatusInventory->GetPosition().x + 75, m_pStatusInventory->GetPosition().y + 105, 0));

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

	if (recorrect)
	{
		SetRect(&HpRc, 0, 0, MaxHp, HprcBottom);
		m_pStatusHealthBar->SetRectFrameSize(HpRc);
		HprcRight = m_pStatusHealthBar->GetrectFrameSize()->right;
		HprcBottom = m_pStatusHealthBar->GetrectFrameSize()->bottom;

		HprcSize = (prevRectSize * 0.81f) / HprcRight;
		m_pStatusHealthBar->setScale(D3DXVECTOR3(HprcSize, 1.0f, 0));

		SetRect(&MpRc, 0, 0, MaxMp, MpRcBottom);
		m_pStatusMpBar->SetRectFrameSize(MpRc);
		MpRcRight = m_pStatusMpBar->GetrectFrameSize()->right;
		MpRcBottom = m_pStatusMpBar->GetrectFrameSize()->bottom;

		MpRcSize = (prevRectSize * 0.81f) / MpRcRight;
		m_pStatusMpBar->setScale(D3DXVECTOR3(MpRcSize, 1.0f, 0));

		recorrect = false;
	}

	if (g_pKeyManager->IsOnceKeyDown('Q'))
	{
		for (auto p : m_mapStatusSkillInfo)
		{
			if (p.first == "q")
			{
				p.second->SetChosen(true);
				p.second->GetskillInfo()->Setalphavalue(100);
				m_bSelected = true;
			}

		}
		g_pSkillManager->IsReady("q");
	}
	if (g_pKeyManager->IsOnceKeyDown('W'))
	{
		for (auto p : m_mapStatusSkillInfo)
		{
			if (CurrentMp < 30) continue;

			if (p.first == "w" && m_bSelected != true)
			{
				if (p.second->GetChosen() == true) continue;

				p.second->SetChosen(true);
				p.second->GetskillInfo()->Setalphavalue(100);

				m_bSelected = true;
				UsedMp = 30;
				g_pSkillManager->IsReady("w");
			}
		}
	}


	if (g_pKeyManager->IsOnceKeyDown('E'))
	{
		for (auto p : m_mapStatusSkillInfo)
		{
			if (CurrentMp < 20)continue;

			if (p.first == "e" && m_bSelected != true)
			{
				if (p.second->GetChosen() == true) continue;

				p.second->SetChosen(true);
				p.second->GetskillInfo()->Setalphavalue(100);
				m_bSelected = true;
				UsedMp = 20;
				g_pSkillManager->IsReady("e");
			}

		}
	}
	if (g_pKeyManager->IsOnceKeyDown('R'))
	{
		for (auto p : m_mapStatusSkillInfo)
		{
			if (CurrentMp < 50) continue;

			if (p.first == "r" && m_bSelected != true)
			{
				if (p.second->GetChosen() == true) continue;

				p.second->SetChosen(true);
				p.second->GetskillInfo()->Setalphavalue(100);

				m_bSelected = true;
				UsedMp = 50;
				g_pSkillManager->IsReady("r");
			}
		}
	}

	if (g_pSkillManager->GetSkill("e")->IsUsingSkill())
	{
		m_bIsUsed = true;
		m_bCheckMpBar = true;
		m_bUsedSkill = true;
		m_bSelected = false;

		for (auto p : m_mapStatusSkillInfo)
		{
			if (p.first == "e")p.second->SetUsing(true);
		}
	}
	if (g_pSkillManager->GetSkill("r")->IsUsingSkill())
	{
		m_bIsUsed = true;
		m_bCheckMpBar = true;
		m_bUsedSkill = true;
		m_bSelected = false;

		for (auto p : m_mapStatusSkillInfo)
		{
			if (p.first == "r")p.second->SetUsing(true);
		}
	}
	if (g_pSkillManager->GetSkill("w")->IsUsingSkill())
	{
		m_bIsUsed = true;
		m_bCheckMpBar = true;
		m_bUsedSkill = true;
		m_bSelected = false;

		for (auto p : m_mapStatusSkillInfo)
		{
			if (p.first == "w")p.second->SetUsing(true);
		}
	}

	if (CurrentHp <= 0)CurrentHp = 0;
	if (CurrentMp <= 0)CurrentMp = 0;

	isClickUi();

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

	m_pStatInfo->Screen->Render();
	m_pStatInfo->MoveSpeed->Render();
	m_pStatInfo->AttackSpeed->Render();
	m_pStatInfo->Atk->Render();
	m_pStatInfo->Defense->Render();


	if (MoveSpeedValue != 0)
		m_pStatInfo->StatNum->MoveSpeedNum_unit->aniRender();
	if (MoveSpeedValue >= 10)
		m_pStatInfo->StatNum->MoveSpeedNum_ten->aniRender();
	if (MoveSpeedValue >= 100)
		m_pStatInfo->StatNum->MoveSpeedNum_huand->aniRender();

	if (DefenseValue != 0)
		m_pStatInfo->StatNum->DefenseNum_unit->aniRender();
	if (DefenseValue >= 10)
		m_pStatInfo->StatNum->DefenseNum_ten->aniRender();
	if (DefenseValue >= 100)
		m_pStatInfo->StatNum->DefenseNum_huand->aniRender();

	if (AttackSpeedValue != 0)
		m_pStatInfo->StatNum->AttackSpeedNum_unit->aniRender();
	if (AttackSpeedValue >= 10)
		m_pStatInfo->StatNum->AttackSpeedNum_ten->aniRender();
	if (AttackSpeedValue >= 100)
		m_pStatInfo->StatNum->AttackSpeedNum_huand->aniRender();

	if (AtkValue != 0)
		m_pStatInfo->StatNum->AtkNum_unit->aniRender();
	if (AtkValue >= 10)
		m_pStatInfo->StatNum->AtkNum_ten->aniRender();
	if (AtkValue >= 100)
		m_pStatInfo->StatNum->AtkNum_huand->aniRender();

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


	for (auto p : m_mapStatusSkillInfo)
	{
		p.second->render();
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

	for (auto p : m_mapStatusSkillInfo)
	{
		if (p.second->GetChosen() == true && p.second->GetUsing() == true)
		{
			g_pFontManager->TextFont(p.second->GetskillInfo()->GetPosition().x + 18,
				p.second->GetskillInfo()->GetPosition().y + 15, D3DXVECTOR3(255, 0, 255), "%d",
				g_pSkillManager->GetSkill(p.first)->CooldownTimer());

			if (g_pSkillManager->GetSkill(p.first)->CooldownTimer() == 0)
			{
				p.second->SetChosen(false);
				p.second->GetskillInfo()->Setalphavalue(255);
				p.second->SetUsing(false);
			}
		}
	}

	g_pFontManager->TextFont(m_pStatusHealthBar->GetPosition().x + 200, m_pStatusHealthBar->GetPosition().y, D3DXVECTOR3(255, 255, 255), "%0.0f", m_pPlayer->GetMAXHP());
	g_pFontManager->TextFont(m_pStatusHealthBar->GetPosition().x + 180, m_pStatusHealthBar->GetPosition().y, D3DXVECTOR3(255, 255, 255), "/");
	g_pFontManager->TextFont(m_pStatusHealthBar->GetPosition().x + 120, m_pStatusHealthBar->GetPosition().y, D3DXVECTOR3(255, 255, 255), "%0.0f", m_pPlayer->GetHP());

	g_pFontManager->TextFont(m_pStatusMpBar->GetPosition().x + 200, m_pStatusMpBar->GetPosition().y, D3DXVECTOR3(255, 255, 255), "%d", MaxMp);
	g_pFontManager->TextFont(m_pStatusMpBar->GetPosition().x + 180, m_pStatusMpBar->GetPosition().y, D3DXVECTOR3(255, 255, 255), "/");
	g_pFontManager->TextFont(m_pStatusMpBar->GetPosition().x + 120, m_pStatusMpBar->GetPosition().y, D3DXVECTOR3(255, 255, 255), "%d", CurrentMp);
}

void cStatus::HitProgress()
{
	if (m_bCheckHpBar)
	{
		if (CurrentHp > 0)
			CurrentHp = CurrentHp - hit;

		HprcRight = m_pStatusHealthBar->GetrectFrameSize()->right;
		HprcBottom = m_pStatusHealthBar->GetrectFrameSize()->bottom;

		m_bCheckHpBar = false;
	}

	if (m_bCheckMpBar)
	{
		if (CurrentMp > 0)
			CurrentMp = CurrentMp - UsedMp;

		MpRcRight = m_pStatusMpBar->GetrectFrameSize()->right;
		MpRcBottom = m_pStatusMpBar->GetrectFrameSize()->bottom;
		m_bCheckMpBar = false;
	}
}
void cStatus::InvenUpdate()
{
	for (int i = 0; i < m_pStatusInvenInfo.size(); i++)
	{
		if (m_vecInven.size() == 0) continue;

		if (m_vecInven[i]->GetinvitemInfo()->GetItemInfo() != NULL)
		{
			m_pStatusInvenInfo = m_vecInven;


			t[i] = D3DXVECTOR3(m_vecInvenPos[i].x, m_vecInvenPos[i].y, 0);
			s[i] = D3DXVECTOR3(0.55f, 0.55f, 0.7f);

			D3DXMatrixScaling(&matS[i], s[i].x, s[i].y, s[i].z);
			D3DXMatrixTranslation(&matT[i], t[i].x,
				t[i].y,
				t[i].z);

			WorldMatrix[i] = matS[i] * matT[i];

			m_pStatusInvenInfo[i]->GetinvitemInfo()->GetItemInfo()->Itemtexture->setWorldMatrix(WorldMatrix[i]);
		}
	}
}
void cStatus::InvenRender()
{
	for (int i = 0; i < m_pStatusInvenInfo.size(); i++)
	{
		if (m_pStatusInvenInfo[i]->GetinvitemInfo()->GetItemInfo() != NULL)
		{
			m_pStatusInvenInfo[i]->GetinvitemInfo()->GetItemInfo()->Itemtexture->GetSprite()->Begin(D3DXSPRITE_ALPHABLEND | D3DXSPRITE_SORT_TEXTURE);

			m_pStatusInvenInfo[i]->GetinvitemInfo()->GetItemInfo()->Itemtexture->GetSprite()->SetTransform(&WorldMatrix[i]);

			m_pStatusInvenInfo[i]->GetinvitemInfo()->GetItemInfo()->Itemtexture->GetSprite()->Draw
			(
				m_pStatusInvenInfo[i]->GetinvitemInfo()->GetItemInfo()->Itemtexture->GetTexture(),
				&m_pStatusInvenInfo[i]->GetinvitemInfo()->GetItemInfo()->Itemtexture->GetRect(),
				&D3DXVECTOR3(0, 0, 0),
				&D3DXVECTOR3(0, 0, 0),
				D3DCOLOR_ARGB(255, 255, 255, 255));

			m_pStatusInvenInfo[i]->GetinvitemInfo()->GetItemInfo()->Itemtexture->GetSprite()->End();
		}
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

bool cStatus::isClickUi()
{
	POINT pt;
	GetCursorPos(&pt);
	ScreenToClient(g_hWnd, &pt);

	RECT* rc = new RECT;
	D3DXMATRIX* matWorld = new D3DXMATRIX;
	ST_UI_SIZE* stSize = new ST_UI_SIZE;

	matWorld = &m_pStatusScreen->GetWolrdMatrix();
	stSize = &m_pStatusScreen->GetUiSize();
	SetRect(rc,
		matWorld->_41,
		matWorld->_42,
		matWorld->_41 + (stSize->nWidth * 0.8f),
		matWorld->_42 + (stSize->nHeight * 0.8f));

	if (PtInRect(rc, pt))
	{
		return true;
	}
	return false;
}

void cStatus::reSizeProgressBar()
{
	SetRect(&HpRc, 0, 0, MaxHp, HprcBottom);
	m_pStatusHealthBar->SetRectFrameSize(HpRc);
	HprcRight = m_pStatusHealthBar->GetrectFrameSize()->right;
	HprcBottom = m_pStatusHealthBar->GetrectFrameSize()->bottom;

	HprcSize = (prevRectSize * 0.81f) / HprcRight;
	m_pStatusHealthBar->setScale(D3DXVECTOR3(HprcSize, 1.0f, 0));

	SetRect(&MpRc, 0, 0, MaxMp, MpRcBottom);
	m_pStatusMpBar->SetRectFrameSize(MpRc);
	MpRcRight = m_pStatusMpBar->GetrectFrameSize()->right;
	MpRcBottom = m_pStatusMpBar->GetrectFrameSize()->bottom;

	MpRcSize = (prevRectSize * 0.81f) / MpRcRight;
	m_pStatusMpBar->setScale(D3DXVECTOR3(MpRcSize, 1.0f, 0));
}
void cStatus::GoldUpdate()
{

}
void cStatus::GoldRender()
{

}