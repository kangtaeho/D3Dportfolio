#pragma once
#include "cCharacter.h"

class cSphere;
class cEnemy;
class cShop;

class cPlayer : public cCharacter
{
private:
	cSphere * m_pSphere;
	D3DXVECTOR3      m_vClickPos;

	cEnemy*         m_pEnemy;
	cShop*         m_pShop;

	SYNTHESIZE(bool, isClickUi, IsClickUI);

	std::vector<cCharacter*>* m_pVecEnemy;

	// 테스트용 벡터
	std::vector<cCharacter*> m_vecEnemy;

	float m_fRespwan;

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
};
