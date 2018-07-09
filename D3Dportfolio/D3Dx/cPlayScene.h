#pragma once
#include "cGameNode.h"

class cPlayer;


class cPlayScene : public cGameNode
{
private:
	cPlayer*		m_pPlayer;

public:
	cPlayScene();
	~cPlayScene();

	HRESULT Setup();
	void Release();
	void Update();
	void Render();

};

