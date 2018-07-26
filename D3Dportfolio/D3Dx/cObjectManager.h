#pragma once

class cObject;
class cCharacter;

class cObjectManager
{
private:
	std::vector<cCharacter*> m_vecObject;
	std::vector<cCharacter*> m_vecMinion;
	std::vector<cCharacter*> m_vecAllBlue;
	std::vector<cCharacter*> m_vecAllEnemy;
	std::vector<STCIRCLE*> m_vecALLObjectCircle;

	STCollisionMapTool		m_stMinionLine;

	std::vector<int>	m_vecMinionLineIndex[3];

	float MinionTimeCount;

public:
	cObjectManager();
	~cObjectManager();

	void Setup();
	void Release();
	void Update();
	void Render();

	std::vector<cCharacter*>* getAllEnemy() { return &m_vecAllEnemy; }
};

