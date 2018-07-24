#include "stdafx.h"
#include "cHealthProgress.h"
#include "Bitmap.h"

cHealthProgress::cHealthProgress()
{
}


cHealthProgress::~cHealthProgress()
{
	
}

void cHealthProgress::setup()
{
	m_pContainer = new Bitmap;
	m_pHpBar = new Bitmap;
	m_pMpBar = new Bitmap;

	m_pContainer = g_pTextureManager->addTexture("Container", "./status/playerHpContainer.dds", NULL, NULL);
	m_pHpBar = g_pTextureManager->addTexture("PlayerHpBar", "./status/playerHpBar.dds",PROGRESSBAR, 1, 1);
	m_pMpBar = g_pTextureManager->addTexture("PlayerMpBar", "./status/playerMpBar.dds", PROGRESSBAR, 1, 1);

	m_fMaxHp = 500;
	m_fCurrentHp = 500;
	m_fHitvalue = 30;
	m_bCheckHpBarSize = false;
	m_bCheckHpHit = false;

	m_fHpBarRight = m_pHpBar->GetrectFrameSize()->right;
	m_fHpBarBottom = m_pHpBar->GetrectFrameSize()->bottom;

	SetRect(&m_HpBarRect, 0, 0, m_fMaxHp, m_fHpBarBottom);

	m_fHpBarSize = m_fHpBarRight / m_fMaxHp;

	m_pHpBar->SetRectFrameSize(m_HpBarRect);
	m_pHpBar->setScale(D3DXVECTOR3(m_fHpBarSize, 1.0f, 0));

	m_fMaxMp = 300;
	m_fCurrentMp = 300;
	m_fUsedMpValue = 30;
	m_bCheckMpBarSize = false;
	m_bCheckMpUsed = false;

	m_fMpBarRight = m_pMpBar->GetrectFrameSize()->right;
	m_fMpBarBottom = m_pMpBar->GetrectFrameSize()->bottom;

	SetRect(&m_MpBarRect, 0, 0, m_fMaxMp, m_fMpBarBottom);

	m_fMpBarSize = m_fMpBarRight / m_fMaxMp;
	m_pMpBar->SetRectFrameSize(m_MpBarRect);
	m_pMpBar->setScale(D3DXVECTOR3(m_fMpBarSize, 1.0f, 0));

	//m_pMpBar->SetRectFrameSize(m_BarRect);
	//m_pMpBar->setScale(D3DXVECTOR3(m_fBarSize, 1.0f, 0));
}

void cHealthProgress::setBarPosition(D3DXVECTOR3 HpPosition, D3DXVECTOR3 MpPosition)
{
	m_pContainer->setPosition(D3DXVECTOR3(HpPosition.x - 80, HpPosition.y - 70, 0));
	m_pHpBar->setPosition(D3DXVECTOR3(HpPosition.x - 55,HpPosition.y - 62,HpPosition.z));
	m_pMpBar->setPosition(D3DXVECTOR3(HpPosition.x ,HpPosition.y,HpPosition.z));
}
void cHealthProgress::update()
{
	m_pContainer->update();
	m_pHpBar->update(0);
	m_pMpBar->update(0);

	
	//m_fCurrentHp = m_fMaxHp - m_fHitvalue;

	//if (!m_bCheckBarSize)
	//{
	//	m_fBarRight = m_pHpBar->GetrectFrameSize()->right;
	//	m_fBarBottom = m_pHpBar->GetrectFrameSize()->bottom;

	//	m_bCheckBarSize = true;
	//}


	//if (m_bCheckHit)
	//{
	//	if(m_pHpBar->GetrectFrameSize()->left <= m_pHpBar->GetrectFrameSize()->right)
	//		m_pHpBar->GetrectFrameSize()->right -= m_fHitvalue;
	//}
}
void cHealthProgress::render()
{
	m_pContainer->Render();
	m_pHpBar->aniRender();
	m_pMpBar->aniRender();
}

void cHealthProgress::Release()
{
	
}