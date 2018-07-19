#include "stdafx.h"
#include "cMapEditer.h"
#include "cCharacter.h"


cMapEditer::cMapEditer()
	: m_pNowCircle(NULL)
	, m_fRadius(100.0f)
	, m_eNowState(MS_SETCIRCLE)
	, m_pPlayer(NULL)
{
}


cMapEditer::~cMapEditer()
{
}

HRESULT cMapEditer::Setup()
{
	//g_pXfileManager->AddXfile("Map", "summoner rift", "summoner_rift.x");

	D3DXCreateCylinder(g_pD3DDevice, 1.0f, 1.0f, CYLINDERHEIGHT, 20, 10, &m_pMesh, NULL);

	Mtl(true, true, true);

	m_pPlayer = new cCharacter;
	m_pPlayer->Setup("Teemo");

	g_pCollisionManager->Setup();

	return S_OK;
}

void cMapEditer::Release()
{
	for (auto p : m_stMap.vecCircle)
	{
		SAFE_DELETE(p);
	}
	m_stMap.vecCircle.clear();
	for (auto p : m_stMap.vecLine)
	{
		SAFE_DELETE(p);
	}
	m_stMap.vecLine.clear();
	SAFE_RELEASE(m_pMesh);
	SAFE_DELETE(m_pPlayer);
}

