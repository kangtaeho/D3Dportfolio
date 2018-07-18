#pragma once
#include "cGameNode.h"

class Bitmap;

class cSelectScene :
	public cGameNode
{
private:
	Bitmap* m_pMainSelectWin;	 // 큰 창
	Bitmap* m_pPlayerSelect;	 // 플레이어 창
	Bitmap* m_pPlayerChamp;		 // 플레이어 챔프 창
	Bitmap* m_pEnemyChamp;		 // 적 챔프 창
	Bitmap* m_pSelect;			 // 선택 태두리 창
	Bitmap* m_pPickIn;			 // 픽인 버튼
	Bitmap* m_pSkin;			 // 스킨창

	RECT rc_Select[10];			 // 챔피언 클릭 판정 렉트
	RECT rc_PickIn;
	std::vector<Bitmap*>	m_vecIcon;

	int m_nPickIndex;
	bool m_bIsLockIn;

public:
	cSelectScene();
	~cSelectScene();

	HRESULT Setup();
	void Update();
	void Render();
	void Release();

	void Control();

};

