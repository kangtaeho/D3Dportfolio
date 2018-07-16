#pragma once

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
		amount = 9500; //√÷¥Î 9999;
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
	virtual bool isClickUi();

	virtual void GoldUpdate();
	virtual void GoldRender();
	std::map<std::string, cMainUI*> GetUIinfo() { return m_mapChild; }
};

