#pragma once
#include "cCharacter.h"

class cSphere;
class cEnemy;

class cPlayer : public cCharacter
{
private:
	cSphere*		m_pSphere;
	D3DXVECTOR3		m_vClickPos;

	cEnemy*			m_pEnemy;

public:
	cPlayer();
	~cPlayer();

	virtual void Setup(const char* name);
	virtual void Release();
	virtual void Update();
	virtual void Render();

	void Check3DMousePointer();				// 마우스 체크
	void AttackEnemy(cEnemy* enemy);

};

