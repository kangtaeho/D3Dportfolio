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
	//bool				m_bIsCasting;		// �����߳�?
	bool				m_bIsCooldown;		// ��Ÿ�ӳ�����?
	bool				m_bIsTarget;		// Ÿ�����̳�?
	bool				m_bIsRemove;		// ������Ʈ �����Ҳ���.

	bool				m_bIsAutoFire;			// �����ȿ� �ֳ�?


	// ������Ʈ
	LPCSKINNEDMESH		m_pMesh;

	// �׽�Ʈ�� ť��
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
	void CoolDownSetup();				// ��ٿ�

	void CastingSkill(SKILL_TYPE skillType);

	void RemoveTime();					// �ð��� ���� ��ų ������
	void RemoveRange();					// ������ ���� ��ų ������
	void RemoveTarget();				// Ÿ���϶� ������Ʈ ����

	void AutoFire();

	// �ϴ��׽�Ʈ�� ť��
	void CreateCube();
	void RenderCube();



};

