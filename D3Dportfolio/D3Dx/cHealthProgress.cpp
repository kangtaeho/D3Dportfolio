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
	m_bCheckHpBarSize = false;
	

	ReCorrectSize = true;

	m_fMaxMp = 300;
	m_fCurrentMp = m_fMaxMp;
	m_fUsedMpValue = 30;
	m_bCheckMpBarSize = false;
	


	m_fHpBarRight = m_pHpBar->GetrectFrameSize()->right;
	m_fHpBarBottom = m_pHpBar->GetrectFrameSize()->bottom;

	SetRect(&m_HpBarRect, 0, 0, m_fMaxHp, m_fHpBarBottom);

	m_fHpBarSize = m_fHpBarRight / m_fMaxHp;

	m_pHpBar->setScale(D3DXVECTOR3(m_fHpBarSize, 1.0f, 0));
	m_pHpBar->SetRectFrameSize(m_HpBarRect);

	PrevHpSize = m_fHpBarRight;



	m_fMpBarRight = m_pMpBar->GetrectFrameSize()->right;
	m_fMpBarBottom = m_pMpBar->GetrectFrameSize()->bottom;

	SetRect(&m_MpBarRect, 0, 0, m_fMaxMp, m_fMpBarBottom);

	m_fMpBarSize = m_fMpBarRight / m_fMaxMp;
	m_pMpBar->SetRectFrameSize(m_MpBarRect);
	m_pMpBar->setScale(D3DXVECTOR3(m_fMpBarSize, 0.7f, 0));

	PrevMpSize = m_fMpBarRight;
	//m_pMpBar->SetRectFrameSize(m_BarRect);
	//m_pMpBar->setScale(D3DXVECTOR3(m_fBarSize, 1.0f, 0));
}

void cHealthProgress::setBarPosition(D3DXVECTOR3 HpPosition, D3DXVECTOR3 MpPosition)
{
	m_pContainer->setPosition(D3DXVECTOR3(HpPosition.x - 80, HpPosition.y - 70, 0));
	m_pHpBar->setPosition(D3DXVECTOR3(HpPosition.x - 48,HpPosition.y - 62,0));
	m_pMpBar->setPosition(D3DXVECTOR3(HpPosition.x - 48 ,HpPosition.y - 52,0));
}
void cHealthProgress::update()
{
	m_pContainer->update();
	m_pHpBar->update(0);
	m_pMpBar->update(0);

	if (ReCorrectSize)
	{
		SetRect(&m_HpBarRect, 0, 0, m_fMaxHp, m_fHpBarBottom);
		m_pHpBar->SetRectFrameSize(m_HpBarRect);

		m_fHpBarRight = m_pHpBar->GetrectFrameSize()->right;
		m_fHpBarBottom = m_pHpBar->GetrectFrameSize()->bottom;

		m_fHpBarSize = PrevHpSize / m_fHpBarRight;

		m_pHpBar->setScale(D3DXVECTOR3(m_fHpBarSize, 1.0f, 0));


		SetRect(&m_MpBarRect, 0, 0, m_fMaxMp, m_fMpBarBottom);
		m_pMpBar->SetRectFrameSize(m_MpBarRect);
		m_fMpBarRight = m_pMpBar->GetrectFrameSize()->right;
		m_fMpBarBottom = m_pMpBar->GetrectFrameSize()->bottom;

		m_fMpBarSize = PrevMpSize / m_fMpBarRight;
		m_pMpBar->setScale(D3DXVECTOR3(m_fMpBarSize, 0.7f, 0));
		ReCorrectSize = false;
	}

	if (m_bCheckHpBarSize)
	{
		if (m_fCurrentHp > 0)
			m_fCurrentHp = m_fCurrentHp - m_fHitvalue;

		if (m_pHpBar->GetrectFrameSize()->right <= 0) m_pHpBar->GetrectFrameSize()->right = 0;

		if (m_pHpBar->GetrectFrameSize()->left < m_pHpBar->GetrectFrameSize()->right)
			m_pHpBar->GetrectFrameSize()->right -= m_fHitvalue;

		m_bCheckHpBarSize = false;
	}
	if (m_bCheckMpBarSize)
	{
		if (m_fCurrentMp > 0)
			m_fCurrentMp = m_fCurrentMp - m_fUsedMpValue;

		if (m_pMpBar->GetrectFrameSize()->right <= 0)m_pMpBar->GetrectFrameSize()->right = 0;

		if (m_pMpBar->GetrectFrameSize()->left < m_pMpBar->GetrectFrameSize()->right)
		{
			m_pMpBar->GetrectFrameSize()->right -= m_fUsedMpValue;
		}
		m_bCheckMpBarSize = false;
	}
	
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