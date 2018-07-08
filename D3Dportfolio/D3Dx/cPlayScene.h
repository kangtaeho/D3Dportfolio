#pragma once
#include "cGameNode.h"

class cPlayer;
class cController;

class cPlayScene : public cGameNode
{
private:
	cPlayer* m_pPlayer;
	cController* m_pController;

public:
	cPlayScene();
	~cPlayScene();

	HRESULT Setup();
	void Release();
	void Update();
	void Render();

};

