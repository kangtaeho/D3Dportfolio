#include "stdafx.h"
#include "cShop.h"
#include "cUIButton.h"
#include "citem.h"
#include "Bitmap.h"
#include "cInventory.h"
cShop::cShop()
	:m_pPurchaseB(NULL)
	, nRow(5)
	, m_vecItem(NULL)
	, m_vecSoldButton(NULL)
	, ItemPrice(0)
	, m_nDragIndex(-1)
{
}


cShop::~cShop()
{
	if (m_pPurchaseB)
		SAFE_DELETE(m_pPurchaseB);
	if (m_pInvenInfo)
		SAFE_DELETE(m_pInvenInfo);
	if (m_pItemInfo)
		SAFE_DELETE(m_pItemInfo);
	if (tempitem)
		SAFE_DELETE(tempitem);
	if (m_pPurchaseB)
		SAFE_DELETE(m_pPurchaseB);
	if (m_pSaleB)
		SAFE_DELETE(m_pSaleB);


	if (tempInvitem)
		SAFE_DELETE(tempInvitem);
	for (auto p : m_vecInventory)
		SAFE_DELETE(p);
	for (auto p : m_vecItem)
		SAFE_DELETE(p);
	for (auto p : m_vecSoldButton)
		SAFE_DELETE(p);


	SAFE_RELEASE(m_pSprite);

	//for (auto p : m_vecSeleted)
	//	SAFE_DELETE(p);

	if (m_pShop)
		SAFE_DELETE(m_pShop);

	if (m_pSelected)
		SAFE_DELETE(m_pSelected);

}

void cShop::setup()
{
	cMainUI::setup();


	m_pItemEx = new ex;

	m_pItemEx->LongSword->setPosition(D3DXVECTOR3(685, 360, 0));
	tempInvitem = new citem;

	m_pItemInfo = new citem;
	m_pRect = new RECT[10];
	m_pRectCraft = new RECT[100];
	m_pRectInv = new RECT[100];
	m_pPurchaseB = new cUIButton;
	m_pPurchaseB->setTexture("purchaseButton", "purchaseButtonOver", "purchaseButtonDown");

	m_pSaleB = new cUIButton;
	m_pSaleB->setTexture("saleButtonUp", "saleButtonOver", "saleButtonDown");

	m_pReturnB = new cUIButton;
	m_pReturnB->setTexture("returnButtonUp", "returnButtonOver", "returnButtonDown");
	m_pRecommandB = new cUIButton;
	m_pRecommandB->setTexture("recommandButtonUp", "recommandButtonOver", "recommandButtonDown");
	m_pWholeB = new cUIButton;
	m_pWholeB->setTexture("wholeButtonUp", "wholeButtonOver", "wholeButtonDown");

	tempLongSword = new citem; tempDagger = new citem;
	tempphage = new citem;  tempSheen = new citem;  tempRed_Orb = new citem;
	tempTrinity_Force = new citem;  tempsp = new citem;  tempBlue_Orb = new citem;

	m_pSelected = new Bitmap;
	m_pSelected = g_pTextureManager->addTexture("selecteButton", "./testFile/selected2.dds", BUTTON, NULL);
	m_pSelected->setPosition(D3DXVECTOR3(-100, 0, 0));
	m_pSelected->setScale(D3DXVECTOR3(0, 0, 0));
	//g_pTextureManager->addTexture("shop2", "./testFile/shop2.dds", UI, NULL);
	m_pShop = g_pTextureManager->addTexture("shops", "./testFile/shops.dds", UIANIMATION, 2.0f, 1.0f);
	m_pShop->setPosition(D3DXVECTOR3(140.0f, 0, 0));
	m_pShop->setScale(D3DXVECTOR3(0.7f, 0.7f, 0));
	shopState = RECOMMAND;

	m_pPurchaseB->setPosition(D3DXVECTOR3(m_pShop->GetPosition().x + 770, m_pShop->GetPosition().y + 380, 0));
	m_pPurchaseB->setScale(D3DXVECTOR3(0.75f, 0.75f, 0));
	m_pReturnB->setPosition(D3DXVECTOR3(m_pShop->GetPosition().x + 280, m_pShop->GetPosition().y + 627, 0));
	m_pReturnB->setScale(D3DXVECTOR3(0.7f, 0.7f, 0));
	m_pSaleB->setPosition(D3DXVECTOR3(m_pShop->GetPosition().x + 210, m_pShop->GetPosition().y + 627, 0));
	m_pSaleB->setScale(D3DXVECTOR3(0.7f, 0.7f, 0));

	m_pRecommandB->setPosition(D3DXVECTOR3(m_pShop->GetPosition().x + 10, m_pShop->GetPosition().y + 20, 0));
	m_pRecommandB->setScale(D3DXVECTOR3(0.75f, 0.75f, 0));

	m_pWholeB->setPosition(D3DXVECTOR3(m_pShop->GetPosition().x + 190, m_pShop->GetPosition().y + 20, 0));
	m_pWholeB->setScale(D3DXVECTOR3(0.75f, 0.75f, 0));

	setInventoryInfo();
	
	ItemSetting();
	setItemPosition();
	setWholeItemPosition();
	setGoldPosition();
	setBluePrintPos();
	sortItemInfo();

	m_pGold.Gold_units = new Bitmap;
	m_pGold.Gold_tens = new Bitmap;
	m_pGold.Gold_huans = new Bitmap;
	m_pGold.Gold_thous = new Bitmap;

	m_pGold.Gold_units = g_pTextureManager->addTexture("Gold_units", "./item/GoldNum.dds", ANIMATION, 10.0f, 1.0f);
	m_pGold.Gold_tens =  g_pTextureManager->addTexture("Gold_tens", "./item/GoldNum.dds", ANIMATION, 10.0f, 1.0f);
	m_pGold.Gold_huans = g_pTextureManager->addTexture("Gold_huans", "./item/GoldNum.dds", ANIMATION, 10.0f, 1.0f);
	m_pGold.Gold_thous = g_pTextureManager->addTexture("Gold_thous", "./item/GoldNum.dds", ANIMATION, 10.0f, 1.0f);


	
}
void cShop::sortItemInfo()
{
	for (auto p : m_vecItem)
	{
		sortItem(p->GetItemInfo()->itemName, p->GetItemInfo()->itemState);

		p->GetItemInfo()->ItemPriceTexture_f->setPosition(D3DXVECTOR3(p->GetItemInfo()->Itemtexture->GetPosition().x,
			p->GetItemInfo()->Itemtexture->GetPosition().y + 40, 0));

		p->GetItemInfo()->ItemPriceTexture_f->setCurrentFrame(p->GetItemInfo()->price / 100);

		p->GetItemInfo()->ItemPriceTexture_s->setPosition(D3DXVECTOR3(p->GetItemInfo()->Itemtexture->GetPosition().x + 15,
			p->GetItemInfo()->Itemtexture->GetPosition().y + 40, 0));

		p->GetItemInfo()->ItemPriceTexture_s->setCurrentFrame((p->GetItemInfo()->price % 100) / 10);

		p->GetItemInfo()->ItemPriceTexture_t->setPosition(D3DXVECTOR3(p->GetItemInfo()->Itemtexture->GetPosition().x + 30,
			p->GetItemInfo()->Itemtexture->GetPosition().y + 40, 0));

		p->GetItemInfo()->ItemPriceTexture_t->setCurrentFrame(((p->GetItemInfo()->price % 10) / 1));
	}
}

