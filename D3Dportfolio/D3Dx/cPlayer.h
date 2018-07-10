#pragma once
#include "cCharacter.h"

class cSphere;

class cPlayer : public cCharacter
{
private:
	cSphere*		m_pSphere;
	bool			m_bIsTarget;
	float			m_fRange;

public:
	cPlayer();
	~cPlayer();

	virtual void Setup(const char* name);
	virtual void Release();
	virtual void Update();
	virtual void Render();

	void Check3DMousePointer();				// 마우스 체크


};

