#pragma once

class cUIButton;

class iButtonDelegate
{
public:
	virtual void OnClick(cUIButton* pSender) = 0;
};

class cUIButton
{
protected:
	ST_UI_SIZE m_stSize;

	enum eButtonState
	{
		BT_UP,
		BT_OVER,
		BT_DOWN,
		BT_STATE_COUNT
	};

	LPDIRECT3DTEXTURE9 m_arrTexture[BT_STATE_COUNT];
	eButtonState	   m_buttonState;

	iButtonDelegate*   m_pDelegate;

	D3DXMATRIX*		   m_matWorld;
	LPD3DXSPRITE	   m_pSprite;
	const char* szTemp;
public:
	cUIButton();
	~cUIButton();

	void setTexture(const char* szUp, const char* szOver, const char* szDown);
	void update();
	void Render();
	void setPosition(D3DXVECTOR3 vPosition);
	void setScale(D3DXVECTOR3 vScale);
	int GetButttonState() { return m_buttonState; }
};