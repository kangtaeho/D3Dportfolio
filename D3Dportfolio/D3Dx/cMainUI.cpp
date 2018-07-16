#include "stdafx.h"
#include "cMainUI.h"


cMainUI::cMainUI()
	: m_pParent(NULL)
	, m_stSize(0,0)
{
}


cMainUI::~cMainUI()
{
	Destroy();
}

void cMainUI::AddChild(cMainUI* pChild,std::string UiName)
{
	m_mapChild.insert(std::make_pair(UiName, pChild));
	
	pChild->SetParent(this);
}
void cMainUI::Destroy()
{
	for (auto child : m_mapChild)
	{
		child.second->Destroy();
	}
	delete this;
}
void cMainUI::setup()
{
	for (auto child : m_mapChild)
	{
		child.second->setup();
	}
}
void cMainUI::update()
{
	m_mapiter = m_mapChild.find(m_pNodeName);

	if (m_mapiter != m_mapChild.end())
	{
		m_mapiter->second->update();
	}
	GoldUpdate();
}
void cMainUI::render()
{
	m_mapiter = m_mapChild.find(m_pNodeName);

	if (m_mapiter != m_mapChild.end())
	{
		m_mapiter->second->render();
	}
	GoldRender();
}

bool cMainUI::isClickUi()
{
	for (auto child : m_mapChild)
	{
		if (child.second->isClickUi()) return true;
	}

	return false;
}

void cMainUI::GoldUpdate()
{

}
void cMainUI::GoldRender()
{

}