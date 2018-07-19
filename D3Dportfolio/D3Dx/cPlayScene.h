#pragma once
#include "cGameNode.h"
#include  "cMainUI.h"
class cPlayer;
class cCollisionMap;
class cShop;
class cStatus;

class cPlayScene : public cGameNode
{
private:
	cPlayer*		m_pPlayer;
	cCollisionMap*  colMap;
	cShop* shop;
	cMainUI* m_pMainUi;
	cStatus* status;
	D3DXMATRIX WorldMatrix, matProj, matViewPort, matView;
	bool changed;
public:
	cPlayScene();
	~cPlayScene();

	HRESULT Setup();
	void Release();
	void Update();
	void Render();

};

