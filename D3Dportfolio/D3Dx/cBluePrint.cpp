#include "stdafx.h"
#include "cBluePrint.h"


cBluePrint::cBluePrint()
{
}


cBluePrint::~cBluePrint()
{
	release();
}
void cBluePrint::AddChild(std::string strKey, cBluePrint* pChild)
{
	m_mapChild.insert(std::make_pair(strKey, pChild));
	
	
	pChild->SetParent(this);
	
}
cBluePrint* cBluePrint::findParent()
{
	m_mapChilditer = m_mapChild.begin();

	if (m_mapChilditer != m_mapChild.end())
	{
		return m_mapChilditer->second->GetParent();
	}

	return false;
}
void cBluePrint::setup()
{
	for (auto p : m_mapChild)
	{
		p.second->setup();
	}
}
void cBluePrint::update()
{
	for (auto p : m_mapChild)
	{
		p.second->update();
	}
}
void cBluePrint::render()
{
	for (auto p : m_mapChild)
	{
		p.second->render();
	}
}

void cBluePrint::release()
{
	/*for (auto p : m_mapChild)
	{
		p.second->release();
	}
	delete this;*/
}
