#include "stdafx.h"
#include "cCollisionManager.h"

cCollisionManager::cCollisionManager()
	: m_pCylinder(NULL)
	, m_pMapMesh(NULL)
{
	D3DXCreateCylinder(g_pD3DDevice, 1.0f, 1.0f, CYLINDERHEIGHT, 20, 10, &m_pCylinder, NULL);

	FILE* fp;
	fopen_s(&fp, "map collision/file_list.txt", "r");

	while (!feof(fp))
	{
		char szTemp[1024];
		fgets(szTemp, 1024, fp);
		if(szTemp[strlen(szTemp) - 1] == '\n')
			szTemp[strlen(szTemp) - 1] = '\0';
		AllFileName.push_back(szTemp);
	}
	
	fclose(fp);

	for (int i = 0; i < AllFileName.size(); ++i)
	{
		std::string allFath = "map collision/";
		allFath += AllFileName[i];
		FILE* fp;
		fopen_s(&fp, allFath.c_str(), "r");
		fseek(fp, 0, SEEK_END);
		int temp = ftell(fp);
		AllFileSize.push_back(temp);
		fclose(fp);
	}
	LoadFileSize.resize(AllFileSize.size());
}

cCollisionManager::~cCollisionManager()
{
}

bool cCollisionManager::Setup(int& allfilesize, int& loadfilesize)
{
	int Index = 0;
	while (Index < AllFileName.size())
	{
		if(LoadFileSize[Index] == AllFileSize[Index])Index++;
		else break;
	}
		
	if (AllFileSize.size() <= Index)return true;

	std::string allFath = "map collision/";
	allFath += AllFileName[Index];
	FILE* fp;
	fopen_s(&fp, allFath.c_str(), "r");
	fseek(fp, LoadFileSize[Index], SEEK_SET);

	int aaaaa = ftell(fp);
	if ("map_collision.obj" == AllFileName[Index] && !ftell(fp))
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
	}

	char szTemp[1024];
	fgets(szTemp, 1024, fp);

	if (szTemp[0] == '#')
	{

	}
	else if (szTemp[0] == 'v')
	{
		if (szTemp[1] == ' ')
		{
			float x, y, z;
			sscanf_s(szTemp, "%*s %f %f %f", &x, &y, &z);
			vecV.push_back(D3DXVECTOR3(-x, y, z));
		}
	}
	else if (szTemp[0] == 'f')
	{
		int nIndex[3];
		sscanf_s(szTemp, "%*s %d/%*d/%*d %d/%*d/%*d %d/%*d/%*d",
			&nIndex[0], &nIndex[1], &nIndex[2]);

		for (int i = 0; i < 3; i++)
		{
			vecSurface.push_back(vecV[nIndex[i] - 1]);
		}
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

	LoadFileSize[Index] = ftell(fp);

	fclose(fp);

	if (LoadFileSize[Index] == AllFileSize[Index] && "map_collision.obj" != AllFileName[Index])
	{
		D3DXMATRIX matWorld, matT, matS, matR;
		D3DXMatrixRotationY(&matR, D3DX_PI);
		D3DXMatrixScaling(&matS, 300.0f, 300.0f, 300.0f);
		matWorld = matR * matS;

		for (int i = 0; i < vecSurface.size(); i++)
		{
			D3DXVec3TransformCoord(&vecSurface[i], &vecSurface[i], &matWorld);
		}

		std::vector<ST_PC_VERTEX> tempVertex;
		for (int i = 0; i < vecSurface.size(); ++i)
		{
			ST_PC_VERTEX tempPC;
			tempPC.p = vecSurface[i];
			tempPC.c = D3DCOLOR_XRGB(255, 255, 255);
			tempVertex.push_back(tempPC);
		}

		D3DXCreateMeshFVF(tempVertex.size() / 3,
			tempVertex.size(),
			D3DXMESH_MANAGED,
			ST_PC_VERTEX::FVF,
			g_pD3DDevice,
			&m_pMapMesh);

		ST_PC_VERTEX* pV = NULL;
		m_pMapMesh->LockVertexBuffer(0, (LPVOID*)&pV);
		memcpy(pV, &tempVertex[0], sizeof(ST_PC_VERTEX) * tempVertex.size());
		m_pMapMesh->UnlockVertexBuffer();

		WORD* pI = NULL;
		m_pMapMesh->LockIndexBuffer(0, (LPVOID*)&pI);
		for (int i = 0; i < tempVertex.size(); i++)
		{
			pI[i] = i;
		}
		m_pMapMesh->UnlockIndexBuffer();

		DWORD* pA = NULL;
		m_pMapMesh->LockAttributeBuffer(0, &pA);
		for (int i = 0; i < tempVertex.size() / 3; i++)
		{
			pA[i] = 0;
		}
		m_pMapMesh->UnlockAttributeBuffer();


		std::vector<DWORD>	vecAdj(tempVertex.size());
		m_pMapMesh->GenerateAdjacency(0.0f, &vecAdj[0]);

		m_pMapMesh->OptimizeInplace(
			D3DXMESHOPT_ATTRSORT |
			D3DXMESHOPT_COMPACT,
			&vecAdj[0],
			0, 0, 0);

		vecSurface.clear();
		vecV.clear();
	}

	allfilesize = loadfilesize = 0;
	for (int i = 0; i < AllFileName.size(); ++i)
	{
		allfilesize += AllFileSize[i];
		loadfilesize += LoadFileSize[i];
	}
	if (allfilesize == loadfilesize)return true;
	return false;
}

