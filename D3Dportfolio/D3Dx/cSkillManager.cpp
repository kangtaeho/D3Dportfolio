#include "stdafx.h"
#include "cSkillManager.h"
#include "cMeleeSkill.h"
#include "cRangeSkill.h"

cSkillManager::cSkillManager()
{
}

cSkillManager::~cSkillManager()
{
}

void cSkillManager::Update()
{
	for (auto p : m_mapSkill)
	{
		p.second->Update();
	}
}

void cSkillManager::Release()
{
	for (auto p : m_mapSkill)
	{

		SAFE_RELEASE(p.second);
		SAFE_DELETE(p.second);
	}
}

void cSkillManager::Render()
{
	for (auto p : m_mapSkill)
	{
		p.second->Render();
	}
}

void cSkillManager::AddSkill(std::string skillName,
	SKILL_TYPE skillType,
	float damage,
	float range,
	float posSpeed,
	float castingTime,
	float cooldown,
	float removeTime,
	bool isTarget,
	const char* name)
{

	if (m_mapSkill.find(skillName) == m_mapSkill.end())
	{
		if (skillType == MELEE_SKILL)
		{
			cMeleeSkill* pMelee = new cMeleeSkill;
			pMelee->Setup(skillType, damage, range, posSpeed, castingTime, cooldown, removeTime, isTarget, name);
			m_mapSkill.insert(std::make_pair(skillName, pMelee));
		}
		else if (skillType == RANGE_SKILL)
		{
			cRangeSkill*pRange = new cRangeSkill;
			pRange->Setup(skillType, damage, range, posSpeed, castingTime, cooldown, removeTime, isTarget, name);
			m_mapSkill.insert(std::make_pair(skillName, pRange));
		}
		else if (skillType == OBJECT_SKILL)
		{

		}

	}

}

void cSkillManager::Fire(std::string skillName,
	D3DXVECTOR3* playerPos,
	D3DXVECTOR3* tagetPos,
	float* currentTime)
{

	if (m_mapSkill.find(skillName) == m_mapSkill.end()) return;

	m_mapSkill[skillName]->Fire(playerPos, tagetPos, currentTime);

}

bool cSkillManager::IsCasting()
{

	for (auto p : m_mapSkill)
	{

		if (p.second->GetIsCasting())
		{
			return true;
		}
		
	}

	return false;
}
