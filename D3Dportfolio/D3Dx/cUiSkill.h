#pragma once
class cUiSkill
{
private:
	SYNTHESIZE(Bitmap*, SkillInfo, skillInfo)
	SYNTHESIZE(bool, hadChosen, Chosen);
	SYNTHESIZE(D3DXVECTOR3, m_vSkillPos, vSkillPos);
public:
	cUiSkill();
	~cUiSkill();

	void update();
	void render();
};