void cMapEditer::Update()
{
	if (getInMouse())return;
	if (g_pKeyManager->IsOnceKeyDown('1')) //충돌원 생성
	{
		m_eNowState = MS_SETCIRCLE;
	}
	if (g_pKeyManager->IsOnceKeyDown('2')) //충돌원 삭제
	{
		m_eNowState = MS_DELCIRCLE;
	}
	if (g_pKeyManager->IsOnceKeyDown('3')) //원연결해 라인 생성
	{
		m_eNowState = MS_SETLINE;
	}

	if (g_pKeyManager->IsOnceKeyDown('9')) //세이브
	{
		Save();
		g_pCollisionManager->LoadMap();
	}
	if (g_pKeyManager->IsOnceKeyDown('0')) //로드
	{
		Load();
		g_pCollisionManager->LoadMap();
		m_pNowCircle = NULL;
	}

	if (m_pNowCircle)
	{
		if (g_pKeyManager->IsStayKeyDown('W'))//선택된 원 크기 늘리기
		{
			m_pNowCircle->fRadius++;
		}
		if (g_pKeyManager->IsStayKeyDown('S'))//선택된 원 크기 줄이기
		{
			m_pNowCircle->fRadius--;
		}
		if (g_pKeyManager->IsStayKeyDown(VK_UP))//선택된 원 위치 조정  위
		{
			m_pNowCircle->mPosition.z++;
		}
		if (g_pKeyManager->IsStayKeyDown(VK_DOWN))//선택된 원 위치 조정  아래
		{
			m_pNowCircle->mPosition.z--;
		}
		if (g_pKeyManager->IsStayKeyDown(VK_LEFT))//선택된 원 위치 조정  좌
		{
			m_pNowCircle->mPosition.x--;
		}
		if (g_pKeyManager->IsStayKeyDown(VK_RIGHT))//선택된 원 위치 조정  우
		{
			m_pNowCircle->mPosition.x++;
		}
	}
	if (g_pKeyManager->IsStayKeyDown('Q'))//생성될 원 크기 늘리기
	{
		m_fRadius++;
	}
	if (g_pKeyManager->IsStayKeyDown('A'))//생성될 원 크기 줄이기
	{
		m_fRadius--;
	}

	if (g_pKeyManager->IsOnceKeyDown(VK_LBUTTON))
	{
		D3DXVECTOR3 tmpRay = getRay();
		STCIRCLE * tempCircle = NULL;
		switch (m_eNowState)
		{
		case MS_SETCIRCLE:
			if (findCircle(tmpRay, &tempCircle))//생성된 원 안에 선택하면
			{
				if (m_pNowCircle == tempCircle)//선택 취소
				{
					m_pNowCircle = NULL;
				}
				else
				{
					m_pNowCircle = tempCircle;//선택
				}
			}
			else
			{
				STCIRCLE* temp = new STCIRCLE;
				temp->iIndex = m_stMap.vecCircle.size();
				temp->mPosition = tmpRay;
				temp->fRadius = m_fRadius;
				temp->mPosition.y = 5000.0f;
				if (m_pNowCircle)//지금 선택된 원이 있으면 라인으로 연결해준다
				{
					STLINE* tempLine = new STLINE;
					tempLine->pCircles[0] = m_pNowCircle;
					tempLine->pCircles[1] = temp;
					D3DXVec3Cross(&tempLine->vCrossVector, &(m_pNowCircle->mPosition - temp->mPosition), &D3DXVECTOR3(0, 1, 0));
					D3DXVec3Normalize(&tempLine->vCrossVector, &tempLine->vCrossVector);
					m_pNowCircle->vecLines.push_back(tempLine);
					temp->vecLines.push_back(tempLine);
					m_stMap.vecLine.push_back(tempLine);
				}
				else
				{
					m_pNowCircle = temp;//아니면 그냥 원만 생성
				}
				m_stMap.vecCircle.push_back(temp);
				m_pNowCircle = temp;//생성한 원을 선택
			}
			break;
		case MS_DELCIRCLE:
			m_pNowCircle = NULL;
			if (findCircle(tmpRay, &tempCircle))//원을 클릭하면 삭제
			{
				deleteCircle(tempCircle);
			}
			break;
		case MS_SETLINE:
			if (findCircle(tmpRay, &tempCircle))
			{
				if (m_pNowCircle == tempCircle)//선택된 원과 같은 원을 선택하면 선택취소
				{
					m_pNowCircle = NULL;
				}
				else
				{
					if (m_pNowCircle)//선택된 원이 있으면
					{
						if (!isCircleInLine(tempCircle))//라인이 연결되어 있지 않으면 연결해준다
						{
							STLINE* tempLine = new STLINE;
							tempLine->pCircles[0] = m_pNowCircle;
							tempLine->pCircles[1] = tempCircle;
							D3DXVec3Cross(&tempLine->vCrossVector, &(m_pNowCircle->mPosition - tempCircle->mPosition), &D3DXVECTOR3(0, 1, 0));
							D3DXVec3Normalize(&tempLine->vCrossVector, &tempLine->vCrossVector);
							m_pNowCircle->vecLines.push_back(tempLine);
							tempCircle->vecLines.push_back(tempLine);
							m_stMap.vecLine.push_back(tempLine);
						}
					}
					else
					{
						m_pNowCircle = tempCircle;
					}
				}
			}
			break;
		default:
			break;
		}
	}

	if (g_pKeyManager->IsOnceKeyDown(VK_RBUTTON))
	{/*
		m_pPlayer->setNextPosition(getRay());
		m_pPlayer->setNextPosition(m_pAStar->PushDestination(m_pPlayer->getNextPosition(), m_pPlayer->GetRadius()));
*/
		//m_pAStar->Setup(*m_pPlayer->getPositionPointer(), m_pPlayer->GetRadius(), m_pAStar->PushDestination(getRay(), m_pPlayer->GetRadius()));
	}

	//=============================================================================
	//if (D3DXVec3Length(&(m_pPlayer->getNextPosition() - *m_pPlayer->getPositionPointer())) > 0.001f)
	//{
	//	int CircleIndex = 0;
	//	for (int i = 0; i < m_stMap.vecCircle.size(); ++i)
	//	{
	//		if (g_pCollisionManager->NextTickInCircle(
	//			g_pCollisionManager->NextPositionPerTick(*m_pPlayer->getPositionPointer(), m_pPlayer->getNextPosition(), m_pPlayer->GetSpeed()),
	//			m_pPlayer->GetRadius(),
	//			m_stMap.vecCircle[i]->mPosition,
	//			m_stMap.vecCircle[i]->fRadius))
	//		{
	//			m_pPlayer->setRotY(g_pCollisionManager->getDirectionWithCircle(
	//				*m_pPlayer->getPositionPointer(),
	//				m_pPlayer->getNextPosition(),
	//				m_stMap.vecCircle[i]->mPosition) + D3DX_PI / 2);
	//			*m_pPlayer->getPositionPointer() = g_pCollisionManager->MoveInCircle(
	//				*m_pPlayer->getPositionPointer(),
	//				g_pCollisionManager->NextPositionPerTick(*m_pPlayer->getPositionPointer(), m_pPlayer->getNextPosition(), m_pPlayer->GetSpeed()),
	//				m_pPlayer->GetRadius(),
	//				m_pPlayer->GetSpeed(),
	//				m_stMap.vecCircle[i]->mPosition,
	//				m_stMap.vecCircle[i]->fRadius);
	//			break;
	//		}
	//		CircleIndex++;
	//	}
	//	if (CircleIndex == m_stMap.vecCircle.size())
	//	{
	//		if (D3DXVec3Length(&(g_pCollisionManager->getVector2(*m_pPlayer->getPositionPointer()) - g_pCollisionManager->getVector2(m_pPlayer->getNextPosition()))) > m_pPlayer->GetSpeed())
	//			m_pPlayer->setRotY(g_pCollisionManager->getDirectionAngle(m_pPlayer->getNextPosition() - *m_pPlayer->getPositionPointer()) + D3DX_PI / 2);
	//		*m_pPlayer->getPositionPointer() = g_pCollisionManager->NextPositionPerTick(
	//			*m_pPlayer->getPositionPointer(),
	//			m_pPlayer->getNextPosition(),
	//			m_pPlayer->GetSpeed());
	//	}
	//	if (D3DXVec3Length(&(g_pCollisionManager->getVector2(*m_pPlayer->getPositionPointer()) - g_pCollisionManager->getVector2(m_pPlayer->getNextPosition()))) < m_pPlayer->GetSpeed())m_pPlayer->setNextPosition(*m_pPlayer->getPositionPointer());
	//}
	//float tempplayerradius = 100.0f;
	//m_pAStar->Update(*m_pPlayer->getPositionPointer(), tempplayerradius, m_pPlayer->GetSpeed(), m_pPlayer->GetRadius());
	//if(tempplayerradius != 100.0f)m_pPlayer->setRotY(tempplayerradius + D3DX_PI / 2);

	m_pPlayer->Update();
}

