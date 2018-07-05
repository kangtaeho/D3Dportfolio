#include "stdafx.h"
#include "cSkill.h"
#include "cCube.h"

cSkill::cSkill()
	: e_skillType(TYPE_COUNT)
	, m_vPos(0,0,0)
	, m_vDir(0,0,0)
	, m_pTargetPos(NULL)
	, m_fRotY(0.0f)
	, m_fDamage(0)
	, m_fRange(0)
	, m_fPosSpeed(0)
	, m_fCooldown(0)
	, m_fCurrentCooldown(0)
	, m_fCastingTime(0)
	, m_fPassedTime(0)
	, m_fRemoveTime(0)
	, m_pCurrentTime(NULL)
	, m_fStartTime(0)
	, m_bIsCasting(false)
	, m_bIsTarget(false)
	, m_bIsCooldown(false)
	, m_bIsRemove(false)
{
	D3DXMatrixIdentity(&m_matWorld);
}


cSkill::~cSkill()
{
}

HRESULT cSkill::Setup(SKILL_TYPE skillType,
					float damage,
					float range,
					float posSpeed,
					float cooldown,
					float castingTime,
					float removeTime,
					bool isTarget)
{
	e_skillType = skillType;
	m_fDamage = damage;
	m_fRange = range;
	m_fPosSpeed = posSpeed;
	m_fCooldown = cooldown;
	m_fRemoveTime = removeTime;
	m_bIsTarget = isTarget;

	return S_OK;
}

void cSkill::Release()
{
	
}

void cSkill::Update()
{

}

void cSkill::Render()
{

}

void cSkill::Fire(D3DXVECTOR3 playerPos,
				D3DXVECTOR3* tagetPos, 
				float* currentTime)
{
	m_vPos = playerPos;
	m_pTargetPos = tagetPos;

	if (D3DXVec3Length(&(*m_pTargetPos - m_vPos)) > m_fRange) return;	// Ÿ�ٰ� �÷��̾��� ��ġ�� �������� ũ�� ����
	if (m_bIsCasting || m_bIsCooldown) return;							// ���� ���̰ų�, ��Ÿ�� ���̸�
	
	m_bIsCasting = true;												// ���� �Ҳ���
	m_pCurrentTime = currentTime;
	m_fStartTime = g_pTimeManager->GetLastUpdateTime();

	m_fRotY = GetAngle(m_vPos.x, m_vPos.z, m_pTargetPos->x, m_pTargetPos->z);		// �ޱ�
	m_vDir = (*m_pTargetPos) - m_vPos;
	D3DXVec3Normalize(&m_vDir, &m_vDir);										// ���⺤��

}

void cSkill::Move()
{
	if (m_pCube)
	{
		m_fRotY = GetAngle(m_vPos.x, m_vPos.z, m_pTargetPos->x, m_pTargetPos->z);		// �ޱ�
		m_vDir = (*m_pTargetPos) - m_vPos;
		D3DXVec3Normalize(&m_vDir, &m_vDir);

		D3DXMATRIX matR, matT;
		D3DXMatrixRotationY(&matR, m_fRotY);

		m_vPos += m_vDir * m_fPosSpeed;

		D3DXMatrixTranslation(&matT, m_vPos.x, m_vPos.y, m_vPos.z);
		m_matWorld = matR*matT;
		m_pCube->SetMatWorld(m_matWorld);
	}
}

void cSkill::Casting()
{
	if (!m_bIsCasting) return;

	if (m_fCastingTime == NULL)		// �޴� ĳ���� Ÿ�������Ͱ� ������
	{
		m_fPassedTime = g_pTimeManager->GetLastUpdateTime() - m_fStartTime;
		if (m_fPassedTime > m_fCastingTime)
		{

			// ���� ���⼭ ������Ʈ �������� �ϸ� �ȴ�.

			CastingSkill(e_skillType);

			m_bIsCasting = false;
			m_bIsCooldown = true;		// ��ٿ� �ٽ� ������

			// ��ٿ� ��������� �������
			// ������ Ÿ�ӿ��� ����
			m_fStartTime = g_pTimeManager->GetLastUpdateTime();
			m_bIsRemove = true;

		}
	}
	else
	{
		if (*m_pCurrentTime > m_fCastingTime)
		{

			// ���� ���⼭ ������Ʈ �������� �ϸ� �ȴ�.

			CastingSkill(e_skillType);

			m_bIsCasting = false;
			m_bIsCooldown = true;		// ��ٿ� �ٽ� ������

			m_fStartTime = g_pTimeManager->GetLastUpdateTime();
			m_bIsRemove = true;

		}
	}

}

void cSkill::CoolDownSetup()
{
	if (!m_bIsCooldown) return;		// ��ٿ��� �ƴ϶�� ����.

	m_fCurrentCooldown += g_pTimeManager->GetElapsedTime();
	
	if (m_fCurrentCooldown > m_fCooldown)
	{
		m_bIsCooldown = false;
		m_bIsCasting = false;
		m_fCurrentCooldown = 0.0f;
	}

}

void cSkill::CastingSkill(SKILL_TYPE skillType)
{

	// if (m_bIsCasting || m_bIsCooldown) return;


	if (skillType == MELEE_SKILL)
	{

		//---------------------------�׽�Ʈ--------------------//
		// �ϴ� �׽�Ʈ
		CreateCube();
		D3DXMATRIX matR, matT;
		D3DXMatrixRotationY(&matR, m_fRotY);
		// Ÿ���� ��ġ�� �ٷ� ť�����
		D3DXMatrixTranslation(&matT, m_pTargetPos->x, m_pTargetPos->y, m_pTargetPos->z);
		m_matWorld = matR*matT;
		m_pCube->SetMatWorld(m_matWorld);
		//---------------------------�׽�Ʈ--------------------//


	}
	else if (skillType == RANGE_SKILL)
	{

		//---------------------------�׽�Ʈ--------------------//
		CreateCube();
		D3DXMATRIX matR, matT;
		D3DXMatrixRotationY(&matR, m_fRotY);
		//  �÷��̾� ��ġ�� �ٷ� ť�����
		D3DXMatrixTranslation(&matT, m_vPos.x, m_vPos.y, m_vPos.z);
		m_matWorld = matR*matT;
		m_pCube->SetMatWorld(m_matWorld);
		//---------------------------�׽�Ʈ--------------------//

	}
	else if (skillType == OBJECT_SKILL)
	{

	}

}

void cSkill::RemoveTime()
{
	if (!m_bIsRemove) return;
		// ��Ÿ���̸鼭 �������� �ƴϸ�
	m_fPassedTime = g_pTimeManager->GetLastUpdateTime() - m_fStartTime;

	if (m_fPassedTime > m_fRemoveTime)
	{
		// ������Ʈ ����(�׽�Ʈ������ ť�����)
		delete m_pCube;
		m_pCube = NULL;
		m_bIsRemove = false;
	}

}

void cSkill::RemoveRange()
{

}















//���߿� ����

void cSkill::CreateCube()
{
	m_pCube = new cCube;
	m_pCube->Setup(D3DXVECTOR3(1.0, 1.0, 1.0), NULL);
}

void cSkill::RenderCube()
{
	if (m_pCube)
		m_pCube->Render();
}
