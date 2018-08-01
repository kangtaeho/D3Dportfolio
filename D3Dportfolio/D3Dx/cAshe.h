#pragma once
#include "cCharacter.h"

class cHealthProgress;
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
	cHealthProgress * m_pProgressBar;
	LPD3DXMESH m_pSphere;

	cRangeSkill* m_pAttack;
	
	std::vector<cCharacter*>*	m_vecAllEnemy;
	std::vector<AI_POS>			m_vecPosAI;

	cCharacter*					m_pEnemy;

	AI_POS						m_sMovePos;
	AI_POS						m_sBackPos;
	AI_POS						m_sStartPos;


	D3DXVECTOR3					m_vStartPos;

	AI_TYPE						m_eAIState;

	float						m_fSite;
	float						m_fPassedTime;
	bool						m_bIsDead;
	bool						m_bIsDanger;
	bool						m_bIsFire;

	float						m_fNowHP;
	float						m_fDangerTime;

public:
	cAshe();
	~cAshe();

	virtual void Setup(const char* name);
	virtual void Release();
	virtual void Update();
	virtual void Render();

	void ChangePos();
	void ControlAI();
	void RespawnAshe();

	LPD3DXMESH getSphere() { return m_pSphere; }
	void SetVecEnemey(std::vector<cCharacter*>* enemy) { m_vecAllEnemy = enemy; }

	void DangerTime();
	void BackAshe();
};