void cMapEditer::Render()
{
	D3DXMATRIX mat, matS, matR, matT, matT1;

	g_pD3DDevice->SetRenderState(D3DRS_LIGHTING, true);
	g_pD3DDevice->SetRenderState(D3DRS_ALPHATESTENABLE, false);

	for (auto p : m_stMap.vecCircle)
	{
		if (m_pNowCircle == p)
		{
			Mtl(false, true, false);
		}
		else
		{
			Mtl(false, false, true);
		}
		D3DXMatrixTranslation(&matT1, 0, 0, -CYLINDERHEIGHT / 2);
		D3DXMatrixScaling(&matS, p->fRadius, p->fRadius, 1.0f);
		D3DXMatrixRotationX(&matR, D3DX_PI / 2);
		D3DXMatrixTranslation(&matT, p->mPosition.x, p->mPosition.y, p->mPosition.z);
		mat = matT1 * matS * matR * matT;
		g_pD3DDevice->SetTransform(D3DTS_WORLD, &mat);
		m_pMesh->DrawSubset(0);
	}

	Mtl(false, false, false);
	D3DXMatrixIdentity(&mat);
	g_pD3DDevice->SetTransform(D3DTS_WORLD, &mat);
	for (auto p : m_stMap.vecLine)
	{
		LineRender(p);
	}

	if (m_eNowState == MS_SETCIRCLE)
	{
		Mtl(true, false, false);
		D3DXVECTOR3 tmpRay = getRay();
		D3DXMatrixTranslation(&matT1, 0, 0, -CYLINDERHEIGHT / 2);
		D3DXMatrixScaling(&matS, m_fRadius, m_fRadius, 1.0f);
		D3DXMatrixRotationX(&matR, D3DX_PI / 2);
		D3DXMatrixTranslation(&matT, tmpRay.x, 5000.0f, tmpRay.z);
		mat = matT1 * matS * matR * matT;
		g_pD3DDevice->SetTransform(D3DTS_WORLD, &mat);
		m_pMesh->DrawSubset(0);
	}

	g_pCollisionManager->MapRender();

/*
	D3DXMatrixRotationY(&matR, m_fPlayerDirecction);
	D3DXMatrixTranslation(&matT, m_vPlayerPosition.x, m_vPlayerPosition.y, m_vPlayerPosition.z);
	mat = matR * matT;
	g_pD3DDevice->SetTransform(D3DTS_WORLD, &mat);
	g_pXfileManager->FindXfile("Teemo")->Render(NULL);

	D3DXMatrixTranslation(&matT1, 0, 0, -CYLINDERHEIGHT / 2);
	D3DXMatrixScaling(&matS, m_fPlayerRadius, m_fPlayerRadius, 1.0f);
	D3DXMatrixRotationX(&matR, D3DX_PI / 2);
	mat = matT1 * matS * matR * matT;
	g_pD3DDevice->SetTransform(D3DTS_WORLD, &mat);
	g_pD3DDevice->SetRenderState(D3DRS_LIGHTING, false);
	g_pD3DDevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_WIREFRAME);
	m_pMesh->DrawSubset(0);
	g_pD3DDevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_SOLID);*/


	g_pD3DDevice->SetRenderState(D3DRS_LIGHTING, false);
	g_pD3DDevice->SetRenderState(D3DRS_ALPHATESTENABLE, true);
	g_pD3DDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);
	D3DXMatrixIdentity(&mat);
	D3DXMatrixIdentity(&matS);
	D3DXMatrixScaling(&matS, 300.0f, 300.0f, 300.0f);
	mat = matS;
	g_pD3DDevice->SetTransform(D3DTS_WORLD, &mat);
	//g_pXfileManager->FindXfile("Map")->Render(NULL);

	m_pPlayer->Render();
	g_pD3DDevice->SetTexture(0, NULL);

}

