#include "stdafx.h"
#include "cPlayer.h"
#include "cRayPicking.h"
#include "cSphere.h"
#include "cAStar.h"
#include "cEnemy.h"
#include "cShop.h"
#include "Bitmap.h"

cPlayer::cPlayer()
{

}

cPlayer::~cPlayer()
{

}

void cPlayer::Setup(const char* name)
{
	m_fRange = 400;
	m_fSpeed = 7.0f;
	m_fMAXHP = 300;
	m_fMAXMP = 250;
	m_fHP = 300;
	m_fMP = 250;
	m_fDEF = 50;
	m_fATK = 50;
	m_fATKSpeed = 50;

	cCharacter::Setup(name);

	m_fRadius = 13.0f;

	g_pSkillManager->AddSkill("평타", RANGE_SKILL, m_fATK, m_fRange, 20.0f, 0.3f, 2.5f, 20, true);
	g_pSkillManager->GetSkill("평타")->SetDamageRender("normalShot");

	g_pSkillManager->AddSkill("r", OBJECT_SKILL, 100, 500, 10.0f, 0.5f, 20.0f, 40, true, "BantamTrap");
	g_pSkillManager->GetSkill("r")->SetPlayer(this);	// 테두리 때문에

	g_pSkillManager->AddSkill("w", BUFF_SKILL, 0, 0, 0, 0.5, 10, 10, false, NULL);
	g_pSkillManager->GetSkill("w")->SetPlayer(this);
	g_pSkillManager->GetSkill("w")->SetBuffType(MOVEUP);

	g_pSkillManager->AddSkill("e", TOXIC_SKILL, 50, 400, 20.0f, 0.5, 10.0f, 10, true);
	g_pSkillManager->GetSkill("e")->SetPlayer(this);

	CreateTargetMesh();

	m_fRespwan = 0.0f;
}

void cPlayer::Release()
{
	g_pSkillManager->Release();
}

void cPlayer::Update()
{
	if (g_pKeyManager->IsStayKeyDown(VK_SPACE))g_pCameraManager->setCameraPos(m_vPosition);
	Check3DMousePointer();

	bool isMove = false;
	isMove = m_AStar.Update(m_vPosition, m_vNextPosition, m_fRotY, m_fSpeed, m_fRadius, m_fRange, m_pEnemyPos);

	g_pSkillManager->Update();

	if (m_fRespwan)
	{
		m_fRespwan -= g_pTimeManager->GetElapsedTime();
		if (m_fRespwan <= 0)
		{
			m_fHP = 300.0f;
			m_vPosition = g_pCollisionManager->SetHeight(D3DXVECTOR3(0, 0, 0));
			m_vNextPosition = m_vPosition;
			m_fRespwan = 0.0f;
		}
	}

	if (m_fHP <= 0)
	{
		setAnimation("Death", false);
		if(!m_fRespwan)
			m_fRespwan = 10.0f;
	}
	else if (g_pSkillManager->IsCasting())
	{
		setAnimation("Attack1");
		if(m_pEnemy)
			m_pEnemy->setEnemy(this);
	}
	else if (isMove)
	{
		setAnimation("Run");
		if (m_pEnemyPos && m_pEnemy)
			*m_pEnemyPos = m_pEnemy->getPosition();
	}
	else
	{
		setAnimation();
	}

}

void cPlayer::Render()
{
	POINT ptMouse;
	GetCursorPos(&ptMouse);
	ScreenToClient(g_hWnd, &ptMouse);
	g_pFontManager->TextFont(ptMouse.x, ptMouse.y, D3DXVECTOR3(255,0, 255), "3D %0.2f, %0.2f, %0.2f", (float)m_vNextPosition.x, (float)m_vNextPosition.y, (float)m_vNextPosition.z);

	g_pSkillManager->Render();

	ClickTargetRender();

	cCharacter::Render();
}

