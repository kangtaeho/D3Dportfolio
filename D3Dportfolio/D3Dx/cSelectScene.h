#pragma once
#include "cGameNode.h"

class Bitmap;

class cSelectScene :
	public cGameNode
{
private:
	Bitmap* m_pMainSelectWin;	 // ū â
	Bitmap* m_pPlayerSelect;	 // �÷��̾� â
	Bitmap* m_pPlayerChamp;		 // �÷��̾� è�� â
	Bitmap* m_pEnemyChamp;		 // �� è�� â
	Bitmap* m_pSelect;			 // ���� �µθ� â
	Bitmap* m_pPickIn;			 // ���� ��ư
	Bitmap* m_pSkin;			 // ��Ųâ

	RECT rc_Select[10];			 // è�Ǿ� Ŭ�� ���� ��Ʈ
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

