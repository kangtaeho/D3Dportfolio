#pragma once
#include "cSkill.h"

class cMeleeSkill :
	public cSkill
{
public:
	cMeleeSkill();
	virtual ~cMeleeSkill();

	virtual HRESULT Setup(
		SKILL_TYPE skillType,
		float damage,
		float range,
		float posSpeed,
		float cooldown,
		float removeTime,
		bool isTarget);

	virtual void	Release();
	virtual void	Update();
	virtual void	Render();

};