void cShop::setInventoryInfo()
{
	float x = 165; float y = 583;
	float xdistance = 40; float ydistance = 40;

	for (int i = 0; i < 2; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			m_vecShopInven.push_back(D3DXVECTOR3(x + xdistance * j, y + ydistance * i, 0));
		}
	}
	D3DXVECTOR3 vtemp = m_vecShopInven.back();
	m_vecShopInven.push_back(D3DXVECTOR3(vtemp.x + 37, vtemp.y - 20, 0));
	for (int i = 0; i < m_vecShopInven.size(); i++)
	{
		m_pInvenInfo = new cInventory;
		citem* itemInfo = new citem;
		m_pInvenInfo->SetinvitemInfo(itemInfo);
		m_pInvenInfo->SethadItem(false);
		m_pInvenInfo->SetvInvenPos(m_vecShopInven[i]);
		m_vecInventory.push_back(m_pInvenInfo);
	}
}
void cShop::ItemSetting()
{
	citem* potion = new citem;
	potion->setup("potion", "./item/potion.dds", START_ITEM, CONSUME);
	potion->GetItemInfo()->price = 50;
	potion->GetItemInfo()->Itemtexture->setScale(D3DXVECTOR3(0.7f, 0.7f, 0));
	m_vecItem.push_back(potion);
	citem* shoes = new citem;
	shoes->setup("shoes", "./item/1001_Boots_of_Speed.dds", START_ITEM, EQUIPABLE);
	shoes->GetItemInfo()->price = 100;
	m_vecItem.push_back(shoes);

	citem* LongSword = new citem;
	LongSword->setup("LongSword", "./item/1036_Long_Sword.dds", EARLY_ITEM, EQUIPABLE);
	LongSword->GetItemInfo()->price = 300;
	m_vecItem.push_back(LongSword);

	citem* Dagger = new citem;
	Dagger->setup("Dagger", "./item/1042_Dagger.dds", EARLY_ITEM, EQUIPABLE);
	Dagger->GetItemInfo()->price = 300;
	m_vecItem.push_back(Dagger);

	citem* phage = new citem;
	phage->setup("phage", "./item/3044_Phage.dds", CORE_ITEM, EQUIPABLE);
	phage->GetItemInfo()->price = 500;
	m_vecItem.push_back(phage);

	citem* Sheen = new citem;
	Sheen->setup("Sheen", "./item/3057_Sheen.dds", CORE_ITEM, EQUIPABLE);
	Sheen->GetItemInfo()->price = 500;
	m_vecItem.push_back(Sheen);

	citem* Red_Orb = new citem;
	Red_Orb->setup("Red_Orb", "./item/3095_Orb_of_Valor.dds", BASIC_ITEM, EQUIPABLE);
	Red_Orb->GetItemInfo()->price = 200;
	m_vecItem.push_back(Red_Orb);

	citem* Trinity_Force = new citem;
	Trinity_Force->setup("Trinity_Force", "./item/3078_Trinity_Force.dds", CORE_ITEM, EQUIPABLE);
	Trinity_Force->GetItemInfo()->price = 999;
	m_vecItem.push_back(Trinity_Force);

	citem* Ward = new citem;
	Ward->setup("Ward", "./item/3350_GreaterYellowTrinket.dds", START_ITEM, ACCESSORY);
	Ward->GetItemInfo()->price = 50;
	m_vecItem.push_back(Ward);

	citem* sp = new citem;
	sp->setup("sp", "./item/3058_Sheen_and_Phage.dds", EARLY_ITEM, EQUIPABLE);
	sp->GetItemInfo()->price = 300;
	m_vecItem.push_back(sp);

	citem* Blue_Orb = new citem;
	Blue_Orb->setup("Blue_Orb", "./item/1027_Sapphire_Sphere.dds", START_ITEM, EQUIPABLE);
	Blue_Orb->GetItemInfo()->price = 200;
	m_vecItem.push_back(Blue_Orb);
}
void cShop::setBluePrintInfo(std::string strKey, int index)
{
	for (int i = 0; i < m_vecItem.size(); i++)
	{
		if (strcmp("LongSword", m_vecItem[i]->GetItemInfo()->itemName.c_str()) == 0)
		{
			tempLongSword = m_vecItem[i];
		}
		if (strcmp("Dagger", m_vecItem[i]->GetItemInfo()->itemName.c_str()) == 0)
		{
			tempDagger = m_vecItem[i];
		}
		if (strcmp("phage", m_vecItem[i]->GetItemInfo()->itemName.c_str()) == 0)
		{
			tempphage = m_vecItem[i];
		}
		if (strcmp("Sheen", m_vecItem[i]->GetItemInfo()->itemName.c_str()) == 0)
		{
			tempSheen = m_vecItem[i];
		}
		if (strcmp("Red_Orb", m_vecItem[i]->GetItemInfo()->itemName.c_str()) == 0)
		{
			tempRed_Orb = m_vecItem[i];
		}
		if (strcmp("Trinity_Force", m_vecItem[i]->GetItemInfo()->itemName.c_str()) == 0)
		{
			tempTrinity_Force = m_vecItem[i];
		}
		if (strcmp("sp", m_vecItem[i]->GetItemInfo()->itemName.c_str()) == 0)
		{
			tempsp = m_vecItem[i];
		}
		if (strcmp("Blue_Orb", m_vecItem[i]->GetItemInfo()->itemName.c_str()) == 0)
		{
			tempBlue_Orb = m_vecItem[i];
		}
	}
	m_vecItem.clear();
	ItemSetting();
	sortItemInfo();

	cBluePrint* Trinity_Force_bp = new cBluePrint;	cBluePrint* Sheen_Bp = new cBluePrint;
	cBluePrint* phage_Bp = new cBluePrint; cBluePrint* sp_Bp = new cBluePrint;
	sp_Bp = tempsp; phage_Bp = tempphage; Trinity_Force_bp = tempTrinity_Force;
	Sheen_Bp = tempSheen; cBluePrint* temp = new cBluePrint;

	sp_Bp->AddChild("Dagger", tempDagger);

	phage_Bp->AddChild("LongSword", tempLongSword);
	phage_Bp->AddChild("Red_Orb", tempRed_Orb);
	Sheen_Bp->AddChild("Blue_Orb", tempBlue_Orb);
	Trinity_Force_bp->AddChild("sp", tempsp);
	Trinity_Force_bp->AddChild("LongSword", tempLongSword);
	Trinity_Force_bp->AddChild("Dagger", tempDagger);
	Trinity_Force_bp->AddChild("Sheen", tempSheen);
	Trinity_Force_bp->AddChild("Blue_Orb", tempBlue_Orb);
	Trinity_Force_bp->AddChild("phage", tempphage);
	Trinity_Force_bp->AddChild("Red_Orb", tempRed_Orb);

	if (strcmp(strKey.c_str(), "Trinity_ForceBp") == 0)
	{
		m_vecPrintitem.clear();

		tempsp->GetItemInfo()->Itemtexture->setPosition(m_vecMtrlPos.front());
		tempDagger->GetItemInfo()->Itemtexture->setPosition(m_vecMtrlPos[1]);
		tempSheen->GetItemInfo()->Itemtexture->setPosition(m_vecMtrlPos[2]);
		tempBlue_Orb->GetItemInfo()->Itemtexture->setPosition(m_vecMtrlPos[3]);
		tempphage->GetItemInfo()->Itemtexture->setPosition(m_vecMtrlPos[4]);
		tempLongSword->GetItemInfo()->Itemtexture->setPosition(m_vecMtrlPos[5]);
		tempRed_Orb->GetItemInfo()->Itemtexture->setPosition(m_vecMtrlPos[6]);
		tempTrinity_Force->GetItemInfo()->Itemtexture->setPosition(m_vecMtrlPos.back());

		m_mapBluePrint.insert(std::make_pair("Trinity_ForceBp", Trinity_Force_bp));

		m_vecPrintitem.push_back(tempLongSword); m_vecPrintitem.push_back(tempDagger);
		m_vecPrintitem.push_back(tempphage); m_vecPrintitem.push_back(tempLongSword);
		m_vecPrintitem.push_back(tempRed_Orb); m_vecPrintitem.push_back(tempTrinity_Force);
		m_vecPrintitem.push_back(tempSheen);
		m_vecPrintitem.push_back(tempsp); m_vecPrintitem.push_back(tempBlue_Orb);
	}

	if (strcmp(strKey.c_str(), "SheenBp") == 0)
	{
		m_vecPrintitem.clear();
		temp = Trinity_Force_bp->findParent();
		tempTrinity_Force->GetItemInfo()->Itemtexture->setPosition(m_vecCraftPos.front());
		m_mapBluePrint.insert(std::make_pair("SheenBp", temp));

		tempSheen->GetItemInfo()->Itemtexture->setPosition(m_vecMtrlPos.back());
		tempBlue_Orb->GetItemInfo()->Itemtexture->setPosition(m_vecMtrlPos[2]);
		m_mapBluePrint.insert(std::make_pair("SheenBp", Sheen_Bp));


		m_vecPrintitem.push_back(tempTrinity_Force);
		m_vecPrintitem.push_back(tempSheen);
		m_vecPrintitem.push_back(tempBlue_Orb);

	}
	if (strcmp(strKey.c_str(), "phageBp") == 0)
	{
		m_vecPrintitem.clear();
		temp = Trinity_Force_bp->findParent();
		tempTrinity_Force->GetItemInfo()->Itemtexture->setPosition(m_vecCraftPos.front());
		m_mapBluePrint.insert(std::make_pair("phageBp", temp));

		tempphage->GetItemInfo()->Itemtexture->setPosition(m_vecMtrlPos.back());
		tempLongSword->GetItemInfo()->Itemtexture->setPosition(m_vecMtrlPos[0]);
		tempRed_Orb->GetItemInfo()->Itemtexture->setPosition(m_vecMtrlPos[4]);
		m_mapBluePrint.insert(std::make_pair("phageBp", phage_Bp));

		m_vecPrintitem.push_back(tempTrinity_Force);
		m_vecPrintitem.push_back(tempphage);
		m_vecPrintitem.push_back(tempRed_Orb);
		m_vecPrintitem.push_back(tempLongSword);
	}

	if (strcmp(strKey.c_str(), "spBp") == 0)
	{
		m_vecPrintitem.clear();
		temp = Trinity_Force_bp->findParent();
		tempTrinity_Force->GetItemInfo()->Itemtexture->setPosition(m_vecCraftPos.front());
		m_mapBluePrint.insert(std::make_pair("spBp", temp));

		tempsp->GetItemInfo()->Itemtexture->setPosition(m_vecMtrlPos.back());
		tempDagger->GetItemInfo()->Itemtexture->setPosition(m_vecMtrlPos[2]);

		m_mapBluePrint.insert(std::make_pair("spBp", sp_Bp));

		m_vecPrintitem.push_back(tempTrinity_Force);
		m_vecPrintitem.push_back(tempsp);
		m_vecPrintitem.push_back(tempDagger);
	}


	if (strcmp(strKey.c_str(), "LongSwordBp") == 0)
	{
		m_vecPrintitem.clear();
		temp = Trinity_Force_bp->findParent();
		tempTrinity_Force->GetItemInfo()->Itemtexture->setPosition(m_vecCraftPos.front());
		m_mapBluePrint.insert(std::make_pair("LongSwordBp", temp));

		temp = phage_Bp->findParent();
		tempphage->GetItemInfo()->Itemtexture->setPosition(m_vecCraftPos[1]);
		m_mapBluePrint.insert(std::make_pair("LongSwordBp", temp));

		m_vecPrintitem.push_back(tempTrinity_Force);
		m_vecPrintitem.push_back(tempphage);
	}

	if (strcmp(strKey.c_str(), "DaggerBp") == 0)
	{
		m_vecPrintitem.clear();
		temp = Trinity_Force_bp->findParent();
		tempTrinity_Force->GetItemInfo()->Itemtexture->setPosition(m_vecCraftPos.front());
		m_mapBluePrint.insert(std::make_pair("DaggerBp", temp));

		temp = sp_Bp->findParent();
		tempsp->GetItemInfo()->Itemtexture->setPosition(m_vecCraftPos[1]);
		m_mapBluePrint.insert(std::make_pair("DaggerBp", temp));

		m_vecPrintitem.push_back(tempTrinity_Force);
		m_vecPrintitem.push_back(tempsp);
	}
	if (strcmp(strKey.c_str(), "Blue_OrbBp") == 0)
	{
		m_vecPrintitem.clear();
		temp = Trinity_Force_bp->findParent();
		tempTrinity_Force->GetItemInfo()->Itemtexture->setPosition(m_vecCraftPos.front());
		m_mapBluePrint.insert(std::make_pair("Blue_OrbBp", temp));

		temp = Sheen_Bp->findParent();
		tempSheen->GetItemInfo()->Itemtexture->setPosition(m_vecCraftPos[1]);
		m_mapBluePrint.insert(std::make_pair("Blue_OrbBp", temp));

		m_vecPrintitem.push_back(tempTrinity_Force);
		m_vecPrintitem.push_back(tempSheen);
	}
	if (strcmp(strKey.c_str(), "Red_OrbBp") == 0)
	{
		m_vecPrintitem.clear();
		temp = Trinity_Force_bp->findParent();
		tempTrinity_Force->GetItemInfo()->Itemtexture->setPosition(m_vecCraftPos.front());
		m_mapBluePrint.insert(std::make_pair("Red_OrbBp", temp));

		temp = phage_Bp->findParent();
		tempphage->GetItemInfo()->Itemtexture->setPosition(m_vecCraftPos[1]);
		m_mapBluePrint.insert(std::make_pair("Red_OrbBp", temp));

		m_vecPrintitem.push_back(tempTrinity_Force);
		m_vecPrintitem.push_back(tempphage);
	}

	if (strcmp(strKey.c_str(), "WardBp") == 0)
	{
		m_vecPrintitem.clear();
	}

	if (strcmp(strKey.c_str(), "shoesBp") == 0)
	{
		m_vecPrintitem.clear();
	}
}
void cShop::update()
{
	
	if (m_pShop)
		m_pShop->update(0);

	if (m_pPurchaseB)
		m_pPurchaseB->update();

	if (m_pSaleB)
		m_pSaleB->update();

	if (m_pReturnB)
		m_pReturnB->update();

	if (m_pRecommandB)
		m_pRecommandB->update();

	if (m_pWholeB)
		m_pWholeB->update();

	if (m_pSelected)
		m_pSelected->update();

	for (int i = 0; i < m_vecItem.size(); i++)
	{
		if (isClick(m_pRect, i)) //여기서 인벤토리에 넣을 정보를 넘긴다.
		{
			ItemPrice = m_vecItem[i]->GetItemInfo()->price;

			checkButton = new Bitmap;
			checkButton = g_pTextureManager->addTexture("boughtButton", "./testFile/bought.dds", BUTTON, NULL);
			checkButton->setPosition(D3DXVECTOR3(m_pRect[i].right - 10.0f, m_pRect[i].top - 5.0f, 0));

			ClickedItem = m_vecItem[i]->GetItemInfo()->itemName.c_str();
			ClickedItem += "Bp";
			setBluePrintInfo(ClickedItem, i);
		}
	}

	for (int i = 0; i < m_vecInventory.size(); i++)
	{
		if (m_vecInventory[i]->GetinvitemInfo()->GetItemInfo() == NULL)continue;
		if (isClickInventory(m_pRectInv, i))
		{

		}
	}


	if (m_pSaleB->GetButttonState() == 2)
	{
		if (tempInvitem->GetItemInfo() != NULL)
			m_pGold.amount += tempInvitem->GetItemInfo()->price / 2;

		isSoldInvenitem();
	}

	if (m_pReturnB->GetButttonState() == 2)
	{
		returnItem();
	}



	if (m_pRecommandB->GetButttonState() == 2)
	{
		shopState = RECOMMAND;
		m_pShop->setCurrentFrame(shopState);

		m_vecItem.clear();
		ItemSetting();
		sortItemInfo();
		m_vecSoldButton.clear();

		m_mapBluePrint.clear();
	}
	if (m_pWholeB->GetButttonState() == 2)
	{
		shopState = WHOLEITEM;
		m_pShop->setCurrentFrame(shopState);


		m_mapBluePrint.clear();


		m_vecItem.clear();
		ItemSetting();
		sortItemInfo();
		m_vecSoldButton.clear();

	}

	if (m_pPurchaseB->GetButttonState() == 2)
	{
		m_pItemInfo = tempitem;
		std::string tempName;
		tempName = m_pItemInfo->GetItemInfo()->itemName;

		tempitem->GetItemInfo()->Itemtexture->GetPosition();
		for (int j = 0; j < m_vecItem.size(); j++)
		{
			if (tempName == m_vecItem[j]->GetItemInfo()->itemName)
			{
				m_pItemInfo = m_vecItem[j];
			}
			else continue;
		}
		m_vecItem.clear();
		ItemSetting();
		sortItemInfo();
		for (int i = 0; i < m_vecInventory.size(); i++)
		{
			if (m_vecInventory[i]->GethadItem() == false)
			{
				if (m_pItemInfo->GetItemInfo()->itemInfo == ACCESSORY)
				{
					if (i != 6)continue;
					m_pItemInfo->GetItemInfo()->Itemtexture->setPosition(m_vecInventory[i]->GetvInvenPos());
					m_vecInventory[i]->SetinvitemInfo(m_pItemInfo);
					m_vecInventory[i]->SethadItem(true);
					IsSold();

					bool checked = false;
					for (auto p : m_vecSoldButton)
					{
						if (p->GetPosition() == checkButton->GetPosition())
							checked = true;
					}
					if (!checked)
					{
						m_vecSoldButton.push_back(checkButton);
					}
				}
				else if (m_pItemInfo->GetItemInfo()->itemInfo == EQUIPABLE || m_pItemInfo->GetItemInfo()->itemInfo == CONSUME)
				{
					if (CraftItem())break;

					m_sItemName = m_pItemInfo->GetItemInfo()->itemName;

					if (i == 6)continue;

					m_pItemInfo->GetItemInfo()->Itemtexture->setPosition(m_vecInventory[i]->GetvInvenPos());
					m_vecInventory[i]->SetinvitemInfo(m_pItemInfo); //인벤토리에 넣었다.
					m_vecInventory[i]->SethadItem(true);
					IsSold();

					bool checked = false;
					for (auto p : m_vecSoldButton)
					{
						if (p->GetPosition() == checkButton->GetPosition())
							checked = true;
					}
					if (!checked)
					{
						m_vecSoldButton.push_back(checkButton);
					}
					break;
				}
			}
		}
	}
	for (int i = 0; i < m_vecPrintitem.size(); i++)
	{
		if (isClickCraft(m_pRectCraft, i))
		{
			for (int j = 0; j < m_vecItem.size(); j++)
			{
				if (m_vecItem[j]->GetItemInfo()->itemName == m_vecPrintitem[i]->GetItemInfo()->itemName)
				{
					checkButton = new Bitmap;
					checkButton = g_pTextureManager->addTexture("boughtButton", "./testFile/bought.dds", BUTTON, NULL);
					checkButton->setPosition(D3DXVECTOR3(m_pRect[j].right - 10.0f, m_pRect[j].top - 5.0f, 0));
				}

			}
			if (g_pKeyManager->IsDoubleKeyDown(VK_LBUTTON))
			{
				ClickedItem = m_vecPrintitem[i]->GetItemInfo()->itemName;
				ClickedItem += "Bp";
				setBluePrintInfo(ClickedItem, i);
			}
		}
	}

	for (auto p : m_vecSoldButton)
	{
		p->update();
	}
	
	for (int i = 0; i < m_vecInventory.size(); i++)
	{
		if (m_vecInventory[i]->GetinvitemInfo()->GetItemInfo() == NULL) continue;
		for (int j = 0; j < m_vecItem.size(); j++)
		{
			if (m_vecItem[j]->GetItemInfo() == NULL)continue;
			if (m_vecInventory[i]->GetinvitemInfo()->GetItemInfo()->itemName == "LongSword")
			{
				if (m_vecItem[j]->GetItemInfo()->itemName == "phage")
				{
					m_vecItem[j]->GetItemInfo()->price = 200;

					m_vecItem[j]->GetItemInfo()->ItemPriceTexture_f->setCurrentFrame(m_vecItem[j]->GetItemInfo()->price / 100);
					m_vecItem[j]->GetItemInfo()->ItemPriceTexture_s->setCurrentFrame((m_vecItem[j]->GetItemInfo()->price % 100) / 10);
					m_vecItem[j]->GetItemInfo()->ItemPriceTexture_t->setCurrentFrame(((m_vecItem[j]->GetItemInfo()->price % 10) / 1));
				}
			}
			//shoes->setup("shoes", "./item/1001_Boots_of_Speed.dds", START_ITEM, EQUIPABLE);
			//shoes->GetItemInfo()->price = 100;		
			//LongSword->setup("LongSword", "./item/1036_Long_Sword.dds", EARLY_ITEM, EQUIPABLE);
			//LongSword->GetItemInfo()->price = 300;
			//Dagger->setup("Dagger", "./item/1042_Dagger.dds", EARLY_ITEM, EQUIPABLE);
			//Dagger->GetItemInfo()->price = 300;
			//phage->setup("phage", "./item/3044_Phage.dds", CORE_ITEM, EQUIPABLE);
			//phage->GetItemInfo()->price = 500;
			//Sheen->setup("Sheen", "./item/3057_Sheen.dds", CORE_ITEM, EQUIPABLE);
			//Sheen->GetItemInfo()->price = 500;
			//Red_Orb->setup("Red_Orb", "./item/3095_Orb_of_Valor.dds", BASIC_ITEM, EQUIPABLE);
			//Red_Orb->GetItemInfo()->price = 200;
			//Trinity_Force->setup("Trinity_Force", "./item/3078_Trinity_Force.dds", CORE_ITEM, EQUIPABLE);
			//Trinity_Force->GetItemInfo()->price = 999;		
			//Ward->setup("Ward", "./item/3350_GreaterYellowTrinket.dds", START_ITEM, ACCESSORY);
			//Ward->GetItemInfo()->price = 50;		
			//sp->setup("sp", "./item/3058_Sheen_and_Phage.dds", EARLY_ITEM, EQUIPABLE);
			//sp->GetItemInfo()->price = 300;
			//Blue_Orb->setup("Blue_Orb", "./item/1027_Sapphire_Sphere.dds", START_ITEM, EQUIPABLE);
			//Blue_Orb->GetItemInfo()->price = 200;
		}
	}

	ItemDragDrop();

	
	if (ClickedItem == "potionBp")
	{
		m_pItemEx->potion->setPosition(D3DXVECTOR3(600, 600, 0));
	}
	/*
	for (int i = 0; i < m_vecPrintitem.size(); i++)
	{
		if (m_vecPrintitem.size() == 0)continue;

		if (m_vecPrintitem[i]->GetItemInfo() != NULL)
		{
			position[i] = D3DXVECTOR3(m_vecMtrlPos[i].x, m_vecMtrlPos[i].y, 0);

			D3DXMatrixTranslation(&matT[i], position[i].x,
				position[i].y, 0);

			m_matWorld[i] = matT[i];

			m_vecPrintitem[i]->GetItemInfo()->Itemtexture->setWorldMatrix(m_matWorld[i]);
		}
	}*/

	cMainUI::update();
}

