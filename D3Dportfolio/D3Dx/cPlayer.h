#pragma once
#include "cCharacter.h"

class cSphere;
class cEnemy;
class cShop;
class cHealthProgress;

class cPlayer : public cCharacter
{
private:
	D3DXVECTOR3         m_vSavePos;
	D3DXVECTOR3			m_vClickPos;
	cEnemy*				m_pEnemy;
	cShop*				m_pShop;

	LPD3DXMESH			m_pTargetMesh;
	cHealthProgress*    m_pTelePortProgress;
	std::vector<cCharacter*>* m_pVecEnemy;
	float m_fRespwan;
	float m_fMaxTelePortTime;
	float m_fTelePortTime;
	float m_fTime;
	bool m_bProgressing;

	SYNTHESIZE(bool, m_bTelePort, TelePort);
	SYNTHESIZE(bool, isClickUi, IsClickUI);

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
