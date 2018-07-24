#pragma once

class Bitmap;

#define g_pProgreesBar cHealthProgress::GetInstance()
class cHealthProgress
{
private:
	SINGLETONE(cHealthProgress);
	RECT  m_HpBarRect;
	RECT  m_MpBarRect;
	Bitmap* m_pContainer;
	Bitmap* m_pHpBar;
	Bitmap* m_pMpBar;

	float m_fHpBarSize;
	float m_fHpBarRight;
	float m_fHpBarBottom;
	float m_fHitvalue;
	
	float m_fMpBarSize;
	float m_fMpBarRight;
	float m_fMpBarBottom;
	float m_fUsedMpValue;

	SYNTHESIZE(float, m_fMaxHp, MaxHp);
	SYNTHESIZE(float, m_fCurrentHp, CurrentHp);
	SYNTHESIZE(float, m_fMaxMp, MaxMp);
	SYNTHESIZE(float, m_fCurrentMp, CurrentMp);
	SYNTHESIZE(bool, m_bCheckHpBarSize, HpBarSize);
	SYNTHESIZE(bool, m_bCheckHpHit, HpHit);
	SYNTHESIZE(bool, m_bCheckMpBarSize, MpBarSize);
	SYNTHESIZE(bool, m_bCheckMpUsed, MpUsed);
	
public:
	void setup();
	void setBarPosition(D3DXVECTOR3 HpPosition, D3DXVECTOR3 MpPosition);
	void update();
	void render();
	void Release();
};

