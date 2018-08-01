#pragma once
#include "cCharacter.h"

class cRangeSkill;
class cHealthProgress;

class cEnemy : public cCharacter
{
private:
	std::vector<int> m_vecGoLine;
	STCollisionMapTool m_stAllCircleLine;
	cHealthProgress* m_pProgressBar;
	bool m_bLive;


	bool m_bAttack;

	SYNTHESIZE(bool, m_fBlue, Blue)

protected:
	LPD3DXMESH m_pSphere;
	STCIRCLE m_pCircle;
	std::vector<cCharacter*>* m_vecAllEnemy;
	cRangeSkill* m_pAttack;
	float m_fSite;

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
};

