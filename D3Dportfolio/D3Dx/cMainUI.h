#pragma once

class cInventory;

struct tagGoldState
{
	Bitmap* Gold_units;
	Bitmap* Gold_tens;
	Bitmap* Gold_huans;
	Bitmap* Gold_thous;
	int goldIncreaseTime;
	int amount;
	int count;
	tagGoldState() {
		amount = 3000; //√÷¥Î 9999;
		goldIncreaseTime = 0;
		count = 0;
	}
};

class cMainUI
{
protected:
	ST_UI_SIZE m_stSize;

	SYNTHESIZE(std::string, m_pNodeName, NodeName);
	std::map<std::string, cMainUI*> m_mapChild;
	std::map<std::string, cMainUI*>::iterator m_mapiter;
	std::map<std::string, cMainUI*>::iterator m_mapiterator;
	SYNTHESIZE(cMainUI*, m_pParent, Parent);

	SYNTHESIZE_REF(tagGoldState, m_pGold, Gold);
	
	
public:
	cMainUI();
	virtual ~cMainUI();

	virtual void AddChild(cMainUI* pChild, std::string UiName);
	virtual void Destroy();
	virtual void setup();
	virtual void update();
	virtual void render();
	virtual bool isClickUi() = 0;

	virtual void GoldUpdate() = 0;
	virtual void GoldRender() = 0;
	virtual void InvenRender() = 0;
	std::map<std::string, cMainUI*> GetUIinfo() { return m_mapChild; }
};

