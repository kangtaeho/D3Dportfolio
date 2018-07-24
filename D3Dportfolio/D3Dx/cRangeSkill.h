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
		float castingTime,
		float cooldown,
		float removeTime,
		bool isTarget,
		const char* name);

	virtual void	Release();
	virtual void	Update();
	virtual void	Render();

};

