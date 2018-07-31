#include "stdafx.h"
#include "cSkill.h"
#include "cCube.h"
#include "cSkinnedMesh.h"
#include "cPlayer.h"
#include "cCharacter.h"

cSkill::cSkill()
	: e_skillType(SKILL_TYPE_COUNT)
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
	, m_bIsReady(false)
	, m_bIsFire(false)
	, m_pMesh(NULL)
	, m_pPlayer(NULL)
	, m_pTargetEnemy(NULL)
	, e_BuffType(BUFF_TYPE_COUNT)
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
	//if (s_AoeMesh) DestroyAOEMesh();

}

void cSkill::Update()
{

}

void cSkill::Render()
{

}

void cSkill::Fire(D3DXVECTOR3* playerPos,
				D3DXVECTOR3* tagetPos,
				cCharacter* targetEnemy,
				bool isNormal)

{
	if (!isNormal)	// 평타가 아닐때
	{
		if (!m_bIsReady) return;	// 스킬시전이 아니라면
	}

	if (m_bIsCasting) return; // 시전 중이거나, 쿨타임 중이면
	if (m_bIsCooldown) return;

	m_vPos = *playerPos;		// 미사일 시작 위치
	m_pPlayerPos = playerPos;	// 플레이어 좌표 포인터
	m_pTargetPos = tagetPos;
	m_pTargetEnemy = targetEnemy;	// 적설정

	// 타겟과 플레이어의 위치가 범위보다 클때
	if (D3DXVec3Length(&(*m_pTargetPos - m_vPos)) > m_fRange)
	{
		if (m_bIsTarget) m_bIsAutoFire = true;	//타겟팅이라면 오토 실행
	}
	else 
	{
		m_bIsCasting = true;
	}

	m_fStartTime = g_pTimeManager->GetLastUpdateTime();

	m_fRotY = GetAngle(m_vPos, *m_pTargetPos);		// 앵글
	m_vDir = (*m_pTargetPos) - m_vPos;
	D3DXVec3Normalize(&m_vDir, &m_vDir);			// 방향벡터

	// 클릭한 순간에 사라저야함.
	m_bIsFire = true; // false는 cooldown에 넣어둘 생각임
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

void cSkill::MeshMove()
{
	for (int i = 0; i < m_vecMesh.size(); i++)
	{
		if (D3DXVec3Length(&(m_vecMesh[i].target - m_vecMesh[i].pos))<m_fPosSpeed) continue;

		D3DXVECTOR3 dir = m_vecMesh[i].target - m_vecMesh[i].pos;
		D3DXVec3Normalize(&dir, &dir);

		m_vecMesh[i].pos += dir*m_fPosSpeed;

	}
}

void cSkill::Casting()
{
	if (!m_bIsCasting) return;

	m_fPassedTime = g_pTimeManager->GetLastUpdateTime() - m_fStartTime;
	if (m_fPassedTime > m_fCastingTime)
	{	
		// 이제 여기서 오브젝트 나가도록 하면 된다.

		if (e_skillType == BUFF_SKILL) BuffStart();		// 타입이 버프 스킬이라면
		else CreateMesh();

		m_bIsCooldown = true;		// 쿨다운 다시 돌린다
		m_bIsCasting = false;

		// 쿨다운 문제생기면 삭제요망
		// 리무브 타임에서 재사용
		m_fStartTime = g_pTimeManager->GetLastUpdateTime();
		m_fPassedTime = 0.0f;

		m_bIsRemove = true;

		m_bIsReady = false;
		m_isUsingSkill = true;
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
		m_bIsFire = false;
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
	if (!m_pTargetEnemy) return;
	if (!m_pCube)return;

	if (D3DXVec3Length(&(*m_pTargetPos - m_vPos)) < 10.0f)
	{
		delete m_pCube;
		m_pCube = NULL;
		m_bIsRemove = false;
		//m_pTargetPos = NULL;

		switch (e_skillType)
		{
		case RANGE_SKILL:
			m_pTargetEnemy->SetHP(m_pTargetEnemy->GetHP() - m_fDamage);
			break;
		case TOXIC_SKILL:
			AddToxicEnemy(m_pTargetEnemy);
			break;
		}
	}
}

void cSkill::RemoveMeshTime()
{
	if (!m_bIsRemove) return;
	// 쿨타임이면서 시전중이 아니면

	for (int i = 0; i < m_vecMesh.size(); i++)
	{
		m_vecMesh[i].removeTime += g_pTimeManager->GetElapsedTime();
		
		if (m_pVecEnemy)
		{
			for (int j = 0; j < m_pVecEnemy->size(); j++)
			{
				if (D3DXVec3Length(&(m_vecMesh[i].pos - (*m_pVecEnemy)[j]->getPosition())) < 60)
				{
					SAFE_DELETE(m_vecMesh[i].animation);
					m_vecMesh.erase(m_vecMesh.begin() + i);
					continue;
				}
			}
		}
			
		if (m_vecMesh[i].removeTime > m_fRemoveTime)
		{
			SAFE_DELETE(m_vecMesh[i].animation);
			m_vecMesh.erase(m_vecMesh.begin() + i);
		}
	}

}

void cSkill::AutoFire()
{
	if (!m_bIsAutoFire) return;

	if (D3DXVec3Length(&(*m_pTargetPos - *m_pPlayerPos)) < m_fRange)
	{
		m_fStartTime = g_pTimeManager->GetLastUpdateTime();
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
	else if (e_skillType == RANGE_SKILL|| e_skillType == TOXIC_SKILL)
	{
		if (m_pCube) return;
		m_pCube = new cCube;
		m_pCube->Setup(D3DXVECTOR3(20.0, 20.0, 50.0), NULL);
		D3DXMATRIX matR, matT;
		D3DXMatrixRotationY(&matR, m_fRotY);
		m_vPos = *m_pPlayerPos;
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
			mesh.pos = *m_pPlayerPos;
			mesh.target = *m_pTargetPos;
			mesh.removeTime = 0;
			mesh.startTime = g_pTimeManager->GetLastUpdateTime();
			mesh.isAttack = false;
			aniCloneAniController(&mesh.animation->getAniController());
			m_vecMesh.push_back(mesh);
			m_vecMesh.back().animation->setAnimation();
		}
	}
	
}

void cSkill::RenderVecMesh()
{
	for (int i = 0; i < m_vecMesh.size(); i++)
	{
		D3DXMATRIX	matT;
		D3DXMatrixTranslation(&matT, m_vecMesh[i].pos.x, m_vecMesh[i].pos.y, m_vecMesh[i].pos.z);
		g_pD3DDevice->SetTransform(D3DTS_WORLD, &matT);
		m_vecMesh[i].animation->UpdateAnimation();
		m_pMesh->Update(m_vecMesh[i].animation->getAniController());
	}
}

bool cSkill::CollisionMesh(D3DXVECTOR3 enemyPos)
{
	for (int i = 0; i < m_vecMesh.size(); i++)
	{
		if (D3DXVec3Length(&(m_vecMesh[i].pos - enemyPos)) < 5.0f)	// 거리가 가까우면
		{
			m_vecMesh.erase(m_vecMesh.begin() + i);
			return true;
		}
	}
	return false;
}

void cSkill::BuffStart()
{
	if (!m_pPlayer) return;

	switch (e_BuffType)
	{
	case MOVEUP:
		m_pPlayer->SetSpeed(m_pPlayer->GetSpeed()*2.0f);
		break;
	case DAMAGEUP:
		break;
	}

}

void cSkill::BuffEnd()
{
	if (!m_pPlayer) return;
	if (!m_bIsRemove) return;
	// 쿨타임이면서 시전중이 아니면
	m_fPassedTime += g_pTimeManager->GetElapsedTime();

	if (m_fPassedTime > m_fRemoveTime)
	{
		switch (e_BuffType)
		{
		case MOVEUP:
			m_pPlayer->SetSpeed(m_pPlayer->GetSpeed() / 2.0f);
			break;
		case DAMAGEUP:
			break;
		}
		m_bIsRemove = false;
	}

}

void cSkill::ReadyIsCasting()
{
	if (m_bIsReady) m_bIsCasting = true;
}

int cSkill::CooldownTimer()
{
	return m_fCooldown-m_fCurrentCooldown;
}

void cSkill::CreateAOEMesh(bool isCreatePointMesh, float pointScale)
{
	// ZeroMemory(&s_AoeMesh, sizeof(AOE_MESH));
	s_AoeMesh = new AOE_MESH;

	ST_PNT_VERTEX v1;
	v1.p = D3DXVECTOR3(-1, 0, 1);
	v1.n = D3DXVECTOR3(0, 1, 0);
	v1.t = D3DXVECTOR2(0, 0);

	ST_PNT_VERTEX v2;
	v2.p = D3DXVECTOR3(1, 0, 1);
	v2.n = D3DXVECTOR3(0, 1, 0);
	v2.t = D3DXVECTOR2(1, 0);

	ST_PNT_VERTEX v3;
	v3.p = D3DXVECTOR3(1, 0, -1);
	v3.n = D3DXVECTOR3(0, 1, 0);
	v3.t = D3DXVECTOR2(1, 1);

	ST_PNT_VERTEX v4;
	v4.p = D3DXVECTOR3(-1, 0, -1);
	v4.n = D3DXVECTOR3(0, 1, 0);
	v4.t = D3DXVECTOR2(0, 1);

	std::vector<ST_PNT_VERTEX> index;
	index.push_back(v1);
	index.push_back(v3);
	index.push_back(v4);
	index.push_back(v1);
	index.push_back(v2);
	index.push_back(v3);

	D3DXCreateMeshFVF(
		2,
		6,
		D3DXMESH_MANAGED,
		ST_PNT_VERTEX::FVF,
		g_pD3DDevice,
		&s_AoeMesh->aoeMesh
	);

	ST_PNT_VERTEX* vM;
	s_AoeMesh->aoeMesh->LockVertexBuffer(0, (void**)&vM);

	for (int i = 0; i < index.size(); i++)
	{
		vM[i] = index[i];
	}

	s_AoeMesh->aoeMesh->UnlockVertexBuffer();

	WORD * wM;
	s_AoeMesh->aoeMesh->LockIndexBuffer(0, (void**)&wM);

	for (int i = 0; i < index.size(); i++)
	{
		wM[i] = i;
	}

	s_AoeMesh->aoeMesh->UnlockIndexBuffer();

	if (isCreatePointMesh)
	{
		D3DXCreateMeshFVF(
			2,
			6,
			D3DXMESH_MANAGED,
			ST_PNT_VERTEX::FVF,
			g_pD3DDevice,
			&s_AoeMesh->pointMesh
		);

		ST_PNT_VERTEX* vM1;

		s_AoeMesh->pointMesh->LockVertexBuffer(0, (void**)&vM1);

		for (int i = 0; i < index.size(); i++)
		{
			vM1[i] = index[i];
		}

		s_AoeMesh->pointMesh->UnlockVertexBuffer();

		WORD * wM1;
		s_AoeMesh->pointMesh->LockIndexBuffer(0, (void**)&wM1);

		for (int i = 0; i < index.size(); i++)
		{
			wM1[i] = i;
		}

		s_AoeMesh->pointMesh->UnlockIndexBuffer();
		s_AoeMesh->pointScale = pointScale;

	}

}

void cSkill::DestroyAOEMesh()
{
	if (s_AoeMesh)
	{
		if (s_AoeMesh->aoeMesh)s_AoeMesh->aoeMesh->Release();
		if (s_AoeMesh->pointMesh)s_AoeMesh->pointMesh->Release();
		SAFE_DELETE(s_AoeMesh);
	}
}

void cSkill::RenderAOEMesh()
{

	//if (m_bIsAutoFire) return;
	if (m_bIsReady && !m_bIsFire)
	{
		if (s_AoeMesh)
		{
			D3DXMATRIX	matAOEWorld, matPointWorld;
			D3DXMATRIX	matS, matT;

			D3DXMatrixScaling(&matS, m_fRange, 1, m_fRange);
			D3DXMatrixTranslation(&matT, m_pPlayer->getPosition().x, m_pPlayer->getPosition().y, m_pPlayer->getPosition().z);

			matAOEWorld = matS*matT;

			g_pD3DDevice->SetTransform(D3DTS_WORLD, &matAOEWorld);
			g_pD3DDevice->SetFVF(ST_PNT_VERTEX::FVF);
			LPDIRECT3DTEXTURE9 texture = g_pTextureManager->GetTexture("./select/skillFloor03.png");
			g_pD3DDevice->SetTexture(0, texture);

			s_AoeMesh->aoeMesh->DrawSubset(0);

			if (s_AoeMesh->pointMesh)
			{
				int isPick = 0;
				D3DXVECTOR3 p = g_pCollisionManager->getRayPosition(isPick);

				D3DXMatrixScaling(&matS, s_AoeMesh->pointScale, 1, s_AoeMesh->pointScale);
				D3DXMatrixTranslation(&matT, p.x, p.y, p.z);

				matPointWorld = matS*matT;

				g_pD3DDevice->SetTransform(D3DTS_WORLD, &matPointWorld);
				g_pD3DDevice->SetFVF(ST_PNT_VERTEX::FVF);
				LPDIRECT3DTEXTURE9 texture1 = g_pTextureManager->GetTexture("./select/skillFloor02.png");
				g_pD3DDevice->SetTexture(0, texture1);

				s_AoeMesh->pointMesh->DrawSubset(0);

			}

		}
	}

}

bool cSkill::IsUsingSkill()
{
	if (m_isUsingSkill)
	{
		m_isUsingSkill = false;
		return true;
	}
	else
	{
		return false;
	}

}

void cSkill::AddToxicEnemy(cCharacter* enemy)
{
	TOXIC_ENEMY t;
	t.enemy = enemy;
	t.removeTime = 0.0f;
	t.countTime = 0.0f;
	t.startTime = g_pTimeManager->GetLastUpdateTime();
	m_vecToxic.push_back(t);
}

void cSkill::DamagedToxic()
{

	for (int i = 0; i < m_vecToxic.size(); i++)
	{
		m_vecToxic[i].removeTime = g_pTimeManager->GetLastUpdateTime() - m_vecToxic[i].startTime;

		if ((m_vecToxic[i].removeTime - m_vecToxic[i].countTime) > 0)
		{
			m_vecToxic[i].countTime+=2.0f;
			m_vecToxic[i].enemy->SetHP(m_vecToxic[i].enemy->GetHP() - m_fDamage / 2.0f);
		}

		if (m_vecToxic[i].removeTime > m_fRemoveTime)
		{
			m_vecToxic.erase(m_vecToxic.begin() + i);
		}

	}
}
