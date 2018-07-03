#pragma once
#include "cGameNode.h"

class cCube;
class cShop;

class cMainScene : public cGameNode
{
private:
	cCube *		m_pCube;
	cShop*		m_pshop;

public:
	cMainScene();
	~cMainScene();

	HRESULT Setup();
	void Update();
	void Render();
	void Release();

};

