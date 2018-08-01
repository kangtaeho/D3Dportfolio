#include "stdafx.h"
#include "cPlayer.h"
#include "cRayPicking.h"
#include "cSphere.h"
#include "cAStar.h"
#include "cEnemy.h"
#include "cShop.h"
#include "Bitmap.h"
#include "cAshe.h"
#include "cHealthProgress.h"
#include <ctime>

cPlayer::cPlayer()
{

}

cPlayer::~cPlayer()
{

}

void cPlayer::Setup(const char* name)
{
	cCharacter::Setup(name);
	m_fRange = 400;
	m_fSpeed = 7.0f;
	m_fMAXHP = 300;
	m_fMAXMP = 250;
	m_fHP = 300;
	m_fMP = 250;
	m_fDEF = 50;
	m_fATK = 50;
	m_fATKSpeed = 50;
	m_fTime = 0.5f;
	m_fRegainHP = 0.1f;
	m_fRegainMP = 0.1f;

	m_vPosition = D3DXVECTOR3(-3118, 5224, -3642);
	m_vNextPosition = D3DXVECTOR3(-3118, 5224, -3642);
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
	m_fTelePortTime = 0.0f;
	m_fMaxTelePortTime = 8.0f;
	m_pTelePortProgress = new cHealthProgress;

	Bitmap* TelePortContainer; Bitmap* TelePortBar;
	TelePortContainer = g_pTextureManager->addTexture("TelePortContainer", "./status/TelePortContainer.dds", NULL, NULL);
	TelePortBar = g_pTextureManager->addTexture("TelePortBar", "./status/TelePortBar.dds", NULL,NULL);

	TelePortContainer->setScale(D3DXVECTOR3(2.5f, 1.2f, 0));
	TelePortBar->setScale(D3DXVECTOR3(2.5f, 1.2f, 0));

	m_pTelePortProgress->SetContainer(TelePortContainer);
	m_pTelePortProgress->SetProgress(TelePortBar);
	m_pTelePortProgress->setup();
	m_bTelePort = false;
	m_bProgressing = false;
	count = 0;
}

void cPlayer::Release()
{
	g_pSkillManager->Release();
}

