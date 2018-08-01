#pragma once
#include "cCharacter.h"

enum AI_TYPE
{
	AI_PATROL,	// Å½Áö
	AI_ATTACK,  // °ø°Ý
	AI_DANGER,  // À§Çù
};

class cRangeSkill;

struct AI_POS
{
	D3DXVECTOR3 pos[2];
	int index;
	bool isChange;
};

class cAshe : public cCharacter
{
private:

	cRangeSkill* m_pAttack;
	
	std::vector<cCharacter*>* m_vecAllEnemy;
	std::vector<AI_POS> m_vecPosAI;

	AI_POS m_sMovePos;
	D3DXVECTOR3 m_vStartPos;

public:
	cAshe();
	~cAshe();

	virtual void Setup(const char* name);
	virtual void Release();
	virtual void Update();
	virtual void Render();

	void ChangePos();

};

