#pragma once

class Bitmap;

#define g_pProgreesBar cHealthProgress::GetInstance()
class cHealthProgress
{
private:
	SINGLETONE(cHealthProgress);
	RECT  m_BarRect;

	Bitmap* m_pContainer;
	Bitmap* m_pHpBar;
	Bitmap* m_pMpBar;

	float m_fBarSize;
	float m_fBarRight;
	float m_fBarBottom;
	float m_fCurrentHp;
	float m_fHitvalue;
	
	SYNTHESIZE(float, m_fMaxHp, MaxHp);
	SYNTHESIZE(float, m_fMaxMp, MaxMp);
	SYNTHESIZE(bool, m_bCheckBarSize, BarSize);
	SYNTHESIZE(bool, m_bCheckHit, Hit);
	
public:
	void setup();
	void setBarPosition(D3DXVECTOR3 HpPosition, D3DXVECTOR3 MpPosition);
	void update();
	void render();
	void Release();
};

