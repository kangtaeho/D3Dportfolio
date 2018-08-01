#pragma once
#include "cCharacter.h"

enum AI_TYPE
{
	AI_PATROL,	// Ž��
	AI_ATTACK,  // ����
	AI_DANGER,  // ����
};

class cRangeSkill;

class cAshe : public cCharacter
{
private:

	cRangeSkill* m_pAttack;
	D3DXVECTOR3	 m_vCurrentPos;
	
	std::vector<cCharacter*>* m_vecAllEnemy;
	std::vector<D3DXVECTOR3> m_vecPosAI;

public:
	cAshe();
	~cAshe();

	virtual void Setup(const char* name);
	virtual void Release();
	virtual void Update();
	virtual void Render();

};

