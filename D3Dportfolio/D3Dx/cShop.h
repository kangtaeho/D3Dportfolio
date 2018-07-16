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

	std::vector<D3DXVECTOR3> m_vecCraftPos;//제작아이템 위치.
	std::vector<D3DXVECTOR3> m_vecMtrlPos; //재료아이템 위치.

	std::vector<citem*>		 m_vecItem; //아이템 관리 벡터
	std::vector<D3DXVECTOR3> m_vecItemPosition; //아이템 위치찍어준 벡터
	std::vector<D3DXVECTOR3> m_vecGoldPosition; //골드위치 벡터

	std::vector<D3DXVECTOR3> m_vecWholeItemPosition;

	std::map<tagItemState, std::vector<D3DXVECTOR3>>		   m_mapWholePosition;
	std::map<tagItemState, std::vector<D3DXVECTOR3>>::iterator m_mapWpiter;
	std::map<tagItemState, std::vector<D3DXVECTOR3>>		   m_mapPosition; //위치 정렬하기위한 맵
	std::map<tagItemState, std::vector<D3DXVECTOR3>>::iterator m_mapiter; //동일

	tagItemState		     m_ItemPosState; //아이템상태정보
	std::vector<Bitmap*>     m_vecSoldButton; //버튼
	int ItemPrice; //선택한 아이템 가격저장용 인트.
	int nIndex; int nRow;
	int i, m, k, p;
	tagItemState m_eItemState;
	int nItem;

	std::string ClickedItem;
	std::string m_sItemName;
	std::map<std::string, cBluePrint*> m_mapBluePrint; //설계도
	Bitmap* m_pShop; //상점 창
	Bitmap* m_pSelected; //아이템 클릭시 나타나는 버튼.

	std::vector<Bitmap*> m_vecSeleted;

	std::vector<citem*> m_vecPrintitem; //설계도에 담긴 아이템벡터
	Bitmap* checkButton;
	RECT* m_pRect;//클릭할 렉트;
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
	void ItemSetting(); //아이템위치세팅
	void setInventoryInfo();
	void setItemPosition(); //아이템위치정렬
	void setWholeItemPosition();
	void setGoldPosition(); //아직 안씀
	void setBluePrintPos();
	void setBluePrintInfo(std::string strKey, int index);
	void ItemDragDrop();
	void sortItem(std::string strKey, int itemState); //정렬하는 함수
	void sortItemInfo();

	bool IsSold(); //아직안씀
	bool isClick(OUT RECT* Outrc, int index); //클릭 판정 여부함수.
	bool isClickCraft(OUT RECT* Outrc, int index);
	bool isClickInventory(OUT RECT* Outrc, int index);

	bool isSoldInvenitem();

	bool returnItem();
	bool CraftItem(); //아이템 조합
	virtual bool isClickUi();


	void GoldUpdate();
	void GoldRender();

	void swap(D3DXVECTOR3* a, D3DXVECTOR3* b);
	void quickSort(int left, int right, std::vector<cInventory*> data);
};

