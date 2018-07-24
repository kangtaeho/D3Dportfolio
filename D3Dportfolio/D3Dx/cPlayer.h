#pragma once
#include "cCharacter.h"

class cSphere;
class cAStar;

class cPlayer : public cCharacter
{
private:
	cSphere*		m_pSphere;
	bool			m_bIsTarget;
	float			m_fRange;
	float			m_fRadius;

	D3DXVECTOR3		m_vClickPos;

	cAStar* aStar;

	bool isTrue;

public:
	cPlayer();
	~cPlayer();

	virtual void Setup(const char* name);
	virtual void Release();
	virtual void Update();
	virtual void Render();

	void Check3DMousePointer();				// 마우스 체크
	void ClickEnemy(D3DXVECTOR3 pos, float radius);

};

