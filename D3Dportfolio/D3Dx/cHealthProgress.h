#pragma once

class Bitmap;

class cHealthProgress
{
private:
	RECT  m_HpBarRect;
	RECT  m_MpBarRect;

	float PrevHpSize;
	float PrevMpSize;
	float m_fHpBarSize;
	float m_fHpBarRight;
	float m_fHpBarBottom;
	
	float m_fMpBarSize;
	float m_fMpBarRight;
	float m_fMpBarBottom;


	SYNTHESIZE(bool, ReCorrectSize, ReCorret);



	SYNTHESIZE(Bitmap*, m_pContainer, Container);
	SYNTHESIZE(float, m_fHitvalue, HitValue);
	SYNTHESIZE(Bitmap*, m_pHpBar, HpBar);
	SYNTHESIZE(Bitmap*, m_pMpBar, MpBar);
	SYNTHESIZE(float, m_fMaxHp, MaxHp);
	SYNTHESIZE(float, m_fCurrentHp, CurrentHp);
	SYNTHESIZE(float, m_fMaxMp, MaxMp);
	SYNTHESIZE(float, m_fCurrentMp, CurrentMp);
	SYNTHESIZE(bool, m_bCheckHpBarSize, HpBarSize);
	
	SYNTHESIZE(bool, m_bCheckMpBarSize, MpBarSize);
	SYNTHESIZE(float, m_fUsedMpValue, MpUsed);
	
public:
	cHealthProgress();
	~cHealthProgress();

	void setup();
	void setBarPosition(D3DXVECTOR3 HpPosition, D3DXVECTOR3 MpPosition);
	void update();
	void render();
	void Release();
};

