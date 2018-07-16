#pragma once


class cBluePrint
{
private:
	std::map<std::string, cBluePrint*> m_mapChild;
	std::map<std::string, cBluePrint*>::iterator m_mapChilditer;

	SYNTHESIZE(cBluePrint*, m_pParent, Parent);
public:
	cBluePrint();
	virtual ~cBluePrint();


	void AddChild(std::string strKey, cBluePrint* pChild);
	cBluePrint* findParent();

	virtual void setup();
	virtual void update();
	virtual void render();

	virtual void release();
};

