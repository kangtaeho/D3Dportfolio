#pragma once
class cUiSkill
{
private:
	SYNTHESIZE_REF(Bitmap*, SkillInfo, skillInfo)
	SYNTHESIZE(bool, hadChosen, Chosen);
	SYNTHESIZE(D3DXVECTOR3, m_vSkillPos, vSkillPos);
	SYNTHESIZE(std::string, skillName, Name);
	SYNTHESIZE(bool, UsingSkill, Using);
public:
	cUiSkill();
	~cUiSkill();

	void update();
	void render();
};

