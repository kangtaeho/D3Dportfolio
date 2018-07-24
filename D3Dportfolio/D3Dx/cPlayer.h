#pragma once
#include "cCharacter.h"

class cSphere;

class cPlayer : public cCharacter
{
private:
	cSphere*		m_pSphere;
	D3DXVECTOR3		m_vClickPos;

public:
	cPlayer();
	~cPlayer();

	virtual void Setup(const char* name);
	virtual void Release();
	virtual void Update();
	virtual void Render();

	void Check3DMousePointer();				// ���콺 üũ
	void ClickEnemy(D3DXVECTOR3 pos, float radius);
	float ModifyRange();

};

