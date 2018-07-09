#pragma once
#include "cSkill.h"

#define g_pSkillManager cSkillManager::GetInstance()

class cSkillManager
{
	SINGLETONE(cSkillManager);

private:
	std::map<std::string, cSkill*> m_mapSkill;

public:

	void Update();
	void Release();
	void Render();

	void AddSkill(std::string skillName, 
		SKILL_TYPE skillType, 
		float damage, 
		float range, 
		float posSpeed, 
		float cooldown, 
		float castingTime,
		float removeTime,
		bool isTarget);

	void Fire(std::string skillName,
		D3DXVECTOR3 playerPos,
		D3DXVECTOR3* tagetPos,
		float* currentTime);

	bool IsCasting();

};

