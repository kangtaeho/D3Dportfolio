#include "stdafx.h"
#include "cCollisionMap.h"


cCollisionMap::cCollisionMap()
{
}


cCollisionMap::~cCollisionMap()
{
}

void cCollisionMap::LoadSurface(OUT std::vector<D3DXVECTOR3>& vecSurface, IN const char * szFolder, IN const char * szFile, IN D3DXMATRIX* pMat)
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
