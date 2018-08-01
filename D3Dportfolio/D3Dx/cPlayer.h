#pragma once
#include "cCharacter.h"

class cSphere;
class cEnemy;
class cShop;
class cAshe;

class cPlayer : public cCharacter
{
private:

	D3DXVECTOR3			m_vClickPos;
	cCharacter*			m_pEnemy;
	cShop*				m_pShop;

	LPD3DXMESH			m_pTargetMesh;

	std::vector<cCharacter*>* m_pVecEnemy;
	float m_fRespwan;

	SYNTHESIZE(bool, isClickUi, IsClickUI);
	SYNTHESIZE(cAshe*, m_pAshe, Ashe);

public:
	cPlayer();
	~cPlayer();

	virtual void Setup(const char* name);
	virtual void Release();
	virtual void Update();
	virtual void Render();

	void Check3DMousePointer();            // 마우스 체크
	void AttackEnemy(cCharacter* enemy);

	void SetVecEnemy(std::vector<cCharacter*>* vecEnemy) { m_pVecEnemy = vecEnemy; }
	void SkillRegisterTarget(){ g_pSkillManager->RegisterVecEnemy(m_pVecEnemy); }

	void CreateTargetMesh();
	void ClickTargetRender();

};
