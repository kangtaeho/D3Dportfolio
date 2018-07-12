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
	if (m_bIsCasting) return; // 시전 중이거나, 쿨타임 중이면
	if (m_bIsCooldown) return;

	m_vPos = *playerPos;		// 미사일 시작 위치
	m_pPlayerPos = playerPos;	// 플레이어 좌표 포인터
	m_pTargetPos = tagetPos;

	// 타겟과 플레이어의 위치가 범위보다 클때
	if (D3DXVec3Length(&(*m_pTargetPos - m_vPos)) > m_fRange)
	{
		if (m_bIsTarget) m_bIsAutoFire = true;	//타겟팅이라면 오토 실행
		
	}
	else {
		m_bIsCasting = true;
	}

	m_pCurrentTime = currentTime;
	m_fStartTime = g_pTimeManager->GetLastUpdateTime();

	m_fRotY = GetAngle(m_vPos, *m_pTargetPos);		// 앵글
	m_vDir = (*m_pTargetPos) - m_vPos;
	D3DXVec3Normalize(&m_vDir, &m_vDir);			// 방향벡터

	

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

		// 이제 여기서 오브젝트 나가도록 하면 된다.
		CreateMesh();

		m_bIsCooldown = true;		// 쿨다운 다시 돌린다
		m_bIsCasting = false;

		// 쿨다운 문제생기면 삭제요망
		// 리무브 타임에서 재사용
		m_fStartTime = g_pTimeManager->GetLastUpdateTime();
		m_bIsRemove = true;

	}
}

void cSkill::CoolDownSetup()
{
	if (!m_bIsCooldown) return;		// 쿨다운이 아니라면 끈다.

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
		// 쿨타임이면서 시전중이 아니면
	m_fPassedTime += g_pTimeManager->GetElapsedTime();

	if (m_fPassedTime > m_fRemoveTime)
	{
		// 오브젝트 삭제(테스트용으로 큐브삭제)
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
	if (!m_pTargetPos) return; // 대상 타겟이 없으면 리턴

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

//나중에 삭제
void cSkill::RenderCube()
{
	if (m_pCube)
		m_pCube->Render();
}

void cSkill::CreateMesh()
{
	if (e_skillType == MELEE_SKILL)
	{
		// 일단 테스트
		D3DXMATRIX matR, matT;
		D3DXMatrixRotationY(&matR, m_fRotY);
		// 타겟팅 위치에 바로 큐브생성
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
		//  플레이어 위치에 바로 큐브생성
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

