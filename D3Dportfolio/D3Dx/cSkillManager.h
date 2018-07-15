#pragma once
#include "cSkill.h"

#define g_pSkillManager cSkillManager::GetInstance()

class cSkillManager
{
	SINGLETONE(cSkillManager);

private:
	std::map<std::string, cSkill*>  m_mapSkill;

public:
	void Update();
	void Release();
	void Render();

	void AddSkill(std::string skillName,
		SKILL_TYPE skillType,
		float damage,
		float range,
		float posSpeed,
		float castingTime,
		float cooldown,
		float removeTime,
		bool isTarget,
		const char* name = NULL);

	void Fire(std::string skillName,
		D3DXVECTOR3* playerPos,
		D3DXVECTOR3* tagetPos,
		bool isNormal=true);	// 노말일 경우엔 평타로 생각함(즉 Ready를 거치지 않음)

	bool IsCasting();
	
	void IsReady(std::string skillName);
	bool CheckReady();			// 레디 상태인지 체크한다.
	void CancelSkill();

};

