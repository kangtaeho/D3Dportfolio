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
	m_bCheckBarSize = false;
	m_bCheckHit = false;

	SetRect(&m_BarRect, 0, 0, m_fMaxHp, m_fBarBottom);

	m_fBarSize = m_fBarRight / m_fMaxHp;

	m_pHpBar->SetRectFrameSize(m_BarRect);
	m_pHpBar->setScale(D3DXVECTOR3(m_fBarSize, 1.0f, 0));
	m_pMpBar->SetRectFrameSize(m_BarRect);
	m_pMpBar->setScale(D3DXVECTOR3(m_fBarSize, 1.0f, 0));
}

void cHealthProgress::setBarPosition(D3DXVECTOR3 HpPosition, D3DXVECTOR3 MpPosition)
{
	m_pContainer->setPosition(D3DXVECTOR3(HpPosition.x - 50, HpPosition.y - 30, 0));
	m_pHpBar->setPosition(HpPosition);
	m_pMpBar->setPosition(MpPosition);
}
void cHealthProgress::update()
{
	m_pContainer->update();
	m_pHpBar->update(0);
	m_pMpBar->update(0);

	m_fCurrentHp = m_fMaxHp - m_fHitvalue;

	if (!m_bCheckBarSize)
	{
		m_fBarRight = m_pHpBar->GetrectFrameSize()->right;
		m_fBarBottom = m_pHpBar->GetrectFrameSize()->bottom;

		m_bCheckBarSize = true;
	}


	if (m_bCheckHit)
	{
		if(m_pHpBar->GetrectFrameSize()->left <= m_pHpBar->GetrectFrameSize()->right)
			m_pHpBar->GetrectFrameSize()->right -= m_fHitvalue;
	}
}
void cHealthProgress::render()
{
	m_pContainer->Render();
	m_pHpBar->Render();
	m_pMpBar->Render();
}

void cHealthProgress::Release()
{
	
}