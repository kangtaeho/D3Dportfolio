#include "stdafx.h"
#include "cCharacter.h"
#include "cRayPicking.h"


cCharacter::cCharacter()
	: m_vPosition(0, 0, 0)
	, m_fRotY(0.0f)
	, m_vNextPosition(0, 0, 0)
	, m_fSpeed(10.0f)
	, m_pSkinnedMesh(NULL)
{
	D3DXMatrixIdentity(&m_matWorld);
}


cCharacter::~cCharacter()
{
}

void cCharacter::Setup(const char* name)
{
	m_pSkinnedMesh = g_pXfileManager->AddXfile(name, "character", (std::string(name) + ".x").c_str());
	m_pSkinnedMesh->CloneAniController(&m_pAnimController);
}

void cCharacter::Release()
{
}

void cCharacter::Update()
{
	GetCollision(m_vNextPosition.x, m_vNextPosition.y, m_vNextPosition.z); //벽충돌
	GetHeight(m_vPosition.x, m_vPosition.y, m_vPosition.z);				   // 높이판정			
}

void cCharacter::Render()
{
	D3DXMATRIX	matWorld, matS, matR, matT;
	D3DXMatrixIdentity(&matWorld);
	D3DXMatrixIdentity(&matS);
	D3DXMatrixIdentity(&matR);
	D3DXMatrixIdentity(&matT);
	D3DXMatrixRotationY(&matR, m_fRotY);
	D3DXMatrixTranslation(&matT, m_vPosition.x, m_vPosition.y, m_vPosition.z);
	m_matWorld = matS * matR * matT;
	g_pD3DDevice->SetTransform(D3DTS_WORLD, &m_matWorld);
	//애니메이션을 넣을때 cAction을 상속받은 후 아래처럼 사용
	UpdateAnimation();
	m_pSkinnedMesh->Update(m_pAnimController);
}

bool cCharacter::GetHeight(float& x, float & y, float& z)
{

	if (!m_pMap) return false;

	D3DXVECTOR3 vRayPos(x, 100000.0f, z);
	D3DXVECTOR3 vRayDir(0, -1, 0);

	for (int i = 0; i < m_pMap->size(); i += 3)
	{
		float u, v, f;
		if (D3DXIntersectTri(&(*m_pMap)[i + 0],
			&(*m_pMap)[i + 1],
			&(*m_pMap)[i + 2],
			&vRayPos,
			&vRayDir,
			&u, &v, &f))
		{
			y = 100000.0f - f;
			return true;
		}
	}

	return false;
}

bool cCharacter::GetCollision(float& x, float & y, float& z)
{
	if (!m_pCollisionMap) return false;



	D3DXVECTOR3 gogo = D3DXVECTOR3(x, y, z) - m_vPosition;		//현재 위치에서 도착 위치까지의 백터
	if (D3DXVec3Length(&gogo) > m_fSpeed)						//백터의 길이가 틱당 스피드보다 길때
	{
		D3DXVec3Normalize(&gogo, &gogo);						//노멀라이즈로 길이를 1로 만들어주고
		gogo *= m_fSpeed;										//스피드를 곱해 스피드만큼 이동

		m_fRotY = GetAngle(m_vPosition, m_vNextPosition);

	}
	gogo += m_vPosition;										//gogo를 도착 위치 백터로 바꿈
	D3DXVECTOR3 vRayPos(gogo.x, 100000.0f, gogo.z);				//도착 위치 하늘이 레이 위치
	D3DXVECTOR3 vRayDir(0, -1, 0);								//레이는 수직 아래로 

	//for (int i = 0; i < m_pCollisionMap->size(); ++i)
	//{
	//	float u, v, f;

	//	if (D3DXVec3Length(&((*m_pCollisionMap)[i].vPosition - m_vPosition)) > 1000) continue;	//충돌맵과 거리가 멀면 컨티뉴(1000이상)
	//	for (int j = 0; j < (*m_pCollisionMap)[i].vecTotalVertex.size(); j += 3)
	//	{
	//		if (D3DXIntersectTri(&(*m_pCollisionMap)[i].vecTotalVertex[j + 0],
	//			&(*m_pCollisionMap)[i].vecTotalVertex[j + 1],
	//			&(*m_pCollisionMap)[i].vecTotalVertex[j + 2],
	//			&vRayPos,
	//			&vRayDir,
	//			&u, &v, &f))			//충돌맵과 인터섹트트라이
	//		{
	//			D3DXVECTOR3(x, y, z) = m_vPosition;
	//			return true;
	//		}
	//	}
	//}
	m_vPosition = gogo;		//충돌이 안됬으면 gogo로 이동
	return false;
}