void cMapEditer::Save()
{
	std::string	sFullPath("map collision");
	sFullPath += (std::string("/") + std::string("map_collision.obj"));

	FILE* fp;
	fopen_s(&fp, sFullPath.c_str(), "w");

	char szTemp[1024];
	sprintf_s(szTemp, "#Collisions");
	fputs(szTemp, fp);

	for (int i = 0; i < m_stMap.vecCircle.size(); ++i)
	{
		sprintf_s(szTemp, "\nC %f %f %f %f %d", 
			m_stMap.vecCircle[i]->mPosition.x, 
			m_stMap.vecCircle[i]->mPosition.y, 
			m_stMap.vecCircle[i]->mPosition.z, 
			m_stMap.vecCircle[i]->fRadius, 
			m_stMap.vecCircle[i]->iIndex);
		fputs(szTemp, fp);
	}

	for (int i = 0; i < m_stMap.vecLine.size(); ++i)
	{
		sprintf_s(szTemp, "\nL %d %d %f %f %f",
			m_stMap.vecLine[i]->pCircles[0]->iIndex,
			m_stMap.vecLine[i]->pCircles[1]->iIndex,
			m_stMap.vecLine[i]->vCrossVector.x,
			m_stMap.vecLine[i]->vCrossVector.y,
			m_stMap.vecLine[i]->vCrossVector.z);
		fputs(szTemp, fp);
	}

	fclose(fp);
}

void cMapEditer::Load()
{
	std::string	sFullPath("map collision");
	sFullPath += (std::string("/") + std::string("map_collision.obj"));

	FILE* fp;
	fopen_s(&fp, sFullPath.c_str(), "r");
	if (!fp)return;

	for (auto p : m_stMap.vecCircle)
	{
		SAFE_DELETE(p);
	}
	m_stMap.vecCircle.clear();
	for (auto p : m_stMap.vecLine)
	{
		SAFE_DELETE(p);
	}
	m_stMap.vecLine.clear();

	while (true)
	{
		if (feof(fp))
			break;

		char szTemp[1024];
		fgets(szTemp, 1024, fp);

		if (szTemp[0] == '#')
		{
			continue;
		}
		else if (szTemp[0] == 'C')
		{
			STCIRCLE* temp = new STCIRCLE;
			sscanf_s(szTemp, "%*s %f %f %f %f %d", 
				&temp->mPosition.x, 
				&temp->mPosition.y, 
				&temp->mPosition.z, 
				&temp->fRadius, 
				&temp->iIndex);
			m_stMap.vecCircle.push_back(temp);
		}
		else if (szTemp[0] == 'L')
		{
			int sour, dest;
			float x, y, z;
			sscanf_s(szTemp, "%*s %d %d %f %f %f", &sour, &dest, &x, &y, &z);
			STLINE* temp = new STLINE;
			temp->pCircles[0] = m_stMap.vecCircle[sour];
			temp->pCircles[1] = m_stMap.vecCircle[dest];
			temp->vCrossVector = D3DXVECTOR3(x, y, z);
			temp->pCircles[0]->vecLines.push_back(temp);
			temp->pCircles[1]->vecLines.push_back(temp);
			m_stMap.vecLine.push_back(temp);
		}
	}

	fclose(fp);
}

