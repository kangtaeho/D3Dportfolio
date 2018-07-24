#pragma once
#include "cCharacter.h"

class cEnemy : public cCharacter
{
public:
	cEnemy();
	~cEnemy();

	virtual void Setup(const char* name);
	virtual void Release();
	virtual void Update();
	virtual void Render();

};

