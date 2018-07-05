#pragma once
#include "cSkill.h"
class cRangeSkill :
	public cSkill
{
public:
	cRangeSkill();
	~cRangeSkill();

	virtual HRESULT Setup(
		SKILL_TYPE skillType,
		float damage,
		float range,
		float posSpeed,
		float cooldown,
		float castingTime,
		float removeTime,
		bool isTarget);

	virtual void	Release();
	virtual void	Update();
	virtual void	Render();
};