void cMapEditer::Mtl(float R, float G, float B)
{
	ZeroMemory(&m_mtl, sizeof(D3DMATERIAL9));
	m_mtl.Ambient =	D3DXCOLOR(1.0f * R, 1.0f * G, 1.0f * B, 1.0f);
	m_mtl.Diffuse = D3DXCOLOR(1.0f * R, 1.0f * G, 1.0f * B, 1.0f);
	m_mtl.Specular = D3DXCOLOR(1.0f * R, 1.0f * G, 1.0f * B, 1.0f);

	g_pD3DDevice->SetMaterial(&m_mtl);
}

D3DXVECTOR3 cMapEditer::getRay()
{
	D3DXVECTOR3		m_vDirection;
	D3DXMATRIX invProj, invViewPort;
	D3DVIEWPORT9 tempViewPort;
	g_pD3DDevice->GetViewport(&tempViewPort);
	g_pD3DDevice->GetTransform(D3DTS_PROJECTION, &invProj);

	POINT ptMouse;
	GetCursorPos(&ptMouse);
	ScreenToClient(g_hWnd, &ptMouse);

	m_vDirection.x = ((2.0f * ptMouse.x) / tempViewPort.Width - 1.0f) / invProj._11;
	m_vDirection.y = ((-2.0f * ptMouse.y) / tempViewPort.Height + 1.0f) / invProj._22;
	m_vDirection.z = 1.0f;

	D3DXMATRIX invView;
	g_pD3DDevice->GetTransform(D3DTS_VIEW, &invView);
	D3DXMatrixInverse(&invView, 0, &invView);

	D3DXVec3TransformNormal(&m_vDirection, &m_vDirection, &invView);
	D3DXVec3Normalize(&m_vDirection, &m_vDirection);

	float u, v, f;
	//int bTemp;
	//DWORD face;
	//D3DXIntersect(g_pCollisionManager->getGround(),
	//	&g_pCameraManager->getCameraEye(),
	//	&m_vDirection,
	//	&bTemp, &face,
	//	&u, &v, &f, NULL, NULL);
	//if (bTemp)
	//{
	//	return g_pCameraManager->getCameraEye() + m_vDirection * f;
	//}
	return D3DXVECTOR3(0, 0, 0);
}

bool cMapEditer::findCircle(D3DXVECTOR3 Ray, STCIRCLE** nowClick)
{
	for (int i = 0; i < m_stMap.vecCircle.size(); ++i)
	{
		if (D3DXVec2Length(&D3DXVECTOR2(Ray.x - m_stMap.vecCircle[i]->mPosition.x, Ray.z - m_stMap.vecCircle[i]->mPosition.z)) < m_stMap.vecCircle[i]->fRadius)
		{
			*nowClick = m_stMap.vecCircle[i];
			return true;
		}
	}
	return false;
}