bool cShop::returnItem()
{
	for (int i = m_vecInventory.size() - 1; i >=0; i--)
	{
		if (m_vecInventory[i]->GetinvitemInfo()->GetItemInfo() != NULL)
		{
			m_pGold.amount += m_vecInventory[i]->GetinvitemInfo()->GetItemInfo()->price;

			m_vecInventory[i]->GetinvitemInfo()->SetItemInfo(NULL);
			m_vecInventory[i]->SethadItem(false);
			return true;
		}
	}
	return false;
}
bool cShop::isSoldInvenitem()
{
	for (int i = 0; i < m_vecInventory.size(); i++)
	{
		if (m_vecInventory[i]->GetinvitemInfo()->GetItemInfo() == NULL ||
			m_vecInventory[i]->GetinvitemInfo() == NULL || tempInvitem->GetItemInfo() == NULL)continue;

		if (tempInvitem->GetItemInfo()->itemName == m_vecInventory[i]->GetinvitemInfo()->GetItemInfo()->itemName)
		{
			m_vecInventory[i]->GetinvitemInfo()->SetItemInfo(NULL);

			m_vecInventory[i]->SethadItem(false);

			return true;
		}
	}
}

void cShop::setBluePrintPos()
{
	int nCraftNum = 5;
	float x = 720; float y = 75;
	float _x = 720;
	float _y = 230;
	float xdistance = 50; float ydistance = 60;
	float _xdistance = 40;
	//m_vecCraftPos; //상위노드 위치 시작지점 720.75
	//m_vecMtrlPos; 맨아래 720,280 , x+25; y - 50;
	for (int i = 0; i < nCraftNum; i++)
	{
		m_vecCraftPos.push_back(D3DXVECTOR3(x + (xdistance * i), y, 0));
	}
	m_vecMtrlPos.push_back(D3DXVECTOR3(_x - 10, _y, 0));
	m_vecMtrlPos.push_back(D3DXVECTOR3(_x - 10, _y + ydistance, 0));
	m_vecMtrlPos.push_back(D3DXVECTOR3(_x + 90, _y, 0));
	m_vecMtrlPos.push_back(D3DXVECTOR3(_x + 90, _y + ydistance, 0));
	m_vecMtrlPos.push_back(D3DXVECTOR3(_x + (_xdistance * 5), _y, 0));
	m_vecMtrlPos.push_back(D3DXVECTOR3(_x + (_xdistance * 5) - xdistance, _y + ydistance, 0));
	m_vecMtrlPos.push_back(D3DXVECTOR3(_x + (_xdistance * 5) + xdistance, _y + ydistance, 0));
	m_vecMtrlPos.push_back(D3DXVECTOR3(_x + 90, _y - 70, 0));
}
void cShop::setItemPosition()
{
	float x = 180, y = 120;
	float xdistance = 60; float ydistance = 85;

	for (int i = 0; i < STATE_END; i++)
	{
		for (int j = 0; j < nRow; j++)
		{
			m_vecItemPosition.push_back(D3DXVECTOR3(x + (xdistance * j), y + (ydistance * i), 0));
		}
	}
	for (int i = 0; i < STATE_END; i++)
	{
		std::vector<D3DXVECTOR3> vTemp;
		for (int j = 0; j < m_vecItemPosition.size(); j++)
		{
			if (vTemp.size() >= nRow) break;
			vTemp.push_back(m_vecItemPosition[(j / nRow) + nIndex]);
			nIndex++;
		}
		m_mapPosition.insert(make_pair((tagItemState)i, vTemp));
		vTemp.clear();
	}
}
void cShop::setWholeItemPosition()
{
	nIndex = 0;
	float x = 350; float y = 120;
	float xdistance = 60; float ydistance = 85;

	for (int i = 0; i < STATE_END; i++)
	{
		for (int j = 0; j < nRow; j++)
		{
			m_vecWholeItemPosition.push_back(D3DXVECTOR3(x + (xdistance * j), y + (ydistance * i), 0));
		}
	}

	for (int i = 0; i < m_vecItem.size(); i++)
	{
		m_pInvenInfo = new cInventory;
		citem* itemInfo = new citem;
		m_pInvenInfo->SetinvitemInfo(itemInfo);
		m_pInvenInfo->SethadItem(false);
		m_pInvenInfo->SetvInvenPos(m_vecWholeItemPosition[i]);
		m_vecWholeItem.push_back(m_pInvenInfo);

	}
	for (int i = 0; i < STATE_END; i++)
	{
		std::vector<D3DXVECTOR3> vTemp;
		for (int j = 0; j < m_vecWholeItemPosition.size(); j++)
		{
			if (vTemp.size() >= nRow) break;
			vTemp.push_back(m_vecWholeItemPosition[(j / nRow) + nIndex]);
			nIndex++;
		}
		m_mapWholePosition.insert(make_pair((tagItemState)i, vTemp));
		vTemp.clear();
	}
}
void cShop::setGoldPosition()
{
	float x = 420; float y = 590;
	float xdistance = 20; float ydistance = 0;
	int numberOfcipers = 4;
	for (int i = 0; i < numberOfcipers; i++)
	{
		m_vecGoldPosition.push_back(D3DXVECTOR3(x + (xdistance * i), y + (ydistance * i), 0));
	}
}


