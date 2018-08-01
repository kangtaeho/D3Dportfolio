#pragma once

class cObject;
class cCharacter;
class cPlayer;

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
	cPlayer* m_pPlayer;

	float MinionTimeCount;

public:
	cObjectManager();
	~cObjectManager();

	void Setup();
	void Release();
	void Update();
	void Render();

	std::vector<cCharacter*>* getAllEnemy() { return &m_vecAllEnemy; }
	std::vector<cCharacter*>* getAllBlue() { return &m_vecAllBlue; }

	void setLinkPlayer(cPlayer* player) { m_pPlayer = player; }
	bool getNexusLiving(bool Blue);
};

