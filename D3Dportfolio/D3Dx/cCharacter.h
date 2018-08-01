#pragma once
#include "cAction.h"
#include "cAStar.h"

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

class cCharacter : public cAction
{
protected:
	LPCSKINNEDMESH					m_pSkinnedMesh;

	D3DXVECTOR3						m_vDirection;
	D3DXVECTOR3						m_vPosition;
	D3DXVECTOR3						m_vNextPosition;

	D3DXMATRIX						m_matWorld;
	D3DXMATRIX*						m_pMatScale;

	float							m_fRotY;
	float							m_fRange;
	D3DXVECTOR3*					m_pEnemyPos;
	cSkill*							m_pSkill;

	cAStar							m_AStar;

	CHARACTER_STATE					m_eState;
	cCharacter*						m_pEnemy;

	SYNTHESIZE(float, m_fSpeed, Speed);
	SYNTHESIZE(float, m_fRadius, Radius);
	SYNTHESIZE(bool, m_isLive, IsLive);
	
	SYNTHESIZE(float, m_fMAXHP, MAXHP);
	SYNTHESIZE(float, m_fMAXMP, MAXMP);
	SYNTHESIZE(float, m_fHP, HP);
	SYNTHESIZE(float, m_fMP, MP);
	SYNTHESIZE(float, m_fATK, ATK);
	SYNTHESIZE(float, m_fATKSpeed, ATKSpeed);
	SYNTHESIZE(float, m_fRegainHP, RegainHP);
	SYNTHESIZE(float, m_fRegainMP, RegainMP);
	SYNTHESIZE(float, m_fDEF, DEF);
	SYNTHESIZE(float, m_fMDEF, MDEF);

public:
	cCharacter();
	~cCharacter();
	//name에 이름만 넣으면 알아서 x파일로 불러옵니다~ /character/******.x로요~
	virtual void Setup(const char* name);
	virtual void Release();
	virtual void Update();
	virtual void Render();

	D3DXVECTOR3 getNextPosition() { return m_vNextPosition; }
	D3DXVECTOR3* getPositionPointer() { return &m_vPosition; }
	D3DXVECTOR3 getPosition() { return m_vPosition; }
	CHARACTER_STATE getState() { return m_eState; }
	void setEnemy(cCharacter* enemy) { m_pEnemy = enemy; }

};