void cCollisionManager::Release()
{
	SAFE_RELEASE(m_pMapMesh);
	SAFE_RELEASE(m_pCylinder);
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
}

void cCollisionManager::LoadMap()
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

void cCollisionManager::CylinderRender(D3DXVECTOR3 position, float radius)
{
	g_pD3DDevice->SetTexture(0, NULL);

	D3DMATERIAL9 m_mtl;
	ZeroMemory(&m_mtl, sizeof(D3DMATERIAL9));
	m_mtl.Ambient = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	m_mtl.Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	m_mtl.Specular = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	g_pD3DDevice->SetMaterial(&m_mtl);

	D3DXMATRIX mat, matS, matR, matT, matT1;
	D3DXMatrixTranslation(&matT, position.x, 5000.0f, position.z);
	D3DXMatrixTranslation(&matT1, 0, 0, -CYLINDERHEIGHT / 2);
	D3DXMatrixScaling(&matS, radius, radius, 1.0f);
	D3DXMatrixRotationX(&matR, D3DX_PI / 2);
	mat = matT1 * matS * matR * matT;
	g_pD3DDevice->SetTransform(D3DTS_WORLD, &mat);
	g_pD3DDevice->SetRenderState(D3DRS_LIGHTING, false);
	g_pD3DDevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_WIREFRAME);
	m_pCylinder->DrawSubset(0);
	g_pD3DDevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_SOLID);
}

void cCollisionManager::MapRender()
{
	g_pD3DDevice->SetRenderState(D3DRS_LIGHTING, true);
	D3DMATERIAL9 m_mtl;
	ZeroMemory(&m_mtl, sizeof(D3DMATERIAL9));
	m_mtl.Ambient = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	m_mtl.Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	m_mtl.Specular = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	g_pD3DDevice->SetMaterial(&m_mtl);
	D3DXMATRIX m_matWorld;
	D3DXMatrixIdentity(&m_matWorld);
	g_pD3DDevice->SetTransform(D3DTS_WORLD, &m_matWorld);
	g_pD3DDevice->SetTexture(0, NULL);
	g_pD3DDevice->SetFVF(D3DFVF_XYZ);
	m_pMapMesh->DrawSubset(0);
}

