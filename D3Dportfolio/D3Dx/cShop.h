#pragma once
#include "cMainUI.h"

class Bitmap;
class cUIButton;
class cBluePrint;
class citem;
class cInventory;

enum tagShopState
{
	WHOLEITEM = 1,
	RECOMMAND
};

struct ex {
	Bitmap* potion;
	Bitmap* shoes;
	Bitmap* LongSword;
	Bitmap* Dagger;
	Bitmap* phage;
	Bitmap* Sheen;
	Bitmap* Red_Orb;
	Bitmap* Trinity_Force;
	Bitmap* Ward;
	Bitmap* sp;
	Bitmap* Blue_Orb;

	ex() {
		potion = new Bitmap;
		potion = g_pTextureManager->addTexture("potionEx", "./ex/potionEx.dds", ITEM, 0);
		

		shoes = new Bitmap;
		shoes = g_pTextureManager->addTexture("shoesEx", "./ex/shoesEx.dds", ITEM, 0);
		LongSword = new Bitmap;
		LongSword = g_pTextureManager->addTexture("LongSwordEx", "./ex/LongSwordEx.dds", ITEM, 0);
		Dagger = new Bitmap;
		Dagger = g_pTextureManager->addTexture("DaggerEx", "./ex/DaggerEx.dds", ITEM, 0);
		phage = new Bitmap;
		phage = g_pTextureManager->addTexture("phageEx", "./ex/hammerEx.dds", ITEM, 0);
		Sheen = new Bitmap;
		Sheen = g_pTextureManager->addTexture("SheenEx", "./ex/Sword2Ex.dds", ITEM, 0);
		Red_Orb = new Bitmap;
		Red_Orb = g_pTextureManager->addTexture("Red_OrbEx", "./ex/Red_OrbEx.dds", ITEM, 0);
		Trinity_Force = new Bitmap;
		Trinity_Force = g_pTextureManager->addTexture("Trinity_ForceEx", "./ex/TriForceEx.dds", ITEM, 0);
		Ward = new Bitmap;
		Ward = g_pTextureManager->addTexture("WardEx", "./ex/WardEx.dds", ITEM, 0);
		sp = new Bitmap;
		sp = g_pTextureManager->addTexture("spEx", "./ex/sword3Ex.dds", ITEM, 0);
		Blue_Orb = new Bitmap;
		Blue_Orb = g_pTextureManager->addTexture("shoesEx", "./ex/Blue_OrbEx.dds", ITEM, 0);
	}
};
class cShop : public cMainUI
{
private:
	ex* m_pItemEx;
	

	citem * potion; citem* shoes; citem* LongSword;
	citem* Dagger; citem* phage; citem* Sheen;
	citem* Red_Orb; citem* Trinity_Force; citem* Ward;
	citem* sp; citem* Blue_Orb;
	cBluePrint* Trinity_Force_bp;	cBluePrint* Sheen_Bp;
	cBluePrint* phage_Bp; cBluePrint* sp_Bp;
	cBluePrint* temp;
protected:
	tagShopState		shopState;
	cInventory*			m_pInvenInfo;
	citem*				m_pItemInfo; citem* tempitem; citem* tempInvitem;

	citem* tempLongSword; citem* tempDagger;
	citem* tempphage; citem* tempSheen; citem* tempRed_Orb;
	citem* tempTrinity_Force; citem* tempsp; citem* tempBlue_Orb;


	SYNTHESIZE(std::vector<cInventory*>, m_vecInventory, vecInventory);

	std::vector<D3DXVECTOR3> m_vecShopInven;


	//std::vector<cInventory*> m_vecInventory;
	cUIButton*			m_pPurchaseB;
	cUIButton*			m_pSaleB;
	cUIButton*			m_pReturnB;
	cUIButton*			m_pRecommandB;
	cUIButton*			m_pWholeB;
	LPD3DXSPRITE		m_pSprite;
	//tagGoldState		m_pGold;

	std::vector<D3DXVECTOR3> m_vecCraftPos;//���۾����� ��ġ.
	std::vector<D3DXVECTOR3> m_vecMtrlPos; //�������� ��ġ.

	std::vector<citem*>		 m_vecItem; //������ ���� ����
	std::vector<D3DXVECTOR3> m_vecItemPosition; //������ ��ġ����� ����
	std::vector<D3DXVECTOR3> m_vecGoldPosition; //�����ġ ����

	std::vector<D3DXVECTOR3> m_vecWholeItemPosition;

	std::map<tagItemState, std::vector<D3DXVECTOR3>>		   m_mapWholePosition;
	std::map<tagItemState, std::vector<D3DXVECTOR3>>::iterator m_mapWpiter;
	std::map<tagItemState, std::vector<D3DXVECTOR3>>		   m_mapPosition; //��ġ �����ϱ����� ��
	std::map<tagItemState, std::vector<D3DXVECTOR3>>::iterator m_mapiter; //����

	tagItemState		     m_ItemPosState; //�����ۻ�������
	std::vector<Bitmap*>     m_vecSoldButton; //��ư
	int ItemPrice; //������ ������ ��������� ��Ʈ.
	int nIndex; int nRow;
	int i, m, k, p;
	tagItemState m_eItemState;
	int nItem;

	std::string ClickedItem;
	std::string m_sItemName;
	std::map<std::string, cBluePrint*> m_mapBluePrint; //���赵
	Bitmap* m_pShop; //���� â
	Bitmap* m_pSelected; //������ Ŭ���� ��Ÿ���� ��ư.

	std::vector<Bitmap*> m_vecSeleted;

	std::vector<citem*> m_vecPrintitem; //���赵�� ��� �����ۺ���
	Bitmap* checkButton;
	RECT* m_pRect;//Ŭ���� ��Ʈ;
	RECT* m_pRectCraft;
	RECT* m_pRectInv;
	int m_nDragIndex;
	bool m_bIsDrag;


	
	D3DXMATRIX* m_matWorld;
	D3DXMATRIX* matT;
	D3DXMATRIX* matS;
	D3DXVECTOR3* scale, *position;
	std::vector<cInventory*> m_vecWholeItem;
public:
	cShop();
	virtual ~cShop();

	virtual void setup();
	virtual void update();
	virtual void render();

	
	void NewItem();
	void DeleteItem();
	void ItemSetting(); //��������ġ����
	void setInventoryInfo();
	void setItemPosition(); //��������ġ����
	void setWholeItemPosition();
	void setGoldPosition(); //���� �Ⱦ�
	void setBluePrintPos();
	void setBluePrintInfo(std::string strKey, int index);
	void ItemDragDrop();
	void sortItem(std::string strKey, int itemState); //�����ϴ� �Լ�
	void sortItemInfo();

	bool IsSold(); //�����Ⱦ�
	bool isClick(OUT RECT* Outrc, int index); //Ŭ�� ���� �����Լ�.
	bool isClickCraft(OUT RECT* Outrc, int index);
	bool isClickInventory(OUT RECT* Outrc, int index);

	bool isSoldInvenitem();

	bool returnItem();
	bool CraftItem(); //������ ����
	virtual bool isClickUi();


	void GoldUpdate();
	void GoldRender();

	void swap(D3DXVECTOR3* a, D3DXVECTOR3* b);
	void quickSort(int left, int right, std::vector<cInventory*> data);


	void InvenRender();
};

