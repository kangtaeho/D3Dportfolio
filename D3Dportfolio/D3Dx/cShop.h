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


class cShop : public cMainUI
{
private:
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
	std::vector<D3DXVECTOR3> m_vecShopInven;
	std::vector<cInventory*> m_vecInventory;
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
};

