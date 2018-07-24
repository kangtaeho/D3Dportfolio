#pragma once
#include "cGameNode.h"
#include  "cMainUI.h"
class cPlayer;
class cShop;
class cStatus;
class cHealthProgress;

class cPlayScene : public cGameNode
{
private:
	cPlayer*		m_pPlayer;
	cShop* shop;
	cMainUI* m_pMainUi;
	cStatus* status;
	D3DXMATRIX WorldMatrix, matProj, matViewPort, matView;
	bool changed;

	std::vector<cHealthProgress*> m_vecHealthProgress;
	
public:
	cPlayScene();
	~cPlayScene();

	HRESULT Setup();
	void Release();
	void Update();
	void Render();

};

