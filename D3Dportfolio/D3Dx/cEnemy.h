#pragma once
#include "cCharacter.h"
#include "cSphere.h"

class cEnemy : public cCharacter
{
private:
	cSphere	tempSphere;

public:
	cEnemy();
	~cEnemy();

	virtual void Setup(const char* name);
	virtual void Release();
	virtual void Update();
	virtual void Render();

	cSphere* getSphere() { return &tempSphere; }
};

