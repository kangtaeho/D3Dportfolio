#pragma once

class cCube;

enum SKILL_TYPE
{
	MELEE_SKILL,
	RANGE_SKILL,
	OBJECT_SKILL,
	TYPE_COUNT
};

class cSkill
{
protected:

	SKILL_TYPE			e_skillType;		// 어떤 스킬일 것이냐,
	
	D3DXMATRIX			m_matWorld;
	D3DXVECTOR3			m_vPos;				// 미사일 위치
	D3DXVECTOR3*		m_pPlayerPos;		// 플레이어 위치
	D3DXVECTOR3*		m_pTargetPos;		// 타겟위치
	D3DXVECTOR3			m_vDir;				// 방향벡터

	std::string			m_sObjectName;		// 오브젝트 이름

	int					m_nLevel;			// 스킬레벨

	float				m_fRotY;
	float				m_fRotX;			

	float				m_fDamage;
	float				m_fRange;			// 타겟범위
	float				m_fPosSpeed;		// 포스 스피드

	float				m_fCooldown;		// 쿨다운
	float				m_fCurrentCooldown;	// 현제 쿨다운시간
	float				m_fCastingTime;		// 시전 시간
	float				m_fStartTime;		// 스킬 시작시간,
	float*				m_pCurrentTime;		// 현제 시간

	float				m_fPassedTime;		// 경과시간.
	float				m_fRemoveTime;		// 삭제할 시간(오브젝트용)

	SYNTHESIZE(bool, m_bIsCasting, IsCasting);
	//bool				m_bIsCasting;		// 시전했냐?
	bool				m_bIsCooldown;		// 쿨타임끝났냐?
	bool				m_bIsTarget;		// 타겟팅이냐?
	bool				m_bIsRemove;		// 오브젝트 삭제할꺼냐.

	bool				m_bIsAutoFire;			// 범위안에 있냐?


	// 오브젝트
	LPCSKINNEDMESH		m_pMesh;

	// 테스트용 큐브
	cCube*				m_pCube;

public:
	cSkill();
	virtual ~cSkill();

	virtual HRESULT Setup(SKILL_TYPE skillType,
						float damage,
						float range,
						float posSpeed,
						float cooldown,
						float removeTime,
						bool isTarget);

	virtual void	Release();
	virtual void	Update();
	virtual void	Render();

	void Fire(D3DXVECTOR3* playerPos,
			D3DXVECTOR3* tagetPos, 
			float* currentTIme = NULL);

	void Move();
	void Casting();
	void CoolDownSetup();				// 쿨다운

	void CastingSkill(SKILL_TYPE skillType);

	void RemoveTime();					// 시간에 따른 스킬 끝내기
	void RemoveRange();					// 범위에 따른 스킬 끝내기
	void RemoveTarget();				// 타겟일때 오브젝트 삭제

	void AutoFire();

	// 일단테스트용 큐브
	void CreateCube();
	void RenderCube();



};

