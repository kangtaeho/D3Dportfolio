#pragma once
#include "cAction.h"

class cCube;
class cSkinnedMesh;
class cPlayer;

enum SKILL_TYPE
{
	MELEE_SKILL,
	RANGE_SKILL,
	OBJECT_SKILL,
	BUFF_SKILL,
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
	bool		isAttack;
	cAction*	animation;
	OBJECT_MESH() { animation = new cAction; }
};

struct AOE_MESH
{
	LPD3DXMESH	aoeMesh;
	float		aoeScale;

	LPD3DXMESH pointMesh;
	float	   pointScale;
};

class cSkill : public cAction	// �θ𿡼� �޴� �ִϸ��̼��� ������(��� �� �𸣰���)
{
protected:

	SKILL_TYPE			e_skillType;		// � ��ų�� ���̳�,
	
	D3DXMATRIX			m_matWorld;
	D3DXVECTOR3			m_vPos;				// �̻��� ��ġ
	D3DXVECTOR3*		m_pPlayerPos;		// �÷��̾� ��ġ
	D3DXVECTOR3*		m_pTargetPos;		// Ÿ����ġ
	D3DXVECTOR3			m_vDir;				// ���⺤��

	std::string			m_sObjectName;		// ������Ʈ �̸�

	int					m_nLevel;			// ��ų����

	float				m_fRotY;
	float				m_fRotX;			

	float				m_fDamage;
	float				m_fRange;			// Ÿ�ٹ���
	float				m_fPosSpeed;		// ���� ���ǵ�

	float				m_fCooldown;		// ��ٿ�
	float				m_fCurrentCooldown;	// ���� ��ٿ�ð�
	float				m_fCastingTime;		// ���� �ð�
	float				m_fStartTime;		// ��ų ���۽ð�,
	float*				m_pCurrentTime;		// ���� �ð�

	float				m_fPassedTime;		// ����ð�.
	float				m_fRemoveTime;		// ������ �ð�(������Ʈ��)

	SYNTHESIZE(bool, m_bIsCasting, IsCasting);
	SYNTHESIZE(bool, m_bIsCooldown, IsCooldown);// ��Ÿ�ӳ�����?
	bool				m_bIsTarget;		// Ÿ�����̳�?
	bool				m_bIsRemove;		// ������Ʈ �����Ҳ���.

	bool				m_bIsAutoFire;			// �����ȿ� �ֳ�?

	bool				m_isUsingSkill;			//

	SYNTHESIZE(bool, m_bIsReady, IsReady); // ��ų ��� �غ� �Ǿ���?

	// ���� �޾����� ���� ó���� ���� �÷��̾� ������
	SYNTHESIZE(cPlayer*, m_pPlayer, Player);		// ������ ������ ����,,, ���� ����
	// SYNTHESIZE_REF(BUFF_TYPE, e_BuffType, , BuffType); �̷����ϸ� �ټ¾ȵ�
	BUFF_TYPE e_BuffType;
	
	// ������Ʈ
	cSkinnedMesh*		m_pMesh;
	cCube*				m_pCube;

	std::vector<OBJECT_MESH> m_vecMesh;

	AOE_MESH*			s_AoeMesh;

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
			bool isNormal);

	void Move();
	void MeshMove();					// �Ž� �̵�
	void Casting();
	void CoolDownSetup();				// ��ٿ�

	void RemoveCubeTime();				// �ð��� ���� ��ų ������
	void RemoveRange();					// ������ ���� ��ų ������
	void RemoveTarget();				// Ÿ���϶� ������Ʈ ����
	void RemoveMeshTime();

	void AutoFire();

	// �ϴ��׽�Ʈ�� ť��
	void RenderCube();

	void CreateMesh();
	void RenderVecMesh();

	bool CollisionMesh(D3DXVECTOR3 enemyPos);		// �������� ���߿� ���̶� �浹������ �������� (�����̶� ���̶� �Ÿ������ؼ� �浹�̸� true �ƴϸ� false ��ȯ)

	float GetCoolDown() { return m_fCurrentCooldown; }
	// ������ �Լ�
	void BuffStart();
	void BuffEnd();
	void ReadyIsCasting();

	void SetBuffType(BUFF_TYPE buffType) { e_BuffType = buffType; }
	float CooldownTimer();

	void CreateAOEMesh(float aoeScale, bool isCreatePointMesh, float pointScale);
	void DestroyAOEMesh();
	void RenderAOEMesh();

	bool IsUsingSkill();

	//void SetPlayerPos(D3DXVECTOR3* pos) { m_pPlayerPos = pos; }
};

