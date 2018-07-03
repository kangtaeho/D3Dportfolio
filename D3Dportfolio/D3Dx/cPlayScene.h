#pragma once
#include "cGameNode.h"

class cPlayScene : public cGameNode
{
public:
	cPlayScene();
	~cPlayScene();

	HRESULT Setup();
	void Release();
	void Update();
	void Render();

};

