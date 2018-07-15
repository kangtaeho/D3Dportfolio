#include "stdafx.h"
#include "cSkillManager.h"
#include "cMeleeSkill.h"
#include "cRangeSkill.h"
#include "cObjectSkill.h"

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

	CancelSkill();		// 스킬 취소
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
			cObjectSkill* pObj = new cObjectSkill;
			pObj->Setup(skillType, damage, range, posSpeed, castingTime, cooldown, removeTime, isTarget, name);
			m_mapSkill.insert(std::make_pair(skillName, pObj));
		}

	}

}

void cSkillManager::Fire(std::string skillName,
	D3DXVECTOR3* playerPos,
	D3DXVECTOR3* tagetPos,
	bool isNormal)
{

	if (m_mapSkill.find(skillName) == m_mapSkill.end()) return;

	m_mapSkill[skillName]->Fire(playerPos, tagetPos, isNormal);

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

void cSkillManager::IsReady(std::string skillName)
{
	if (m_mapSkill.find(skillName) == m_mapSkill.end()) return;

	for (auto p : m_mapSkill)	// 다른 스킬이 하나라도 입력을 받았으면
	{
		if (p.second->GetIsReady())
		{
			return;
		}
	}

	// 여기까지 도달했다는건 모두 false라는 뜻

	m_mapSkill[skillName]->SetIsReady(true);

}

void cSkillManager::CancelSkill()
{
	if (g_pKeyManager->IsOnceKeyDown(VK_CLEAR))
	{
		for (auto p : m_mapSkill)	// 다른 스킬이 하나라도 입력을 받았으면
		{
			p.second->SetIsReady(false);
		}
	}
}
