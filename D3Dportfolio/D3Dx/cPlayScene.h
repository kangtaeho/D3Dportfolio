#pragma once
#include "cGameNode.h"

class cPlayer;
class cCollisionMap;

class cPlayScene : public cGameNode
{
private:
	cPlayer*		m_pPlayer;
	cCollisionMap*  colMap;

public:
	cPlayScene();
	~cPlayScene();

	HRESULT Setup();
	void Release();
	void Update();
	void Render();

};

