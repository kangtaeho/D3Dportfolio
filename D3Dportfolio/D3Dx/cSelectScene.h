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

	RECT rc_Select[10];			 // 챔피언 클릭 판정 렉트

public:
	cSelectScene();
	~cSelectScene();

	HRESULT Setup();
	void Update();
	void Render();
	void Release();
};

