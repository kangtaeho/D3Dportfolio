#pragma once
#include "cGameNode.h"
#include  "cMainUI.h"
class cPlayer;
class cCollisionMap;

class cPlayScene : public cGameNode
{
private:
	cPlayer*		m_pPlayer;
	cCollisionMap*  colMap;

	cMainUI* m_pMainUi;
public:
	cPlayScene();
	~cPlayScene();

	HRESULT Setup();
	void Release();
	void Update();
	void Render();

};