void cShop::swap(D3DXVECTOR3* a, D3DXVECTOR3* b)
{
	D3DXVECTOR3 t = *a;
	*a = *b;
	*b = t;
}
void cShop::quickSort(int left, int right, std::vector<cInventory*> data)
{
	/*citem* cPivot = new citem; citem* J = new citem;
	citem* I = new citem;
	cPivot = data[left];
	J = cPivot;
	I = data[left + 1];*/
	bool isSwitched = false;
	int pivot = left;
	int j = pivot;

	if (left < right)
	{
		D3DXVECTOR3 vTemp;
		for (int i = left + 1; i < right; i++)
		{

			int a = data[i]->GetinvitemInfo()->GetItemInfo()->price;
			int b = data[pivot]->GetinvitemInfo()->GetItemInfo()->price;

			if (data[i]->GetinvitemInfo()->GetItemInfo()->price < data[pivot]->GetinvitemInfo()->GetItemInfo()->price)
			{
				citem* item;
				j++;
				item = data[j]->GetinvitemInfo();

				vTemp = data[j]->GetinvitemInfo()->GetItemInfo()->Itemtexture->GetPosition();
				//j==2 , i == 8
				data[j]->GetinvitemInfo()->GetItemInfo()->Itemtexture->setPosition(data[i]->GetinvitemInfo()->GetItemInfo()->Itemtexture->GetPosition());
				data[i]->GetinvitemInfo()->GetItemInfo()->Itemtexture->setPosition(vTemp);

				data[j]->SetinvitemInfo(data[i]->GetinvitemInfo());
				data[i]->SetinvitemInfo(item);
				//롱소드와 와드의 위치가 바뀌엇다.

				isSwitched = true;
			}

			if (isSwitched)
			{
				D3DXVECTOR3 temp; citem* tempitem;
				tempitem = data[left]->GetinvitemInfo();
				temp = data[left]->GetinvitemInfo()->GetItemInfo()->Itemtexture->GetPosition();
				data[left]->GetinvitemInfo()->GetItemInfo()->Itemtexture->setPosition(
					data[j]->GetinvitemInfo()->GetItemInfo()->Itemtexture->GetPosition());

				data[j]->GetinvitemInfo()->GetItemInfo()->Itemtexture->setPosition(
					temp);

				data[left]->SetinvitemInfo(data[j]->GetinvitemInfo());
				data[j]->SetinvitemInfo(tempitem);
				pivot = j;

				isSwitched = false;
			}
		}

		quickSort(left, pivot - 1, data);
		quickSort(pivot + 1, right, data);
	}
}


