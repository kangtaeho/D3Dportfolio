#pragma once

class cObject;
class cCharacter;

class cObjectManager
{
private:
	std::vector<cCharacter*> m_vecObject;
	std::vector<cCharacter*> m_vecAllEnemy;

public:
	cObjectManager();
	~cObjectManager();

	void Setup();
	void Release();
	void Update();
	void Render();

	std::vector<cCharacter*>* getAllEnemy() { return &m_vecAllEnemy; }
};

