#pragma once
#include "cCharacter.h"

class cPlayer : public cCharacter
{
private:
	
public:
	cPlayer();
	~cPlayer();

	virtual void Setup();
	virtual void Release();
	virtual void Update();
	virtual void Render();

};

