#include "stdafx.h"
#include "cCharacter.h"
#include "cRayPicking.h"


cCharacter::cCharacter()
	: m_vPosition(0, 0, 0)
	, m_fRotY(0.0f)
	, m_vNextPosition(0, 0, 0)
	, m_fSpeed(10.0f)
{
}


cCharacter::~cCharacter()
{
}

void cCharacter::Setup(const char* name)
{
	m_sName = name;
	g_pXfileManager->AddXfile(m_sName.c_str(), "character", (m_sName + ".x").c_str());
}

void cCharacter::Release()
{
}

void cCharacter::Update()
{
	//m_vNextPosition = m_vPosition;
	// if (GetKeyState('A') & 0x8000)
	// {
	// 	m_fRotY -= 0.1;
	// }
	// if (GetKeyState('D') & 0x8000)
	// {
	// 	m_fRotY += 0.1;
	// }
	//D3DXMATRIX mRotation;
	//D3DXMatrixRotationY(&mRotation, m_fRotY);
	//D3DXVec3TransformNormal(&m_vDirection, &D3DXVECTOR3(0, 0, 1), &mRotation);
	//if (GetKeyState('W') & 0x8000)
	//{
	//	m_vNextPosition += m_vDirection * m_fSpeed;
	//}
	//if (GetKeyState('S') & 0x8000)
	//{
	//	m_vNextPosition -= m_vDirection * m_fSpeed;
	//}
	// if (g_pKeyManager->IsOnceKeyDown('T'))
	// {
	// 	cRayPicking tmp;
	// 	for (int i = 0; i < m_pMap->size(); i += 3)
	// 	{
	// 		if (tmp.PickTri((*m_pMap)[i], (*m_pMap)[i + 1], (*m_pMap)[i + 2], g_pCameraManager->getEye(), m_vNextPosition))
	// 			break;
	// 	}
	// }

	GetCollision(m_vNextPosition.x, m_vNextPosition.y, m_vNextPosition.z);
	GetHeight(m_vPosition.x, m_vPosition.y, m_vPosition.z);
	g_pXfileManager->Update(m_sName.c_str());
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
	matWorld = matS * matR * matT;
	g_pXfileManager->Render(m_sName.c_str(), &matWorld);
}

bool cCharacter::GetHeight(float& x, float & y, float& z)
{
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
	D3DXVECTOR3 gogo = D3DXVECTOR3(x, y, z) - m_vPosition;
	if (D3DXVec3Length(&gogo) > m_fSpeed)
	{
		D3DXVec3Normalize(&gogo, &gogo);
		gogo *= m_fSpeed;
	}
	gogo += m_vPosition;
	D3DXVECTOR3 vRayPos(gogo.x, 100000.0f, gogo.z);
	D3DXVECTOR3 vRayDir(0, -1, 0);

	for (int i = 0; i < m_pCollisionMap->size(); ++i)
	{
		float u, v, f;
		if (D3DXVec3Length(&((*m_pCollisionMap)[i].vPosition - m_vPosition)) > 1000)continue;
		for (int j = 0; j < (*m_pCollisionMap)[i].vecTotalVertex.size(); j += 3)
		{
			if (D3DXIntersectTri(&(*m_pCollisionMap)[i].vecTotalVertex[j + 0],
				&(*m_pCollisionMap)[i].vecTotalVertex[j + 1],
				&(*m_pCollisionMap)[i].vecTotalVertex[j + 2],
				&vRayPos,
				&vRayDir,
				&u, &v, &f))
			{
				return true;
			}
		}
	}
	m_vPosition = gogo;
	return false;
}

