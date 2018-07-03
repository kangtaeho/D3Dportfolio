#pragma once
#include "cGameNode.h"

class cMainGame  :public cGameNode
{
private:

public:
	cMainGame();
	virtual ~cMainGame();

	virtual HRESULT Setup();
	virtual void Update();
	virtual void Render();
	virtual void Release();

	void addSprite();

};