void cPlayer::Check3DMousePointer()
{

	if (g_pKeyManager->IsOnceKeyDown(VK_LBUTTON))
	{
		if (!g_pSkillManager->CheckReady()) return;

		SAFE_DELETE(m_pEnemyPos);

		int isPick = 0;
		for (int i = 0; i < m_pVecEnemy->size(); ++i)
		{
			m_vNextPosition = g_pCollisionManager->getRayPosition(isPick, (*m_pVecEnemy)[i]->getPosition(), ((cEnemy*)(*m_pVecEnemy)[i])->getSphere(), (*m_pVecEnemy)[i]->GetRadius()); //포지션 받고	

			if (isPick)
			{
				m_pEnemy = (cEnemy*)(*m_pVecEnemy)[i];
				break;
			}
		}
		


		m_pEnemyPos = new D3DXVECTOR3;
		*m_pEnemyPos = m_vNextPosition;

		m_vClickPos = m_vNextPosition;

		if (g_pSkillManager->GetSkill("e")->GetIsReady())
		{
			if (m_pEnemy)
			{
				m_pEnemy->setEnemy(this);
				g_pSkillManager->Fire("e", &m_vPosition, m_pEnemy->getPositionPointer(), m_pEnemy);
			}
		}
		else if (g_pSkillManager->GetSkill("r")->GetIsReady())
		{
			g_pSkillManager->Fire("r", &m_vPosition, &m_vClickPos, false);
		}

	}

	if (g_pKeyManager->IsOnceKeyDown(VK_RBUTTON) && !isClickUi)
	{
		AttackEnemy(m_pEnemy);
	}

}

void cPlayer::AttackEnemy(cCharacter* enemy)
{
	SAFE_DELETE(m_pEnemyPos);

	int isPick = 0;

	for (int i = 0; i < m_pVecEnemy->size(); ++i)
	{
		m_vNextPosition = g_pCollisionManager->getRayPosition(isPick, (*m_pVecEnemy)[i]->getPosition(), ((cEnemy*)(*m_pVecEnemy)[i])->getSphere(), (*m_pVecEnemy)[i]->GetRadius()); //포지션 받고	
		if (isPick)
		{
			m_pEnemy = (cEnemy*)(*m_pVecEnemy)[i];
			break;
		}
	}
	if (m_pEnemy && m_pEnemy->GetHP() <= 0)
	{
		m_pEnemy = NULL;
		isPick = 0;
		m_vNextPosition = m_vPosition;
	}

	if (isPick)
	{
		m_pEnemyPos = new D3DXVECTOR3;
		*m_pEnemyPos = m_pEnemy->getPosition();
		if (D3DXVec3Length(&(m_vPosition - m_pEnemy->getPosition())) < m_fRange);
		{
			m_fRotY = GetAngle(m_vPosition, m_pEnemy->getPosition());
			g_pSkillManager->Fire("평타", &m_vPosition, m_pEnemy->getPositionPointer(), m_pEnemy);
			//SAFE_DELETE(m_pEnemyPos);
		}
	}
}

void cPlayer::CreateTargetMesh()
{
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
		&m_pTargetMesh
	);

	ST_PNT_VERTEX* vM;
	m_pTargetMesh->LockVertexBuffer(0, (void**)&vM);

	for (int i = 0; i < index.size(); i++)
	{
		vM[i] = index[i];
	}

	m_pTargetMesh->UnlockVertexBuffer();

	WORD * wM;
	m_pTargetMesh->LockIndexBuffer(0, (void**)&wM);

	for (int i = 0; i < index.size(); i++)
	{
		wM[i] = i;
	}

	m_pTargetMesh->UnlockIndexBuffer();
}

void cPlayer::ClickTargetRender()
{
	if (m_pEnemy)
	{
		D3DXMATRIX	matAOEWorld, matPointWorld;
		D3DXMATRIX	matS, matT;

		D3DXMatrixScaling(&matS, m_pEnemy->GetRadius()+10, 1, m_pEnemy->GetRadius()+10);
		D3DXMatrixTranslation(&matT, m_pEnemy->getPosition().x, m_pEnemy->getPosition().y + 5, m_pEnemy->getPosition().z);

		matAOEWorld = matS*matT;

		g_pD3DDevice->SetTransform(D3DTS_WORLD, &matAOEWorld);
		g_pD3DDevice->SetFVF(ST_PNT_VERTEX::FVF);
		LPDIRECT3DTEXTURE9 texture = g_pTextureManager->GetTexture("./select/targetRound.png");
		g_pD3DDevice->SetTexture(0, texture);

		m_pTargetMesh->DrawSubset(0);

	}
}
