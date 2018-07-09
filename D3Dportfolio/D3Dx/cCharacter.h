#pragma once

enum CHARACTER_STATE
{
	DEAD,
	IDLE,
	RUN,
	ATTACK,
	SKILL1,
	SKILL2,
	SKILL3,
	SKILL4
};

class cCharacter
{
protected:
	std::string						m_sName;
	D3DXVECTOR3						m_vDirection;
	D3DXVECTOR3						m_vPosition;
	D3DXVECTOR3						m_vNextPosition;
	float							m_fRotY;
	float							m_fSpeed;

	std::vector<D3DXVECTOR3>*		m_pMap;
	std::vector<stCollisionMap>*	m_pCollisionMap;
	cSkill*							m_pSkill;


public:
	cCharacter();
	~cCharacter();
	//name에 이름만 넣으면 알아서 x파일로 불러옵니다~ /character/******.x로요~
	virtual void Setup(const char* name);
	virtual void Release();
	virtual void Update();
	virtual void Render();

	void setCollisionMap(std::vector<stCollisionMap>* pCollisionMap) { m_pCollisionMap = pCollisionMap; }
	void setMap(std::vector<D3DXVECTOR3>* pMap) { m_pMap = pMap; }
	bool GetHeight(float& x, float & y, float& z);
	bool GetCollision(float& x, float & y, float& z);

};