D3DXVECTOR3 cCollisionManager::SetHeight(D3DXVECTOR3 position)
{
	if (!m_pMapMesh) return position;
	
	D3DXVECTOR3 vRayPos(position.x, 100000.0f, position.z);
	D3DXVECTOR3 vRayDir(0, -1, 0);
	
	float u, v, f;
	int isGround;
	D3DXIntersect(m_pMapMesh,
		&vRayPos,
		&vRayDir,
		&isGround, NULL,
		&u, &v, &f, NULL, NULL);
	if (isGround)
	{
		position.y = 100000.0f - f;
	}
	return position;
}

D3DXVECTOR3 cCollisionManager::getRayPosition(int bTemp, LPD3DXMESH Mesh)
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
	DWORD face;
	LPD3DXMESH tempMesh = m_pMapMesh;
	if (Mesh)tempMesh = Mesh;
	D3DXIntersect(tempMesh,
		&g_pCameraManager->getEye(),
		&m_vDirection,
		&bTemp, &face,
		&u, &v, &f, NULL, NULL);
	if (bTemp)
	{
		return g_pCameraManager->getEye() + m_vDirection * f;
	}
	else
	{
		int temptemptemp = 0;
		D3DXIntersect(m_pMapMesh,
			&g_pCameraManager->getEye(),
			&m_vDirection,
			&temptemptemp, &face,
			&u, &v, &f, NULL, NULL);

		return g_pCameraManager->getEye() + m_vDirection * f;
	}
	return D3DXVECTOR3(0, 0, 0);
}

D3DXVECTOR3 cCollisionManager::NextPositionPerTick(D3DXVECTOR3 position, D3DXVECTOR3 nextposition, float speed)
{
	D3DXVECTOR3 TickPosition = getVector2(nextposition) - getVector2(position);
	D3DXVec3Normalize(&TickPosition, &TickPosition);
	TickPosition *= speed;
	return SetHeight(getVector2(position) + TickPosition);
}

float cCollisionManager::getDirectionWithCircle(D3DXVECTOR3 position, D3DXVECTOR3 nextposition, D3DXVECTOR3 circleposition)
{
	D3DXVECTOR3 tempDirection = getVector2(position) - getVector2(circleposition);
	D3DXVec3Cross(&tempDirection, &D3DXVECTOR3(0, 1, 0), &tempDirection);
	if (WherePositionLR(circleposition, position, nextposition))tempDirection *= -1;
	return getDirectionAngle(tempDirection);
}

bool cCollisionManager::NextTickInCircle(D3DXVECTOR3 tickposition, float radius, D3DXVECTOR3 circleposition, float circleradius)
{
	if (D3DXVec3Length(&(getVector2(tickposition) - getVector2(circleposition))) < radius + circleradius)return true;
	else return false;
}

D3DXVECTOR3 cCollisionManager::MoveInCircle(D3DXVECTOR3 position, D3DXVECTOR3 tickposition, float radius, float speed, D3DXVECTOR3 circleposition, float circleradius)
{
	float radian = speed / (radius + circleradius);
	if (WherePositionLR(circleposition, position, tickposition))
	{
		radian = -radian;
	}

	D3DXMATRIX mat;
	D3DXMatrixRotationY(&mat, radian);
	D3DXVECTOR3 NextTickPosition;
	D3DXVec3TransformCoord(&NextTickPosition, &(getVector2(position) - getVector2(circleposition)), &mat);
	NextTickPosition += getVector2(circleposition);
	return SetHeight(NextTickPosition);
}

float cCollisionManager::getDirectionAngle(D3DXVECTOR3 v)
{
	float x = v.x - 0;
	float y = v.z - 0;

	float distance = sqrtf(x * x + y * y);

	float angle = acosf(x / distance);

	if (v.z > 0)
	{
		angle = D3DX_PI * 2 - angle;
	}

	return angle;
}

