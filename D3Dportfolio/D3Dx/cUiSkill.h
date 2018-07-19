#pragma once
class cUiSkill
{
private:
	SYNTHESIZE_REF(Bitmap*, SkillInfo, skillInfo)
	SYNTHESIZE(bool, hadChosen, Chosen);
	SYNTHESIZE(D3DXVECTOR3, m_vSkillPos, vSkillPos);
public:
	cUiSkill();
	~cUiSkill();

	void update();
	void render();
};

