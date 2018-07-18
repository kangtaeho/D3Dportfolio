#pragma once
#include "cGameNode.h"

class cCharacter;

enum eMouseState
{
	MS_SETCIRCLE,
	MS_DELCIRCLE,
	MS_SETLINE
};

class cMapEditer : public cGameNode
{
private:
	STCIRCLE*						m_pNowCircle; 
	STCollisionMapTool				m_stMap;

	float							m_fRadius;

	eMouseState						m_eNowState;

	LPD3DXMESH						m_pMesh;
	D3DMATERIAL9					m_mtl;

	cCharacter*						m_pPlayer;

public:
	cMapEditer();
	~cMapEditer();

	HRESULT Setup();
	void Release();
	void Update();
	void Render();

	STCollisionMapTool* getCollisionMap() { return &m_stMap; }

	void Save();
	void Load();

	void Mtl(float R, float G, float B);
	D3DXVECTOR3 getRay();
	bool findCircle(D3DXVECTOR3 Ray, STCIRCLE** nowClick);
	void LineRender(STLINE* line);
	void deleteCircle(STCIRCLE* circle);
	bool getInMouse();
	bool isCircleInLine(STCIRCLE* circle);
};

