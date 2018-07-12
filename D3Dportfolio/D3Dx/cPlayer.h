#pragma once
#include "cCharacter.h"

class cSphere;

class cPlayer : public cCharacter
{
private:
	cSphere*		m_pSphere;
	bool			m_bIsTarget;
	float			m_fRange;

	D3DXVECTOR3		m_vClickPos;

public:
	cPlayer();
	~cPlayer();

	virtual void Setup(const char* name);
	virtual void Release();
	virtual void Update();
	virtual void Render();

	void Check3DMousePointer();				// 마우스 체크


};

