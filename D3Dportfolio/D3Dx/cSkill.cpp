#include "stdafx.h"
#include "cSkill.h"
#include "cCube.h"

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

	if (m_fCastingTime == NULL)		// 받는 캐스팅 타임포인터가 없을때
	{
		m_fPassedTime = g_pTimeManager->GetLastUpdateTime() - m_fStartTime;
		if (m_fPassedTime > m_fCastingTime)
	{	

			// 이제 여기서 오브젝트 나가도록 하면 된다.

			CastingSkill(e_skillType);

			m_bIsCooldown = true;		// 쿨다운 다시 돌린다
			m_bIsCasting = false;

			// 쿨다운 문제생기면 삭제요망
			// 리무브 타임에서 재사용
			m_fStartTime = g_pTimeManager->GetLastUpdateTime();
			m_bIsRemove = true;

		}
	}
	else
	{
		if (*m_pCurrentTime > m_fCastingTime)
		{

			// 이제 여기서 오브젝트 나가도록 하면 된다.

			CastingSkill(e_skillType);

			m_bIsCasting = false;
			m_bIsCooldown = true;		// 쿨다운 다시 돌린다

			m_fStartTime = g_pTimeManager->GetLastUpdateTime();
			m_bIsRemove = true;

		}
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

void cSkill::CastingSkill(SKILL_TYPE skillType)
{

	// if (m_bIsCasting || m_bIsCooldown) return;


	if (skillType == MELEE_SKILL)
	{

		//---------------------------테스트--------------------//
		// 일단 테스트
		CreateCube();
		D3DXMATRIX matR, matT;
		D3DXMatrixRotationY(&matR, m_fRotY);
		// 타겟팅 위치에 바로 큐브생성
		D3DXMatrixTranslation(&matT, m_pTargetPos->x, m_pTargetPos->y, m_pTargetPos->z);
		m_matWorld = matR*matT;
		// m_pCube->SetMatWorld(m_matWorld);
		// ---------------------------테스트--------------------//


	}
	else if (skillType == RANGE_SKILL)
	{

		//---------------------------테스트--------------------//
		CreateCube();
		D3DXMATRIX matR, matT;
		D3DXMatrixRotationY(&matR, m_fRotY);
		//  플레이어 위치에 바로 큐브생성
		D3DXMatrixTranslation(&matT, m_vPos.x, m_vPos.y, m_vPos.z);
		m_matWorld = matR*matT;
		m_pCube->SetMatWorld(m_matWorld);
		//---------------------------테스트--------------------//

	}
	else if (skillType == OBJECT_SKILL)
	{

	}

}

void cSkill::RemoveTime()
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

	if (D3DXVec3Length(&(*m_pTargetPos - m_vPos)) < 2.0f)
	{
		delete m_pCube;
		m_pCube = NULL;
		m_bIsRemove = false;
	}
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

void cSkill::CreateCube()
{
	m_pCube = new cCube;
	m_pCube->Setup(D3DXVECTOR3(50.0, 20.0, 20.0), NULL);
}

void cSkill::RenderCube()
{
	if (m_pCube)
		m_pCube->Render();
}

