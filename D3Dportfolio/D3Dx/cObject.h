#pragma once
#include "cCharacter.h"
#include "cSphere.h"


class cObject : public cCharacter
{
private:
	std::string m_sName;
	int m_bBlue;
	cAction m_pAction;
	cSphere	tempSphere;
	STCIRCLE m_pCircle;
	SYNTHESIZE(float, m_fScale, Scale);

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
	cSphere* getSphere() { return &tempSphere; }
	STCIRCLE* getCirclePointer() { return &m_pCircle; }
};

