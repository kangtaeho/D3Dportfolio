#pragma once

#define g_pFontManager cFontManager::GetInstance()

class cFontManager
{
	SINGLETONE(cFontManager);

public:

	LPD3DXFONT		m_pFont;

	SYNTHESIZE(bool, m_bIsSetup, IsSetup);

	void Setup();
	void TextFont(int x, int y, D3DXVECTOR3 color, const char* text, ...);
	void Destroy();

};