void cShop::sortItem(std::string strKey, int itemState)
{
	m_eItemState = (tagItemState)itemState;

	if (shopState == WHOLEITEM)
	{
		for (int i = 0; i < m_vecItem.size(); i++)
		{
			m_vecItem[i]->GetItemInfo()->Itemtexture->setPosition(m_vecWholeItemPosition[i]);

			m_vecWholeItem[i]->SetinvitemInfo(m_vecItem[i]);
		}

		quickSort(0, m_vecItem.size(),
			m_vecWholeItem);

		for (int i = 0; i < m_vecItem.size(); i++)
		{
			m_vecItem[i] = m_vecWholeItem[i]->GetinvitemInfo();
		}
	}

	if (shopState == RECOMMAND)
	{
		switch (m_eItemState)
		{
		case START_ITEM:
			m_mapiter = m_mapPosition.find(m_eItemState);
			if (g_pTextureManager->GetImageState(strKey) == m_mapiter->first)
			{
				for (i; i < nRow;)
				{
					if (m_mapiter != m_mapPosition.end())
					{
						for (int k = 0; k < m_vecItem.size(); k++)
						{
							D3DXVECTOR3 temp;
							temp = m_mapiter->second[i];
							if (m_vecItem[k]->GetItemInfo()->itemState == m_eItemState)
								m_vecItem[k]->GetItemInfo()->Itemtexture->setPosition(m_mapiter->second[i]);

							if (temp == m_vecItem[k]->GetItemInfo()->Itemtexture->GetPosition())i++;
						}
						//g_pTextureManager->setPosition(strKey, m_mapiter->second[i]);
					}
					i = 0;
					return;
				}
			}
			break;
		case EARLY_ITEM:
			m_mapiter = m_mapPosition.find(m_eItemState);

			if (g_pTextureManager->GetImageState(strKey) == m_mapiter->first)
			{
				for (m; m < nRow;)
				{
					for (int k = 0; k < m_vecItem.size(); k++)
					{
						D3DXVECTOR3 temp;
						temp = m_mapiter->second[m];
						if (m_vecItem[k]->GetItemInfo()->itemState == m_eItemState)
							m_vecItem[k]->GetItemInfo()->Itemtexture->setPosition(m_mapiter->second[m]);

						if (temp == m_vecItem[k]->GetItemInfo()->Itemtexture->GetPosition())m++;
					}
					m = 0;
					return;
				}
			}
			break;
		case BASIC_ITEM:
			m_mapiter = m_mapPosition.find(m_eItemState);

			if (g_pTextureManager->GetImageState(strKey) == m_mapiter->first)
			{
				for (k; k < nRow;)
				{
					for (int t = 0; t < m_vecItem.size(); t++)
					{
						D3DXVECTOR3 temp;
						temp = m_mapiter->second[k];
						if (m_vecItem[t]->GetItemInfo()->itemState == m_eItemState)
							m_vecItem[t]->GetItemInfo()->Itemtexture->setPosition(m_mapiter->second[k]);

						if (temp == m_vecItem[t]->GetItemInfo()->Itemtexture->GetPosition())k++;
					}
					k = 0;
					return;
				}
			}
			break;
		case CORE_ITEM:
			m_mapiter = m_mapPosition.find(m_eItemState);

			if (g_pTextureManager->GetImageState(strKey) == m_mapiter->first)
			{
				for (p; p < nRow;)
				{
					for (int t = 0; t < m_vecItem.size(); t++)
					{
						D3DXVECTOR3 temp;
						temp = m_mapiter->second[p];
						if (m_vecItem[t]->GetItemInfo()->itemState == m_eItemState)
							m_vecItem[t]->GetItemInfo()->Itemtexture->setPosition(m_mapiter->second[p]);

						if (temp == m_vecItem[t]->GetItemInfo()->Itemtexture->GetPosition())p++;
					}
					p = 0;
					return;
				}
			}
			break;
		case STATE_END:
			break;
		}
	}
}

