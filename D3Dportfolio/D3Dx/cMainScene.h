#pragma once
#include "cGameNode.h"

class cShop;

class cMainScene : public cGameNode
{
private:
	cShop*		m_pshop;

public:
	cMainScene();
	~cMainScene();

	HRESULT Setup();
	void Update();
	void Render();
	void Release();

};