void cPlayer::Update()
{
	if (g_pKeyManager->IsStayKeyDown(VK_SPACE))g_pCameraManager->setCameraPos(m_vPosition);

	bool isMove = false;
	isMove = m_AStar.Update(m_vPosition, m_vNextPosition, m_fRotY, m_fSpeed, m_fRadius, m_fRange, m_pEnemyPos);

	g_pSkillManager->Update();

	if (m_fRegainHP != 0.1f)
	{
		count++;
		if (count % 300 == 0)
		{
			m_fRegainHP = 0.1f;
			count = 0;
		}
	}

	if (m_fTime)
	{
		m_fTime -= g_pTimeManager->GetElapsedTime();

		if (m_fTime <= 0)
		{
			if (m_fHP < m_fMAXHP && m_fHP != 0) m_fHP += m_fRegainHP;
			m_fTime = 0.5f;
		}
	}


	if (m_fRespwan)
	{
		m_fRespwan -= g_pTimeManager->GetElapsedTime();
		if (m_fRespwan <= 0)
		{
			m_fHP = m_fMAXHP;
			//m_vPosition = g_pCollisionManager->SetHeight(D3DXVECTOR3(0, 0, 0));
			m_vPosition = g_pCollisionManager->SetHeight(D3DXVECTOR3(-3118, 5224, -3642));
			m_vNextPosition = m_vPosition;
			g_pCameraManager->setCameraPos(D3DXVECTOR3(-3118, 5224, -3642));
			m_fRespwan = 0.0f;
		}
	}

	if (m_vSavePos != m_vPosition)
	{
		m_bTelePort = false;
		m_bProgressing = false;

		m_vSavePos = m_vPosition;
		m_fTelePortTime = 0.0f;
	}

	if (g_pKeyManager->IsOnceKeyDown('B'))
	{
		if (!m_fTelePortTime)
		{
			m_bTelePort = true;
			m_bProgressing = true;
			m_vSavePos = m_vPosition;
			m_fTelePortTime = m_pTelePortProgress->GetProgress()->GETRECT()->right;
			m_pTelePortProgress->GetProgress()->GETRECT()->right = 0;
		}
	}

	D3DXVECTOR3 tempposition(0, 0, 0);
	D3DXMATRIX WorldMatrix, matProj, matViewPort, matView;
	D3DXMatrixTranslation(&WorldMatrix, m_vPosition.x, m_vPosition.y, m_vPosition.z);
	D3DVIEWPORT9 tempViewPort;
	g_pD3DDevice->GetViewport(&tempViewPort);
	D3DXMatrixIdentity(&matViewPort);
	matViewPort._11 = tempViewPort.Width / (float)2;
	matViewPort._22 = -(int)tempViewPort.Height / (float)2;
	matViewPort._33 = tempViewPort.MaxZ - tempViewPort.MinZ;
	matViewPort._41 = tempViewPort.X + tempViewPort.Width / (float)2;
	matViewPort._42 = tempViewPort.Y + tempViewPort.Height / (float)2;
	matViewPort._43 = tempViewPort.MinZ;
	g_pD3DDevice->GetTransform(D3DTS_PROJECTION, &matProj);
	g_pD3DDevice->GetTransform(D3DTS_VIEW, &matView);

	WorldMatrix = WorldMatrix * matView * matProj * matViewPort;
	D3DXVec3TransformCoord(&tempposition, &tempposition, &WorldMatrix);

	if (m_bTelePort)
	{
		m_pTelePortProgress->GetContainer()->setPosition(D3DXVECTOR3(WINSIZEX / 2 - 100, WINSIZEY / 2 + 100, 0));
		m_pTelePortProgress->GetProgress()->setPosition(D3DXVECTOR3(WINSIZEX / 2 - 100, WINSIZEY / 2 + 100, 0));
	}

	m_pTelePortProgress->update();

	if (m_bProgressing)
	{
		srand(GetTickCount());
		float time = rand() % 5;

		if(m_pTelePortProgress->GetProgress()->GETRECT()->right < m_pTelePortProgress->GetContainer()->GETRECT()->right)
		m_pTelePortProgress->GetProgress()->GETRECT()->right += time;

		if (m_pTelePortProgress->GetProgress()->GETRECT()->right >= m_pTelePortProgress->GetContainer()->GETRECT()->right)
		{
			m_bProgressing = false;
			m_fTelePortTime = m_pTelePortProgress->GetProgress()->GETRECT()->right;
		}
	}

	if (m_fTelePortTime && m_bTelePort)
	{
		if (!m_bProgressing)
		{
			setAnimation("Dance");
			m_fTelePortTime -= 0.5f;
			m_pTelePortProgress->GetProgress()->GETRECT()->right = m_fTelePortTime;
		}

		if (m_fTelePortTime <= 0)
		{
			m_vPosition = g_pCollisionManager->SetHeight(D3DXVECTOR3(-3118, 5224, -3642));
			m_vNextPosition = m_vPosition;
			g_pCameraManager->setCameraPos(D3DXVECTOR3(-3118, 5224, -3642));
			m_fTelePortTime = 0.0f;
			m_bTelePort = false;
		}
	}


	if (m_fHP <= 0)
	{
		m_fHP = 0;
		setAnimation("Death", false);
		if(!m_fRespwan)
			m_fRespwan = 10.0f;
		return;
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

	Check3DMousePointer();
}

void cPlayer::Render()
{
	POINT ptMouse;
	GetCursorPos(&ptMouse);
	ScreenToClient(g_hWnd, &ptMouse);
	g_pFontManager->TextFont(ptMouse.x, ptMouse.y, D3DXVECTOR3(255,0, 255), "3D %0.2f, %0.2f, %0.2f", (float)m_vNextPosition.x, (float)m_vNextPosition.y, (float)m_vNextPosition.z);

	g_pSkillManager->Render();

	ClickTargetRender();

	if (m_bTelePort)
	{
		m_pTelePortProgress->render();

		g_pFontManager->TextFont(WINSIZEX / 2 + 10, WINSIZEY / 2 + 80, D3DXVECTOR3(8, 130, 123), "귀환");

		if(!m_bProgressing)
		g_pFontManager->TextFont(WINSIZEX / 2 + 10, WINSIZEY / 2 + 120, D3DXVECTOR3(8, 130, 123),"%0.1f", m_fTelePortTime / 10);
	}

	g_pFontManager->TextFont(760,730, D3DXVECTOR3(255, 255, 255), "%0.1f",m_fRegainHP);
	g_pFontManager->TextFont(760, 750, D3DXVECTOR3(255, 255, 255), "%0.1f", m_fRegainMP);

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

	bool isCheck = false;
	if (m_pAshe)
	{
		m_vNextPosition = g_pCollisionManager->getRayPosition(isPick, m_pAshe->getPosition(),m_pAshe->getSphere(), m_pAshe->GetRadius()); //포지션 받고
		if (isPick)
		{
			m_pEnemy = (cAshe*)m_pAshe;
			isCheck = true;
		}
	}

	if (!isCheck)
	{
		for (int i = 0; i < m_pVecEnemy->size(); ++i)
		{
			m_vNextPosition = g_pCollisionManager->getRayPosition(isPick, (*m_pVecEnemy)[i]->getPosition(), ((cEnemy*)(*m_pVecEnemy)[i])->getSphere(), (*m_pVecEnemy)[i]->GetRadius()); //포지션 받고	
			if (isPick)
			{
				m_pEnemy = (cEnemy*)(*m_pVecEnemy)[i];
				break;
			}
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