void cShop::render()
{
	if (m_pShop)
		m_pShop->aniRender();

	if (ClickedItem == "LongSwordBp")
	{
		m_pItemEx->LongSword->Render();
	}
	if (ClickedItem == "DaggerBp")
	{
		m_pItemEx->Dagger->Render();
	}
	if (ClickedItem == "phageBp")
	{
		m_pItemEx->phage->Render();
	}
	if (ClickedItem == "SheenBp")
	{
		m_pItemEx->Sheen->Render();
	}
	if (ClickedItem == "Red_OrbBp")
	{
		m_pItemEx->Red_Orb->Render();
	}
	if (ClickedItem == "Trinity_ForceBp")
	{
		m_pItemEx->Trinity_Force->Render();
	}
	if (ClickedItem == "spBp")
	{
		m_pItemEx->sp->Render();
	}
	if (ClickedItem == "Blue_OrbBp")
	{
		m_pItemEx->Blue_Orb->Render();
	}
	if (ClickedItem == "shoesBp")
	{
		m_pItemEx->shoes->Render();
	}
	if (ClickedItem == "WardBp")
	{
		m_pItemEx->Ward->Render();
	}
	if (ClickedItem == "potionBp")
	{
		m_pItemEx->potion->Render();
	}

	if (m_pPurchaseB)
		m_pPurchaseB->Render();
	if (m_pSaleB)
		m_pSaleB->Render();
	if (m_pReturnB)
		m_pReturnB->Render();
	if (m_pRecommandB)
		m_pRecommandB->Render();
	if (m_pWholeB)
		m_pWholeB->Render();

	for (auto p : m_vecItem)
	{
		p->render();
	}
	// 720 250


	for (auto p : m_mapBluePrint)
	{
		if (ClickedItem == p.first && p.second != NULL)
		{
			p.second->render();
		}
	}


	for (auto p : m_vecSoldButton)
	{
		p->Render();
	}

	if (m_pSelected)
		m_pSelected->Render();

	for (int i = 0; i < m_vecSeleted.size(); i++)
	{
		if (m_vecSeleted.size() != 0)
			m_vecSeleted[i]->Render();
	}

	for (auto p : m_vecInventory)
	{
		if (p->GetinvitemInfo()->GetItemInfo() != NULL)
		{
			p->render();
		}
	}

	GoldRender();
	
	//g_pTextureManager->aniRender("Gold");
	cMainUI::render();
}

