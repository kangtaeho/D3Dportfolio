#pragma once
#include "cAction.h"

class cCube;
class cSkinnedMesh;
class cPlayer;
class cCharacter;
class cDamageRender;

enum SKILL_TYPE
{
	MELEE_SKILL,
	RANGE_SKILL,
	OBJECT_SKILL,
	BUFF_SKILL,
	TOXIC_SKILL,
	SKILL_TYPE_COUNT
};

enum BUFF_TYPE
{
	MOVEUP,
	DAMAGEUP,
	BUFF_TYPE_COUNT
};

struct OBJECT_MESH
{
	D3DXVECTOR3	pos;
	D3DXVECTOR3	target;
	float		removeTime;
	float		startTime;
	bool		isAttack;
	cAction*	animation;
	OBJECT_MESH() { animation = new cAction; }
};

struct TOXIC_ENEMY
{
	float removeTime;
	float countTime;
	float startTime;
	cCharacter* enemy;
};

struct AOE_MESH
{
	LPD3DXMESH	aoeMesh;
	float		aoeScale;

	LPD3DXMESH pointMesh;
	float	   pointScale;
};

class cSkill : public cAction	// 부모에서 받는 애니메이션은 원본임(사실 잘 모르겟음)
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

	
	float				m_fRange;			// 타겟범위
	float				m_fPosSpeed;		// 포스 스피드

	float				m_fCooldown;		// 쿨다운
	float				m_fCurrentCooldown;	// 현제 쿨다운시간
	float				m_fCastingTime;		// 시전 시간
	float				m_fStartTime;		// 스킬 시작시간,
	float*				m_pCurrentTime;		// 현제 시간

	float				m_fPassedTime;		// 경과시간.
	float				m_fRemoveTime;		// 삭제할 시간(오브젝트용)

	bool				m_bIsTarget;		// 타겟팅이냐?
	bool				m_bIsRemove;		// 오브젝트 삭제할꺼냐.

	bool				m_bIsAutoFire;			// 범위안에 있냐?

	bool				m_isUsingSkill;
	bool				m_bIsFire;

	BUFF_TYPE e_BuffType;

	// 오브젝트
	cSkinnedMesh*		m_pMesh;
	cCube*				m_pCube;

	std::vector<OBJECT_MESH> m_vecMesh;

	AOE_MESH*			s_AoeMesh;

	// 독데미지 판정
	std::vector<TOXIC_ENEMY> m_vecToxic;
	cCharacter* m_pTargetEnemy;

	cDamageRender*		m_pDamageRender;

	SYNTHESIZE(bool, m_bIsReady, IsReady); // 스킬 사용 준비가 되었냐?
	SYNTHESIZE(cPlayer*, m_pPlayer, Player);		// 버프를 생각을 못함,,, 구조 ㅄ됨
	SYNTHESIZE(bool, m_bIsCasting, IsCasting);
	SYNTHESIZE(bool, m_bIsCooldown, IsCooldown);// 쿨타임끝났냐?
	SYNTHESIZE(std::vector<cCharacter*>*, m_pVecEnemy, VecEnemyPointer);
	SYNTHESIZE(float, m_fDamage, Damage);
	SYNTHESIZE(bool, m_bIsKill, IsKill);

public:
	cSkill();
	virtual ~cSkill();

	virtual HRESULT Setup(SKILL_TYPE skillType,
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

	void Fire(D3DXVECTOR3* playerPos,
		D3DXVECTOR3* tagetPos,
		cCharacter* targetEnemy,
			bool isNormal);

	void Move();
	void MeshMove();					// 매쉬 이동
	void Casting();
	void CoolDownSetup();				// 쿨다운

	void RemoveCubeTime();				// 시간에 따른 스킬 끝내기
	void RemoveRange();					// 범위에 따른 스킬 끝내기
	void RemoveTarget();				// 타겟일때 오브젝트 삭제
	void RemoveMeshTime();

	void AutoFire();

	// 일단테스트용 큐브
	void RenderCube();

	void CreateMesh();
	void RenderVecMesh();

	bool CollisionMesh(D3DXVECTOR3 enemyPos);		// 경훈이형 나중에 적이랑 충돌용으로 만들어놓음 (버섯이랑 적이랑 거리판정해서 충돌이면 true 아니면 false 반환)

	float GetCoolDown() { return m_fCurrentCooldown; }
	// 버프용 함수
	void BuffStart();
	void BuffEnd();
	void ReadyIsCasting();

	void SetBuffType(BUFF_TYPE buffType) { e_BuffType = buffType; }
	int CooldownTimer();

	void CreateAOEMesh(bool isCreatePointMesh, float pointScale);
	void DestroyAOEMesh();
	void RenderAOEMesh();

	bool IsUsingSkill();

	// 독데미지
	void AddToxicEnemy(cCharacter* enemy);
	void DamagedToxic();

	void SetVecEnemy(std::vector<cCharacter*>* pVecEnemy) { m_pVecEnemy = pVecEnemy; }

	void SetDamageRender(std::string texName);
	void UpdateDamageRender();
	void RenderDR();

};