float cCollisionManager::getAngleWithVecters(D3DXVECTOR3 first, D3DXVECTOR3 mid, D3DXVECTOR3 end)
{
	if (first == mid || mid == end)return 0.0f;

	D3DXMATRIX mat, matR, matT;
	D3DXMatrixTranslation(&matT, -getVector2(mid).x, -getVector2(mid).y, -getVector2(mid).z);
	D3DXMatrixRotationY(&matR, -getDirectionAngle(getVector2(end) - getVector2(mid)));

	D3DXVec3TransformCoord(&mid, &getVector2(mid), &matT);
	D3DXVec3TransformNormal(&end, &end, &matR);

	D3DXVECTOR3 tempTick;
	D3DXVec3TransformCoord(&tempTick, &getVector2(first), &matT);
	D3DXVec3TransformNormal(&tempTick, &tempTick, &matR);

	return getDirectionAngle(tempTick);
}

bool cCollisionManager::CollisionUnit(D3DXVECTOR3 tickposition, float radius, D3DXVECTOR3 unitposition, float unitradius)
{
	if (D3DXVec3Length(&(getVector2(tickposition) - getVector2(unitposition))) < radius + unitradius)return true;
	return false;
}

bool cCollisionManager::WherePositionLR(D3DXVECTOR3 position, D3DXVECTOR3 vecterStart, D3DXVECTOR3 vecterEnd)
{
	D3DXMATRIX mat, matR, matT;
	D3DXMatrixTranslation(&matT, -getVector2(vecterStart).x, -getVector2(vecterStart).y, -getVector2(vecterStart).z);
	D3DXMatrixRotationY(&matR, -getDirectionAngle(getVector2(vecterEnd) - getVector2(vecterStart)));

	D3DXVECTOR3 tempTick;
	D3DXVec3TransformCoord(&tempTick, &getVector2(position), &matT);
	D3DXVec3TransformNormal(&tempTick, &tempTick, &matR);

	if (tempTick.z > 0) return true;	//¿ÞÂÊ
	else return false;					//¿À¸¥ÂÊ
}

bool cCollisionManager::WherePositionInVector(D3DXVECTOR3 position, D3DXVECTOR3 vecterStart, D3DXVECTOR3 vecterEnd)
{
	D3DXMATRIX mat, matR, matT;
	D3DXMatrixTranslation(&matT, -getVector2(vecterStart).x, -getVector2(vecterStart).y, -getVector2(vecterStart).z);
	D3DXMatrixRotationY(&matR, -getDirectionAngle(getVector2(vecterEnd) - getVector2(vecterStart)));

	D3DXVec3TransformCoord(&vecterStart, &getVector2(vecterStart), &matT);
	D3DXVec3TransformCoord(&vecterEnd, &getVector2(vecterEnd), &matT);
	D3DXVec3TransformNormal(&vecterEnd, &vecterEnd, &matR);

	D3DXVECTOR3 tempTick;
	D3DXVec3TransformCoord(&tempTick, &getVector2(position), &matT);
	D3DXVec3TransformNormal(&tempTick, &tempTick, &matR);

	if (vecterStart.x < tempTick.x && tempTick.x < vecterEnd.x)return true;
	return false;
}

D3DXVECTOR3 cCollisionManager::WherePositionposition(D3DXVECTOR3 position, D3DXVECTOR3 vecterStart, D3DXVECTOR3 vecterEnd)
{
	D3DXMATRIX mat, matR, matT;
	D3DXMatrixTranslation(&matT, -getVector2(vecterStart).x, -getVector2(vecterStart).y, -getVector2(vecterStart).z);
	D3DXMatrixRotationY(&matR, -getDirectionAngle(getVector2(vecterEnd) - getVector2(vecterStart)));

	D3DXVec3TransformCoord(&vecterStart, &getVector2(vecterStart), &matT);
	D3DXVec3TransformCoord(&vecterEnd, &getVector2(vecterEnd), &matT);
	D3DXVec3TransformNormal(&vecterEnd, &vecterEnd, &matR);

	D3DXVECTOR3 tempTick;
	D3DXVec3TransformCoord(&tempTick, &getVector2(position), &matT);
	D3DXVec3TransformNormal(&tempTick, &tempTick, &matR);
	
	return tempTick;
}

