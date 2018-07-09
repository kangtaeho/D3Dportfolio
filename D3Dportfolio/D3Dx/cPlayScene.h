#pragma once
#include "cGameNode.h"

class cPlayer;
class cTestPlay;

class cPlayScene : public cGameNode
{
private:
	cPlayer*		m_pPlayer;
	cTestPlay*		m_pTestPlay;

public:
	cPlayScene();
	~cPlayScene();

	HRESULT Setup();
	void Release();
	void Update();
	void Render();

};

