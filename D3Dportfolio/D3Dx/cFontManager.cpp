#include "stdafx.h"
#include "cFontManager.h"


cFontManager::cFontManager()
	:m_bIsSetup(false)
{
}


cFontManager::~cFontManager()
{
	
}

void cFontManager::Setup()
{
	D3DXFONT_DESC desc;
	memset(&desc, 0, sizeof(D3DXFONT_DESC));
	desc.CharSet = HANGUL_CHARSET;
	desc.Height = 20;
	desc.Width = 10;
	desc.Weight = FW_NORMAL;
	desc.Quality = DEFAULT_QUALITY;
	desc.MipLevels = 1;
	desc.Italic = 0;
	desc.OutputPrecision = OUT_DEFAULT_PRECIS;
	desc.PitchAndFamily = FF_DONTCARE;

	D3DXCreateFontIndirect(g_pD3DDevice, &desc, &m_pFont);

	m_bIsSetup = true;
}

void cFontManager::TextFont(int x, int y, char* text, ...)
{
	RECT rc;
	char str[258] = { 0, };		// ÃÊ±âÈ­

	va_list ap;

	SetRect(&rc, x, y, 800, 600);

	va_start(ap, text);
	vsprintf_s(str, text, ap);
	va_end(ap);

	m_pFont->DrawTextA(NULL, str, -1, &rc, DT_LEFT, D3DCOLOR_XRGB(255, 0, 255));

}

void cFontManager::Destroy()
{
	m_pFont->Release();
}