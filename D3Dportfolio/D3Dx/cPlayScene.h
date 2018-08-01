#pragma once
#include "cGameNode.h"
#include  "cMainUI.h"

class cPlayer;
class cAshe;
class cShop;
class cStatus;
class cHealthProgress;
class cMinimap;
class cObjectManager;


class cPlayScene : public cGameNode
{
private:
	cPlayer*		m_pPlayer;
	cShop* shop;
	cMainUI* m_pMainUi;
	cStatus* status;
	cMinimap* m_pMinimap;
	cObjectManager* m_pEnemyManager;
	D3DXMATRIX WorldMatrix, matProj, matViewPort, matView;
	bool changed;

	std::vector<cHealthProgress*> m_vecHealthProgress;
	
	bool isOpen;

	cAshe* m_pAshe;

	bool isKill;

public:
	cPlayScene();
	~cPlayScene();

	HRESULT Setup();
	void Release();
	void Update();
	void Render();

};

