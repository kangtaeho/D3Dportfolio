#pragma once
#include "cEnemy.h"

class cHealthProgress;
class cObject : public cEnemy
{
private:
	std::string m_sName;
	int m_bBlue;
	cAction m_pAction;
	D3DXVECTOR3 m_vFirePosition;
	SYNTHESIZE(float, m_fScale, Scale);
	cHealthProgress* m_pObjectProgressBar;
public:
	cObject();
	~cObject();

	void Setup(const char * name, int BlueTeam, float scale);
	void Release();
	void Update();
	void Render();

	std::string getName() { return m_sName; }
	int getBlue() { return m_bBlue; }
	float getRotY() { return m_fRotY; }
	void SetRotY(float rotY) { m_fRotY = rotY; }
};