void cMapEditer::LineRender(STLINE * line)
{
	line->pCircles[0]->mPosition;
	line->pCircles[0]->fRadius;
	std::vector<ST_PC_VERTEX> tempCube;
	line->vCrossVector;
	ST_PC_VERTEX v;
	v.c = D3DCOLOR_XRGB(255, 255, 255);
	v.p = line->pCircles[0]->mPosition + line->pCircles[0]->fRadius * line->vCrossVector; v.p.y = 5000.0f; tempCube.push_back(v);
	v.p = line->pCircles[0]->mPosition + line->pCircles[0]->fRadius * line->vCrossVector; v.p.y = 5000.0f + CYLINDERHEIGHT - 10; tempCube.push_back(v);
	v.p = line->pCircles[1]->mPosition + line->pCircles[1]->fRadius * line->vCrossVector; v.p.y = 5000.0f + CYLINDERHEIGHT - 10; tempCube.push_back(v);//
	v.p = line->pCircles[0]->mPosition + line->pCircles[0]->fRadius * line->vCrossVector; v.p.y = 5000.0f; tempCube.push_back(v);
	v.p = line->pCircles[1]->mPosition + line->pCircles[1]->fRadius * line->vCrossVector; v.p.y = 5000.0f + CYLINDERHEIGHT - 10; tempCube.push_back(v);
	v.p = line->pCircles[1]->mPosition + line->pCircles[1]->fRadius * line->vCrossVector; v.p.y = 5000.0f; tempCube.push_back(v);//
	v.p = line->pCircles[0]->mPosition - line->pCircles[0]->fRadius * line->vCrossVector; v.p.y = 5000.0f; tempCube.push_back(v);
	v.p = line->pCircles[1]->mPosition - line->pCircles[1]->fRadius * line->vCrossVector; v.p.y = 5000.0f + CYLINDERHEIGHT - 10; tempCube.push_back(v);
	v.p = line->pCircles[0]->mPosition - line->pCircles[0]->fRadius * line->vCrossVector; v.p.y = 5000.0f + CYLINDERHEIGHT - 10; tempCube.push_back(v);//
	v.p = line->pCircles[0]->mPosition - line->pCircles[0]->fRadius * line->vCrossVector; v.p.y = 5000.0f; tempCube.push_back(v);
	v.p = line->pCircles[1]->mPosition - line->pCircles[1]->fRadius * line->vCrossVector; v.p.y = 5000.0f; tempCube.push_back(v);
	v.p = line->pCircles[1]->mPosition - line->pCircles[1]->fRadius * line->vCrossVector; v.p.y = 5000.0f + CYLINDERHEIGHT - 10; tempCube.push_back(v);//
	v.p = line->pCircles[0]->mPosition - line->pCircles[0]->fRadius * line->vCrossVector; v.p.y = 5000.0f; tempCube.push_back(v);
	v.p = line->pCircles[0]->mPosition - line->pCircles[0]->fRadius * line->vCrossVector; v.p.y = 5000.0f + CYLINDERHEIGHT - 10; tempCube.push_back(v);
	v.p = line->pCircles[0]->mPosition + line->pCircles[0]->fRadius * line->vCrossVector; v.p.y = 5000.0f + CYLINDERHEIGHT - 10; tempCube.push_back(v);//
	v.p = line->pCircles[0]->mPosition - line->pCircles[0]->fRadius * line->vCrossVector; v.p.y = 5000.0f; tempCube.push_back(v);
	v.p = line->pCircles[0]->mPosition + line->pCircles[0]->fRadius * line->vCrossVector; v.p.y = 5000.0f + CYLINDERHEIGHT - 10; tempCube.push_back(v);
	v.p = line->pCircles[0]->mPosition + line->pCircles[0]->fRadius * line->vCrossVector; v.p.y = 5000.0f; tempCube.push_back(v);//
	v.p = line->pCircles[1]->mPosition + line->pCircles[1]->fRadius * line->vCrossVector; v.p.y = 5000.0f; tempCube.push_back(v);
	v.p = line->pCircles[1]->mPosition + line->pCircles[1]->fRadius * line->vCrossVector; v.p.y = 5000.0f + CYLINDERHEIGHT - 10; tempCube.push_back(v);
	v.p = line->pCircles[1]->mPosition - line->pCircles[1]->fRadius * line->vCrossVector; v.p.y = 5000.0f + CYLINDERHEIGHT - 10; tempCube.push_back(v);//
	v.p = line->pCircles[1]->mPosition + line->pCircles[1]->fRadius * line->vCrossVector; v.p.y = 5000.0f; tempCube.push_back(v);
	v.p = line->pCircles[1]->mPosition - line->pCircles[1]->fRadius * line->vCrossVector; v.p.y = 5000.0f + CYLINDERHEIGHT - 10; tempCube.push_back(v);
	v.p = line->pCircles[1]->mPosition - line->pCircles[1]->fRadius * line->vCrossVector; v.p.y = 5000.0f; tempCube.push_back(v);//
	v.p = line->pCircles[0]->mPosition + line->pCircles[0]->fRadius * line->vCrossVector; v.p.y = 5000.0f + CYLINDERHEIGHT - 10; tempCube.push_back(v);
	v.p = line->pCircles[0]->mPosition - line->pCircles[0]->fRadius * line->vCrossVector; v.p.y = 5000.0f + CYLINDERHEIGHT - 10; tempCube.push_back(v);
	v.p = line->pCircles[1]->mPosition - line->pCircles[1]->fRadius * line->vCrossVector; v.p.y = 5000.0f + CYLINDERHEIGHT - 10; tempCube.push_back(v);//
	v.p = line->pCircles[0]->mPosition + line->pCircles[0]->fRadius * line->vCrossVector; v.p.y = 5000.0f + CYLINDERHEIGHT - 10; tempCube.push_back(v);
	v.p = line->pCircles[1]->mPosition - line->pCircles[1]->fRadius * line->vCrossVector; v.p.y = 5000.0f + CYLINDERHEIGHT - 10; tempCube.push_back(v);
	v.p = line->pCircles[1]->mPosition + line->pCircles[1]->fRadius * line->vCrossVector; v.p.y = 5000.0f + CYLINDERHEIGHT - 10; tempCube.push_back(v);//
	v.p = line->pCircles[0]->mPosition - line->pCircles[0]->fRadius * line->vCrossVector; v.p.y = 5000.0f; tempCube.push_back(v);
	v.p = line->pCircles[0]->mPosition + line->pCircles[0]->fRadius * line->vCrossVector; v.p.y = 5000.0f; tempCube.push_back(v);
	v.p = line->pCircles[1]->mPosition + line->pCircles[1]->fRadius * line->vCrossVector; v.p.y = 5000.0f; tempCube.push_back(v);//
	v.p = line->pCircles[0]->mPosition - line->pCircles[0]->fRadius * line->vCrossVector; v.p.y = 5000.0f; tempCube.push_back(v);
	v.p = line->pCircles[1]->mPosition + line->pCircles[1]->fRadius * line->vCrossVector; v.p.y = 5000.0f; tempCube.push_back(v);
	v.p = line->pCircles[1]->mPosition - line->pCircles[1]->fRadius * line->vCrossVector; v.p.y = 5000.0f; tempCube.push_back(v);

	g_pD3DDevice->SetFVF(ST_PC_VERTEX::FVF);
	g_pD3DDevice->DrawPrimitiveUP(D3DPT_TRIANGLELIST,
		tempCube.size() / 3,
		&tempCube[0],
		sizeof(ST_PC_VERTEX));
}