bool cShop::isClickInventory(OUT RECT* Outrc, int index)
{
	POINT pt;
	GetCursorPos(&pt);
	ScreenToClient(g_hWnd, &pt);

	int nItem = m_vecInventory.size();
	RECT* rc = new RECT[nItem];
	D3DXMATRIX* pmatWorld = new D3DXMATRIX[nItem];
	ST_UI_SIZE* stSize = new ST_UI_SIZE[nItem];

	for (int i = 0; i < m_vecInventory.size(); i++)
	{
		if (m_vecInventory[index]->GetinvitemInfo()->GetItemInfo() == NULL) continue;

		D3DXMatrixIdentity(pmatWorld);
		pmatWorld[index] = m_vecInventory[index]->GetinvitemInfo()->GetItemInfo()->Itemtexture->GetWolrdMatrix();
		stSize[index] = m_vecInventory[index]->GetinvitemInfo()->GetItemInfo()->m_stSize;
		SetRect(&rc[index],
			(int)m_vecInventory[index]->GetinvitemInfo()->GetItemInfo()->Itemtexture->GetPosition().x,
			(int)m_vecInventory[index]->GetinvitemInfo()->GetItemInfo()->Itemtexture->GetPosition().y,
			(int)m_vecInventory[index]->GetinvitemInfo()->GetItemInfo()->Itemtexture->GetPosition().x + (stSize[index].nWidth * 0.6f),
			(int)m_vecInventory[index]->GetinvitemInfo()->GetItemInfo()->Itemtexture->GetPosition().y + (stSize[index].nHeight * 0.6f));

		Outrc[index] = rc[index];

		SetRect(&Outrc[index],
			(int)m_vecInventory[index]->GetinvitemInfo()->GetItemInfo()->Itemtexture->GetPosition().x,
			(int)m_vecInventory[index]->GetinvitemInfo()->GetItemInfo()->Itemtexture->GetPosition().y,
			(int)m_vecInventory[index]->GetinvitemInfo()->GetItemInfo()->Itemtexture->GetPosition().x + (stSize[index].nWidth * 0.6f),
			(int)m_vecInventory[index]->GetinvitemInfo()->GetItemInfo()->Itemtexture->GetPosition().y + (stSize[index].nHeight * 0.6f));

		if (PtInRect(&rc[index], pt))
		{
			if (g_pKeyManager->IsOnceKeyDown(VK_LBUTTON))
			{
				tempInvitem = m_vecInventory[index]->GetinvitemInfo();

				return true;
			}
		}
	}
	return false;
}
bool cShop::isClickCraft(OUT RECT* Outrc, int index)
{
	POINT pt;
	GetCursorPos(&pt);
	ScreenToClient(g_hWnd, &pt);

	int nItem = m_vecPrintitem.size();
	RECT* rc = new RECT[nItem];
	D3DXMATRIX* pmatWorld = new D3DXMATRIX[nItem];
	ST_UI_SIZE* stSize = new ST_UI_SIZE[nItem];

	for (int i = 0; i < m_vecPrintitem.size(); i++)
	{
		D3DXMatrixIdentity(pmatWorld);
		pmatWorld[index] = m_vecPrintitem[index]->GetItemInfo()->Itemtexture->GetWolrdMatrix();
		stSize[index] = m_vecPrintitem[index]->GetItemInfo()->m_stSize;
		SetRect(&rc[index],
			(int)m_vecPrintitem[index]->GetItemInfo()->Itemtexture->GetPosition().x,
			(int)m_vecPrintitem[index]->GetItemInfo()->Itemtexture->GetPosition().y,
			(int)m_vecPrintitem[index]->GetItemInfo()->Itemtexture->GetPosition().x + (stSize[index].nWidth * 0.6f),
			(int)m_vecPrintitem[index]->GetItemInfo()->Itemtexture->GetPosition().y + (stSize[index].nHeight * 0.6f));

		Outrc[index] = rc[index];

		SetRect(&Outrc[index],
			(int)m_vecPrintitem[index]->GetItemInfo()->Itemtexture->GetPosition().x,
			(int)m_vecPrintitem[index]->GetItemInfo()->Itemtexture->GetPosition().y,
			(int)m_vecPrintitem[index]->GetItemInfo()->Itemtexture->GetPosition().x + (stSize[index].nWidth * 0.6f),
			(int)m_vecPrintitem[index]->GetItemInfo()->Itemtexture->GetPosition().y + (stSize[index].nHeight * 0.6f));

		if (PtInRect(&rc[index], pt))
		{
			if (g_pKeyManager->IsOnceKeyDown(VK_LBUTTON))
			{
				tempitem = new citem;
				tempitem = m_vecPrintitem[index];
				return true;
			}
		}
	}
	return false;
}
bool cShop::isClick(OUT RECT* Outrc, int index)
{
	POINT pt;
	GetCursorPos(&pt);
	ScreenToClient(g_hWnd, &pt);

	int nItem = m_vecItem.size();

	RECT* rc = new RECT[nItem];
	D3DXMATRIX* matWorld = new D3DXMATRIX[nItem];
	ST_UI_SIZE* stSize = new ST_UI_SIZE[nItem];



	for (int i = 0; i < m_vecItem.size(); i++)
	{
		matWorld[index] = m_vecItem[index]->GetItemInfo()->Itemtexture->GetWolrdMatrix();
		stSize[index] = m_vecItem[index]->GetItemInfo()->m_stSize;
		SetRect(&rc[index],
			(int)matWorld[index]._41,
			(int)matWorld[index]._42,
			(int)matWorld[index]._41 + (stSize[index].nWidth * 0.5f),
			(int)matWorld[index]._42 + (stSize[index].nHeight * 0.5f));

		Outrc[index] = rc[index];

		SetRect(&Outrc[index],
			(int)matWorld[index]._41,
			(int)matWorld[index]._42,
			(int)matWorld[index]._41 + (stSize[index].nWidth * 0.5f),
			(int)matWorld[index]._42 + (stSize[index].nHeight * 0.5f));

		if (PtInRect(&rc[index], pt))
		{
			m_pSelected->setScale(D3DXVECTOR3(0.8f, 0.8f, 0.0f));
			m_pSelected->setPosition(D3DXVECTOR3(rc[index].left - 4.5f, rc[index].top - 2.0f, 0.0f));
			m_pSelected->update();
			if (g_pKeyManager->IsOnceKeyDown(VK_LBUTTON))
			{
				tempitem = new citem;
				tempitem = m_vecItem[index];

				if (m_vecSeleted.size() != NULL) m_vecSeleted.pop_back();

				Bitmap* mp = new Bitmap;
				mp = m_pSelected;
				mp->update();

				m_vecSeleted.push_back(mp);
				return true;
			}
		}
	}
	return false;
}
bool cShop::IsSold()
{
	if (ItemPrice == 0) return false;

	if (m_pGold.amount >= ItemPrice)
	{
		m_pGold.amount -= ItemPrice;
		return true;
	}

	else
	{
		m_pGold.amount = m_pGold.amount;
		return false;
	}

	return false;
}
void cShop::GoldUpdate()
{
	m_pGold.count++;
	if (m_pGold.amount <= 9999)
	{
		m_pGold.Gold_units->update(0);
		m_pGold.Gold_tens->update(0);
		m_pGold.Gold_huans->update(0);
		m_pGold.Gold_thous->update(0);
	}
	if (m_pGold.count % 10 == 0)
	{
		m_pGold.amount++;
		m_pGold.count = 0;
	}

	m_pGold.Gold_units->setCurrentFrame((m_pGold.amount % 10) / 1);
	m_pGold.Gold_tens->setCurrentFrame((m_pGold.amount % 100) / 10);
	m_pGold.Gold_huans->setCurrentFrame((m_pGold.amount % 1000) / 100);
	m_pGold.Gold_thous->setCurrentFrame(m_pGold.amount / 1000);

	m_pGold.Gold_units->setPosition(m_vecGoldPosition.back());
	m_pGold.Gold_tens->setPosition(m_vecGoldPosition[2]);
	m_pGold.Gold_huans->setPosition(m_vecGoldPosition[1]);
	m_pGold.Gold_thous->setPosition(m_vecGoldPosition[0]);


}
void cShop::GoldRender()
{
	if (m_pGold.amount != 0)
		m_pGold.Gold_units->aniRender();
	if (m_pGold.amount > 10)
		m_pGold.Gold_tens->aniRender();
	if (m_pGold.amount >= 100)
		m_pGold.Gold_huans->aniRender();
	if (m_pGold.amount >= 1000)
		m_pGold.Gold_thous->aniRender();
}

