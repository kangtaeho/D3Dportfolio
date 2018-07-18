#include "stdafx.h"
#include "cUIButton.h"


cUIButton::cUIButton()
{
}


cUIButton::~cUIButton()
{
}

void cUIButton::setTexture(const char* szUp, const char* szOver, const char* szDown)
{
	D3DXIMAGE_INFO stImageInfo;

	stImageInfo = g_pTextureManager->GetImageInfo(szUp);

	m_arrTexture[BT_UP] = g_pTextureManager->getTexture(szUp);

	m_stSize.nHeight = stImageInfo.Height;
	m_stSize.nWidth = stImageInfo.Width;


	m_arrTexture[BT_OVER] = g_pTextureManager->getTexture(szOver);

	m_arrTexture[BT_DOWN] = g_pTextureManager->getTexture(szDown);


	m_matWorld = &g_pTextureManager->GetWorldMatrix(szUp);
	m_pSprite = g_pTextureManager->GetSprite(szUp);
	szTemp = szUp;
}
void cUIButton::update()
{
	POINT pt;
	GetCursorPos(&pt);
	ScreenToClient(g_hWnd, &pt);


	RECT rc;
	SetRect(&rc,
		(int)m_matWorld->_41,
		(int)m_matWorld->_42,
		(int)m_matWorld->_41 + m_stSize.nWidth * 0.7f,
		(int)m_matWorld->_42 + m_stSize.nHeight * 0.7f);

	if (PtInRect(&rc, pt))
	{
		m_buttonState = BT_OVER;
		if (g_pKeyManager->IsOnceKeyDown(VK_LBUTTON))
		{
			m_buttonState = BT_DOWN;
		}
		else if (g_pKeyManager->IsOnceKeyUp(VK_LBUTTON))
		{
			m_buttonState = BT_OVER;
		}
		/*if (GetKeyState(VK_LBUTTON) & 0x8000)
		{
		if (m_buttonState == BT_OVER)
		{
		m_buttonState = BT_DOWN;
		}
		}
		else
		{
		if (BT_DOWN == m_buttonState)
		{
		if (m_pDelegate)
		m_pDelegate->OnClick(this);
		}
		m_buttonState = BT_OVER;
		}*/
	}
	else
	{
		m_buttonState = BT_UP;
	}


	g_pTextureManager->update(szTemp);
}
void cUIButton::Render()
{
	m_pSprite->Begin(D3DXSPRITE_SORT_TEXTURE);

	m_pSprite->SetTransform(m_matWorld);

	RECT rc;
	SetRect(&rc, 0, 0, m_stSize.nWidth, m_stSize.nHeight);
	m_pSprite->Draw(m_arrTexture[m_buttonState], &rc,
		&D3DXVECTOR3(0, 0, 0),
		&D3DXVECTOR3(0, 0, 0),
		D3DCOLOR_ARGB(255, 255, 255, 255));

	m_pSprite->End();
}

void cUIButton::setPosition(D3DXVECTOR3 vPosition)
{
	g_pTextureManager->setPosition(szTemp, vPosition);
}
void cUIButton::setScale(D3DXVECTOR3 vScale)
{
	g_pTextureManager->setScale(szTemp, vScale);
}