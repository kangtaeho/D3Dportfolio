#pragma once
#include "cCharacter.h"

class cPlayer : public cCharacter
{
private:
	
public:
	cPlayer();
	~cPlayer();

	virtual void Setup(const char* name);
	virtual void Release();
	virtual void Update();
	virtual void Render();

	void Check3DMousePointer();				// 마우스 체크
	
};

