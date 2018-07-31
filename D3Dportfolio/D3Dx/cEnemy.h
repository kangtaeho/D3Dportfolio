#pragma once
#include "cCharacter.h"

class cRangeSkill;

class cEnemy : public cCharacter
{
private:
	std::vector<int> m_vecGoLine;
	STCollisionMapTool m_stAllCircleLine;
	std::vector<cCharacter*>* m_vecAllEnemy;
	cCharacter* m_pEnemy;
	float m_fSite;

	bool m_bLive;

	cRangeSkill* m_pAttack;

	bool m_bAttack;

	SYNTHESIZE(bool, m_fBlue, Blue)

protected:
	LPD3DXMESH m_pSphere;
	STCIRCLE m_pCircle;

public:
	cEnemy();
	~cEnemy();

	virtual void Setup(const char* name, bool Blue);
	virtual void Release();
	virtual void Update();
	virtual void Render();

	LPD3DXMESH getSphere() { return m_pSphere; }
	STCIRCLE* getCirclePointer() { return &m_pCircle; }
	void setGoLine(std::vector<int> GoLine) { m_vecGoLine = GoLine; }
	void setCircleLine(STCollisionMapTool AllCircleLine) { m_stAllCircleLine = AllCircleLine; }
	void setEnemy(std::vector<cCharacter*>* vecAllEnemy) { m_vecAllEnemy = vecAllEnemy; }
	bool getLive() { return m_bLive; }
	void setEnemy(cCharacter* enemy) { m_pEnemy = enemy; }
};

