#include "stdafx.h"
#include "cCollisionMap.h"

void LoadSurface(OUT std::vector<D3DXVECTOR3>& vecSurface,
	IN const char* szFolder, IN const char* szFile,
	IN D3DXMATRIX* pMat = NULL);
void LoadCollisionSurface(OUT std::vector<stCollisionMap>& VecCollisionFace, IN const char * szFolder, IN const char * szFile, IN D3DXMATRIX* pMat);


cCollisionMap::cCollisionMap()
{
	D3DXMATRIX matWorld, matT, matS, matR;
	D3DXMatrixRotationY(&matR, D3DX_PI);
	D3DXMatrixScaling(&matS, 300.0f, 300.0f, 300.0f);
	matWorld = matR * matS;
	LoadSurface(m_pVecSurface, "map collision", "map_skp_sample.obj", &matWorld);
	LoadCollisionSurface(m_pVecCollisionFace, "map collision", "map_collision.obj", &matWorld);
}


cCollisionMap::~cCollisionMap()
{
}

void LoadSurface(OUT std::vector<D3DXVECTOR3>& vecSurface, IN const char * szFolder, IN const char * szFile, IN D3DXMATRIX* pMat)
{
	std::vector<D3DXVECTOR3>	vecV;

	std::string	sFullPath(szFolder);
	sFullPath += (std::string("/") + std::string(szFile));

	FILE* fp;
	fopen_s(&fp, sFullPath.c_str(), "r");

	std::string sMtlName;
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
	}

	fclose(fp);

	if (pMat)
	{
		for (int i = 0; i < vecSurface.size(); i++)
		{
			D3DXVec3TransformCoord(&vecSurface[i], &vecSurface[i], pMat);
		}
	}
}

void LoadCollisionSurface(OUT std::vector<stCollisionMap>& VecCollisionFace, IN const char * szFolder, IN const char * szFile, IN D3DXMATRIX* pMat)
{
	std::vector<D3DXVECTOR3>	vecV;

	std::string	sFullPath(szFolder);
	sFullPath += (std::string("/") + std::string(szFile));

	FILE* fp;
	fopen_s(&fp, sFullPath.c_str(), "r");

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
		else if (szTemp[0] == 'v')
		{
			if (szTemp[1] == ' ')
			{
				float x, y, z;
				sscanf_s(szTemp, "%*s %f %f %f", &x, &y, &z);
				vecV.push_back(D3DXVECTOR3(-x, y, z));
			}
		}
		else if (szTemp[0] == 'g')
		{
			stCollisionMap tempcolmap;
			char temp[1024];
			sscanf_s(szTemp, "%*s %s", temp, 1024);
			tempcolmap.sObjName = temp;
			VecCollisionFace.push_back(tempcolmap);
		}
		else if (szTemp[0] == 'f')
		{
			int nIndex[3];
			sscanf_s(szTemp, "%*s %d/%*d/%*d %d/%*d/%*d %d/%*d/%*d",
				&nIndex[0], &nIndex[1], &nIndex[2]);

			for (int i = 0; i < 3; i++)
			{
				VecCollisionFace.back().vecTotalVertex.push_back(vecV[nIndex[i] - 1]);
			}
		}
	}
	fclose(fp);

	for (int i = 0; i < VecCollisionFace.size(); ++i)
	{
		VecCollisionFace[i].vPosition = D3DXVECTOR3(0, 0, 0);
		for (int j = 0; j < VecCollisionFace[i].vecTotalVertex.size(); ++j)
		{
			VecCollisionFace[i].vPosition.x += VecCollisionFace[i].vecTotalVertex[j].x;
			VecCollisionFace[i].vPosition.y += VecCollisionFace[i].vecTotalVertex[j].y;
			VecCollisionFace[i].vPosition.z += VecCollisionFace[i].vecTotalVertex[j].z;
		}
		VecCollisionFace[i].vPosition /= (float)VecCollisionFace[i].vecTotalVertex.size();
	}

	for (int j = 0; j < VecCollisionFace.size(); ++j)
	{
		if (pMat)
		{
			D3DXVec3TransformCoord(&VecCollisionFace[j].vPosition, &VecCollisionFace[j].vPosition, pMat);
			for (int i = 0; i < VecCollisionFace[j].vecTotalVertex.size(); i++)
			{
				D3DXVec3TransformCoord(&VecCollisionFace[j].vecTotalVertex[i], &VecCollisionFace[j].vecTotalVertex[i], pMat);
			}
		}
	}
}

void cCollisionMap::Render()
{
<<<<<<< HEAD
	D3DXMATRIX world;
	D3DXMatrixIdentity(&world);
	g_pD3DDevice->SetTransform(D3DTS_WORLD, &world);
	//g_pD3DDevice->SetTexture(0, NULL);
=======
	g_pD3DDevice->SetRenderState(D3DRS_LIGHTING, false);
	D3DXMATRIX m_matWorld;
	D3DXMatrixIdentity(&m_matWorld);
	g_pD3DDevice->SetTransform(D3DTS_WORLD, &m_matWorld);
	g_pD3DDevice->SetTexture(0, NULL);
	g_pD3DDevice->SetFVF(D3DFVF_XYZ);
>>>>>>> 7f467cce3eae88d1d63b8b2de9887e7e73b9c9f3
	g_pD3DDevice->DrawPrimitiveUP(D3DPT_TRIANGLELIST,
		m_pVecSurface.size() / 3,
		&m_pVecSurface[0],
		sizeof(D3DXVECTOR3));
}