bool cShop::CraftItem()
{
	for (int i = 0; i < m_vecInventory.size(); i++)
	{
		if (m_vecInventory[i]->GetinvitemInfo()->GetItemInfo() == NULL) continue;

		//Trinity_Force->setup("Trinity_Force", "./item/3078_Trinity_Force.dds", CORE_ITEM, EQUIPABLE);
		//Trinity_Force->GetItemInfo()->price = 999;
		for (int j = 0; j < m_vecInventory.size(); j++)
		{
			if (m_vecInventory[j]->GetinvitemInfo()->GetItemInfo() == NULL) continue;

			if (m_pItemInfo == NULL) continue;
			//Trinity_Force sp Blue_Orb
			//if(m_pItemInfo->GetItemInfo()->itemName == "")
			if (m_pItemInfo->GetItemInfo()->itemName == "Sheen" &&
				m_vecInventory[i]->GetinvitemInfo()->GetItemInfo()->itemName == "phage" &&
				m_vecInventory[j]->GetinvitemInfo()->GetItemInfo()->itemName == "sp")
			{
				m_vecInventory[i]->GetinvitemInfo()->SetItemInfo(NULL);
				m_vecInventory[j]->GetinvitemInfo()->SetItemInfo(NULL);
				m_vecInventory[j]->SethadItem(false);

				citem* NewItem = new citem;
				NewItem->setup("Trinity_Force", "./item/3078_Trinity_Force.dds", CORE_ITEM, EQUIPABLE);
				NewItem->GetItemInfo()->price = 999;
				NewItem->GetItemInfo()->Itemtexture->setPosition(m_vecInventory[i]->GetvInvenPos());
				m_vecInventory[i]->SetinvitemInfo(NewItem);

				return true;
			}
			if (m_pItemInfo->GetItemInfo()->itemName == "phage" &&
				m_vecInventory[i]->GetinvitemInfo()->GetItemInfo()->itemName == "sp" &&
				m_vecInventory[j]->GetinvitemInfo()->GetItemInfo()->itemName == "Sheen")
			{
				m_vecInventory[i]->GetinvitemInfo()->SetItemInfo(NULL);
				m_vecInventory[j]->GetinvitemInfo()->SetItemInfo(NULL);
				m_vecInventory[j]->SethadItem(false);

				citem* NewItem = new citem;
				NewItem->setup("Trinity_Force", "./item/3078_Trinity_Force.dds", CORE_ITEM, EQUIPABLE);
				NewItem->GetItemInfo()->price = 999;
				NewItem->GetItemInfo()->Itemtexture->setPosition(m_vecInventory[i]->GetvInvenPos());
				m_vecInventory[i]->SetinvitemInfo(NewItem);

				return true;
			}
			if (m_pItemInfo->GetItemInfo()->itemName == "sp" &&
				m_vecInventory[i]->GetinvitemInfo()->GetItemInfo()->itemName == "Sheen" &&
				m_vecInventory[j]->GetinvitemInfo()->GetItemInfo()->itemName == "phage")
			{
				m_vecInventory[i]->GetinvitemInfo()->SetItemInfo(NULL);
				m_vecInventory[j]->GetinvitemInfo()->SetItemInfo(NULL);
				m_vecInventory[j]->SethadItem(false);

				citem* NewItem = new citem;
				NewItem->setup("Trinity_Force", "./item/3078_Trinity_Force.dds", CORE_ITEM, EQUIPABLE);
				NewItem->GetItemInfo()->price = 999;
				NewItem->GetItemInfo()->Itemtexture->setPosition(m_vecInventory[i]->GetvInvenPos());
				m_vecInventory[i]->SetinvitemInfo(NewItem);

				return true;
			}
			if (m_pItemInfo->GetItemInfo()->itemName == "LongSword" &&
				m_vecInventory[j]->GetinvitemInfo()->GetItemInfo()->itemName == "Red_Orb")
			{
				citem* NewItem = new citem;
				NewItem->setup("phage", "./item/3044_Phage.dds", CORE_ITEM, EQUIPABLE);
				NewItem->GetItemInfo()->price = 500;
				NewItem->GetItemInfo()->Itemtexture->setPosition(m_vecInventory[j]->GetvInvenPos());
				m_vecInventory[j]->SetinvitemInfo(NewItem);
				return true;
			}
			if (m_pItemInfo->GetItemInfo()->itemName == "Red_Orb" &&
				m_vecInventory[j]->GetinvitemInfo()->GetItemInfo()->itemName == "LongSword")
			{
				citem* NewItem = new citem;
				NewItem->setup("phage", "./item/3044_Phage.dds", CORE_ITEM, EQUIPABLE);
				NewItem->GetItemInfo()->price = 500;
				NewItem->GetItemInfo()->Itemtexture->setPosition(m_vecInventory[j]->GetvInvenPos());
				m_vecInventory[j]->SetinvitemInfo(NewItem);
				return true;
			}

			//Sheen->setup("Sheen", "./item/3057_Sheen.dds", CORE_ITEM, EQUIPABLE);
			//Sheen->GetItemInfo()->price = 500;
			if (m_pItemInfo->GetItemInfo()->itemName == "Sheen" &&
				m_vecInventory[j]->GetinvitemInfo()->GetItemInfo()->itemName == "Blue_Orb")
			{
				m_vecInventory[j]->GetinvitemInfo()->SetItemInfo(NULL);
				citem* NewItem = new citem;
				NewItem->setup("Sheen", "./item/3057_Sheen.dds", CORE_ITEM, EQUIPABLE);
				NewItem->GetItemInfo()->price = 500;
				NewItem->GetItemInfo()->Itemtexture->setPosition(m_vecInventory[j]->GetvInvenPos());
				m_vecInventory[j]->SetinvitemInfo(NewItem);
				return true;
			}

			if (m_pItemInfo->GetItemInfo()->itemName == "sp" &&
				m_vecInventory[j]->GetinvitemInfo()->GetItemInfo()->itemName == "Dagger")
			{
				m_vecInventory[j]->GetinvitemInfo()->SetItemInfo(NULL);
				citem* NewItem = new citem;
				NewItem->setup("sp", "./item/3058_Sheen_and_Phage.dds", EARLY_ITEM, EQUIPABLE);
				NewItem->GetItemInfo()->price = 300;
				NewItem->GetItemInfo()->Itemtexture->setPosition(m_vecInventory[j]->GetvInvenPos());
				m_vecInventory[j]->SetinvitemInfo(NewItem);
				return true;
			}
		}
	}
	return false;
}
bool cShop::isClickUi()
{
	return true;
}




void cShop::ItemDragDrop()
{
	POINT pt;
	GetCursorPos(&pt);
	ScreenToClient(g_hWnd, &pt);

	for (int i = 0; i < m_vecInventory.size(); i++)
	{

		int nItem = m_vecInventory.size();
		RECT* rc = new RECT[nItem];
		D3DXMATRIX* pmatWorld = new D3DXMATRIX[nItem];
		ST_UI_SIZE* stSize = new ST_UI_SIZE[nItem];


		if (m_vecInventory[i]->GetinvitemInfo()->GetItemInfo() == NULL) continue;


		ST_UI_SIZE tempsize;
		RECT itemp; RECT jtemp;
		D3DXMatrixIdentity(pmatWorld);
		pmatWorld[i] = m_vecInventory[i]->GetinvitemInfo()->GetItemInfo()->Itemtexture->GetWolrdMatrix();
		stSize[i] = m_vecInventory[i]->GetinvitemInfo()->GetItemInfo()->m_stSize;
		SetRect(&rc[i],
			(int)m_vecInventory[i]->GetinvitemInfo()->GetItemInfo()->Itemtexture->GetPosition().x,
			(int)m_vecInventory[i]->GetinvitemInfo()->GetItemInfo()->Itemtexture->GetPosition().y,
			(int)m_vecInventory[i]->GetinvitemInfo()->GetItemInfo()->Itemtexture->GetPosition().x + (stSize[i].nWidth * 0.5f),
			(int)m_vecInventory[i]->GetinvitemInfo()->GetItemInfo()->Itemtexture->GetPosition().y + (stSize[i].nHeight * 0.5f));

		tempsize = stSize[i];
		itemp = rc[i];

	
		if (PtInRect(&rc[i], pt))
		{
			if (g_pKeyManager->IsOnceKeyDown(VK_LBUTTON))
			{
				m_bIsDrag = true;
				m_nDragIndex = i;
			}

		}

		if (g_pKeyManager->IsOnceKeyUp(VK_LBUTTON) && m_nDragIndex == i)
		{
			bool isChange = false;

			for (int j = 0; j < m_vecInventory.size(); j++)
			{

				POINT ptInvenPos;
				ptInvenPos.x = (int)m_vecInventory[j]->GetvInvenPos().x + (tempsize.nWidth * 0.4f) / 2;
				ptInvenPos.y = (int)m_vecInventory[j]->GetvInvenPos().y + (tempsize.nHeight * 0.6f) / 2;

				if (PtInRect(&itemp, ptInvenPos))// 인벤의 중점과 내가 드래그한 사각형이 일치하면
				{
					if (m_vecInventory[j]->GethadItem())
					{
						D3DXVECTOR3 vTemp = m_vecInventory[i]->GetvInvenPos();
						m_vecInventory[i]->GetinvitemInfo()->GetItemInfo()->Itemtexture->setPosition(
							m_vecInventory[j]->GetvInvenPos());
						m_vecInventory[j]->GetinvitemInfo()->GetItemInfo()->Itemtexture->setPosition(
							vTemp);

						citem* tempitem;
						tempitem = m_vecInventory[i]->GetinvitemInfo();

						m_vecInventory[i]->SetinvitemInfo(m_vecInventory[j]->GetinvitemInfo());
						m_vecInventory[j]->SetinvitemInfo(tempitem);
						m_vecInventory[i]->SethadItem(true);
						m_vecInventory[j]->SethadItem(true);
					}
					else
					{
						m_vecInventory[i]->GetinvitemInfo()->GetItemInfo()->Itemtexture->setPosition(
							m_vecInventory[j]->GetvInvenPos());
						citem* tempitem;
						tempitem = m_vecInventory[i]->GetinvitemInfo();

						m_vecInventory[i]->SetinvitemInfo(m_vecInventory[j]->GetinvitemInfo());
						m_vecInventory[j]->SetinvitemInfo(tempitem);
						m_vecInventory[i]->SethadItem(false);
						m_vecInventory[j]->SethadItem(true);
					}
					isChange = true;
					break;
				}

			}

			if (!isChange)	// 변화가 없으면
			{
				m_vecInventory[i]->GetinvitemInfo()->GetItemInfo()->Itemtexture->setPosition(
					m_vecInventory[i]->GetvInvenPos());
			}
			m_nDragIndex = -1;
			m_bIsDrag = false;
		}

	}

	if (g_pKeyManager->IsStayKeyDown(VK_LBUTTON))
	{
		if (m_bIsDrag)
			m_vecInventory[m_nDragIndex]->GetinvitemInfo()->GetItemInfo()->Itemtexture->setPosition(D3DXVECTOR3(pt.x - 12, pt.y - 10, 0));
	}

}

void cShop::InvenRender()
{

}