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
		bool isNormal=true);	// �븻�� ��쿣 ��Ÿ�� ������(�� Ready�� ��ġ�� ����)

	bool IsCasting();
	
	void IsReady(std::string skillName);
	bool CheckReady();			// ���� �������� üũ�Ѵ�.
	void CancelSkill();

};