bool cCollisionManager::IsCrossingVector(D3DXVECTOR3 position1_1, D3DXVECTOR3 position1_2, D3DXVECTOR3 position2_1, D3DXVECTOR3 position2_2)
{
	if (WherePositionLR(position1_1, position2_1, position2_2) != WherePositionLR(position1_2, position2_1, position2_2) &&
		WherePositionLR(position2_1, position1_1, position1_2) != WherePositionLR(position2_2, position1_1, position1_2))return true;
	return false;
}

D3DXVECTOR3 cCollisionManager::CrossingVectorPosition(D3DXVECTOR3 position1_1, D3DXVECTOR3 position1_2, D3DXVECTOR3 position2_1, D3DXVECTOR3 position2_2)
{
	return D3DXVECTOR3();
}

float cCollisionManager::CrossingVectorLength(D3DXVECTOR3 position1_1, D3DXVECTOR3 position1_2, D3DXVECTOR3 position2_1, D3DXVECTOR3 position2_2)
{
	D3DXMATRIX mat, matR, matT;
	D3DXMatrixTranslation(&matT, -getVector2(position1_1).x, -getVector2(position1_1).y, -getVector2(position1_1).z);
	D3DXMatrixRotationY(&matR, -getDirectionAngle(getVector2(position1_2) - getVector2(position1_1)));

	D3DXVec3TransformCoord(&position1_1, &getVector2(position1_1), &matT);
	D3DXVec3TransformCoord(&position1_2, &getVector2(position1_2), &matT);
	D3DXVec3TransformNormal(&position1_2, &position1_2, &matR);

	D3DXVec3TransformCoord(&position2_1, &getVector2(position2_1), &matT);
	D3DXVec3TransformNormal(&position2_1, &position2_1, &matR);
	D3DXVec3TransformCoord(&position2_2, &getVector2(position2_2), &matT);
	D3DXVec3TransformNormal(&position2_2, &position2_2, &matR);

	D3DXVECTOR3 tempLength = position2_2 - position2_1;
	float distance = tempLength.z;
	D3DXVec3Normalize(&tempLength, &tempLength);
	tempLength *= abs(position2_1.z) / distance;

	return D3DXVec3Length(&tempLength);
}

//=============================================================

//
//bool cMapEditer::GoCircle(D3DXVECTOR3& direction)
//{
//	for (auto p : m_vecCircle)
//	{
//		D3DXVECTOR3 temp2direction(direction.x - p->mPosition.x, 0, direction.z - p->mPosition.z);
//		D3DXVECTOR3 tempPlayer(m_vPlayerPosition.x - p->mPosition.x, 0, m_vPlayerPosition.z - p->mPosition.z);
//		if (D3DXVec3Length(&temp2direction) < m_fPlayerRadius + p->fRadius)
//		{
//			float radian = PLAYERSPEED / (m_fPlayerRadius + p->fRadius);
//
//			D3DXMATRIX tempmat;
//			D3DXMatrixRotationY(&tempmat, radian);
//			D3DXVec3TransformCoord(&temp2direction, &tempPlayer, &tempmat);
//			direction = p->mPosition + temp2direction;
//			//temp2direction = direction - p->mPosition;
//			//D3DXVec3Cross(&temp2direction, &temp2direction, &D3DXVECTOR3(0, 1, 0));
//			m_fPlayerDirecction = atan2f(p->fRadius + m_fPlayerRadius, m_fPlayerRadius);
//			return true;
//		}
//	}
//	return false;
//}
