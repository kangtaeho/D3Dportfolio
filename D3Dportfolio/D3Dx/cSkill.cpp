#include "stdafx.h"
#include "cSkill.h"
#include "cCube.h"
#include "cSkinnedMesh.h"

cSkill::cSkill()
	: e_skillType(TYPE_COUNT)
	, m_vPos(0,0,0)
	, m_vDir(0,0,0)
	, m_pPlayerPos(NULL)
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
	, m_bIsAutoFire(false)
	, m_pMesh(NULL)
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
					float castingTime,
					float cooldown,
					float removeTime,
					bool isTarget,
					const char* name)
{
	e_skillType = skillType;
	m_fDamage = damage;
	m_fRange = range;
	m_fPosSpeed = posSpeed;
	m_fCastingTime = castingTime;
	m_fCooldown = cooldown;
	m_fRemoveTime = removeTime;
	m_bIsTarget = isTarget;

	if (name)
	{
		m_pMesh = g_pXfileManager->AddXfile(name, "character", (std::string(name) + ".x").c_str());
		m_pMesh->CloneAniController(&m_pAnimController);
	}

	return S_OK;
}

void cSkill::Release()
{
	if (m_pCube) delete m_pCube;
}

void cSkill::Update()
{

}

void cSkill::Render()
{

}

void cSkill::Fire(D3DXVECTOR3* playerPos,
				D3DXVECTOR3* tagetPos, 
				float* currentTime)
{
	if (m_bIsCasting) return; // ���� ���̰ų�, ��Ÿ�� ���̸�
	if (m_bIsCooldown) return;

	m_vPos = *playerPos;		// �̻��� ���� ��ġ
	m_pPlayerPos = playerPos;	// �÷��̾� ��ǥ ������
	m_pTargetPos = tagetPos;

	// Ÿ�ٰ� �÷��̾��� ��ġ�� �������� Ŭ��
	if (D3DXVec3Length(&(*m_pTargetPos - m_vPos)) > m_fRange)
	{
		if (m_bIsTarget) m_bIsAutoFire = true;	//Ÿ�����̶�� ���� ����
		
	}
	else {
		m_bIsCasting = true;
	}

	m_pCurrentTime = currentTime;
	m_fStartTime = g_pTimeManager->GetLastUpdateTime();

	m_fRotY = GetAngle(m_vPos, *m_pTargetPos);		// �ޱ�
	m_vDir = (*m_pTargetPos) - m_vPos;
	D3DXVec3Normalize(&m_vDir, &m_vDir);			// ���⺤��

	

}

void cSkill::Move()
{
	if (m_pCube)
	{
		m_fRotY = GetAngle(m_vPos, *m_pTargetPos);
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

	m_fPassedTime = g_pTimeManager->GetLastUpdateTime() - m_fStartTime;
	if (m_fPassedTime > m_fCastingTime)
	{	

		// ���� ���⼭ ������Ʈ �������� �ϸ� �ȴ�.
		CreateMesh();

		m_bIsCooldown = true;		// ��ٿ� �ٽ� ������
		m_bIsCasting = false;

		// ��ٿ� ��������� �������
		// ������ Ÿ�ӿ��� ����
		m_fStartTime = g_pTimeManager->GetLastUpdateTime();
		m_bIsRemove = true;

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

void cSkill::RemoveCubeTime()
{
	if (!m_bIsRemove) return;
		// ��Ÿ���̸鼭 �������� �ƴϸ�
	m_fPassedTime += g_pTimeManager->GetElapsedTime();

	if (m_fPassedTime > m_fRemoveTime)
	{
		// ������Ʈ ����(�׽�Ʈ������ ť�����)
		delete m_pCube;
		m_pCube = NULL;
		m_bIsRemove = false;
		m_fPassedTime = 0.0f;
	}

}

void cSkill::RemoveRange()
{

}

void cSkill::RemoveTarget()
{
	if (!m_pTargetPos) return; // ��� Ÿ���� ������ ����

	if (D3DXVec3Length(&(*m_pTargetPos - m_vPos)) < 10.0f)
	{
		delete m_pCube;
		m_pCube = NULL;
		m_bIsRemove = false;
	}
}

void cSkill::RemoveMeshTime()
{
}

void cSkill::AutoFire()
{
	if (!m_bIsAutoFire) return;

	if (D3DXVec3Length(&(*m_pTargetPos - *m_pPlayerPos)) < m_fRange)
	{
		m_bIsCasting = true;
		m_vPos = *m_pPlayerPos;
		m_bIsAutoFire = false;
	}
}

//���߿� ����
void cSkill::RenderCube()
{
	if (m_pCube)
		m_pCube->Render();
}

void cSkill::CreateMesh()
{
	if (e_skillType == MELEE_SKILL)
	{
		// �ϴ� �׽�Ʈ
		D3DXMATRIX matR, matT;
		D3DXMatrixRotationY(&matR, m_fRotY);
		// Ÿ���� ��ġ�� �ٷ� ť�����
		D3DXMatrixTranslation(&matT, m_pTargetPos->x, m_pTargetPos->y, m_pTargetPos->z);
		m_matWorld = matR*matT;
		// m_pCube->SetMatWorld(m_matWorld);
	}
	else if (e_skillType == RANGE_SKILL)
	{
		if (m_pCube) return;
		m_pCube = new cCube;
		m_pCube->Setup(D3DXVECTOR3(20.0, 20.0, 50.0), NULL);
		D3DXMATRIX matR, matT;
		D3DXMatrixRotationY(&matR, m_fRotY);
		//  �÷��̾� ��ġ�� �ٷ� ť�����
		D3DXMatrixTranslation(&matT, m_vPos.x, m_vPos.y, m_vPos.z);
		m_matWorld = matR*matT;
		m_pCube->SetMatWorld(m_matWorld);
	}
	else if (e_skillType == OBJECT_SKILL)
	{
		if (m_pMesh)
		{
			OBJECT_MESH mesh;
			D3DXMATRIX matT;
			D3DXMatrixTranslation(&matT, m_pTargetPos->x, m_pTargetPos->y, m_pTargetPos->z);
			mesh.world = matT;
			mesh.removeTime = 0;
			m_vecMesh.push_back(mesh);
		}
	}
	
}

void cSkill::RenderVecMesh()
{
	for (int i = 0; i < m_vecMesh.size(); i++)
	{
		g_pD3DDevice->SetTransform(D3DTS_WORLD, &m_vecMesh[i].world);
		UpdateAnimation();
		m_pMesh->Update(m_pAnimController);
	}
}