void cMapEditer::deleteCircle(STCIRCLE * circle)
{
	std::vector<STLINE*>::iterator tempILine;
	for (auto p : circle->vecLines)
	{
		for (int i = 0; i < 2; ++i)
		{
			if (circle == p->pCircles[i])continue;
			for (tempILine = p->pCircles[i]->vecLines.begin(); tempILine != p->pCircles[i]->vecLines.end();)
			{
				if (*tempILine == p)
				{
					p->pCircles[i]->vecLines.erase(tempILine);
					tempILine = p->pCircles[i]->vecLines.begin();
				}
				else
				{
					tempILine++;
				}
			}
		}
		for (tempILine = m_stMap.vecLine.begin(); tempILine != m_stMap.vecLine.end();)
		{
			if (*tempILine == p)
			{
				m_stMap.vecLine.erase(tempILine);
				tempILine = m_stMap.vecLine.begin();
			}
			else
			{
				tempILine++;
			}
		}
		STLINE* temp = p;
		p = nullptr;
		SAFE_DELETE(temp);
	}
	std::vector<STCIRCLE*>::iterator tempIcircle;
	for (tempIcircle = m_stMap.vecCircle.begin(); tempIcircle != m_stMap.vecCircle.end();)
	{
		if ((*tempIcircle)->iIndex > circle->iIndex)(*tempIcircle)->iIndex--;
		if (*tempIcircle == circle)
		{
			m_stMap.vecCircle.erase(tempIcircle);
			tempIcircle = m_stMap.vecCircle.begin();
		}
		else
		{
			tempIcircle++;
		}
	}

	SAFE_DELETE(circle);
}

bool cMapEditer::getInMouse()
{
	POINT ptMouse;
	RECT WinRC;
	GetCursorPos(&ptMouse);
	ScreenToClient(g_hWnd, &ptMouse);
	GetClientRect(g_hWnd, &WinRC);

	if (ptMouse.x > WinRC.left &&
		ptMouse.x < WinRC.right && 
		ptMouse.y > WinRC.top &&
		ptMouse.y < WinRC.bottom)return false;
	return true;
}

bool cMapEditer::isCircleInLine(STCIRCLE * circle)
{
	for (auto p : m_pNowCircle->vecLines)
	{
		for (int i = 0; i < 2; ++i)
		{
			if (p->pCircles[i] == circle)return true;
		}
	}

	return false;
}
