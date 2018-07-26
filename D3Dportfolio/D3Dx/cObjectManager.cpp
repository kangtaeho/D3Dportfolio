#include "stdafx.h"
#include "cObjectManager.h"
#include "cObject.h"


cObjectManager::cObjectManager()
{
}


cObjectManager::~cObjectManager()
{
}

void cObjectManager::Setup()
{
	std::string	sFullPath("NPC Object");
	sFullPath += (std::string("/") + std::string("Object.obj"));

	FILE* fp;
	fopen_s(&fp, sFullPath.c_str(), "r");
	if (!fp)return;
	char szTemp[1024];
	sprintf_s(szTemp, "#Object");
	fputs(szTemp, fp);

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
		else if (szTemp[0] == 'O')
		{
			cObject* temp = new cObject;
			char name[1024];
			D3DXVECTOR3 position;
			float scale;
			float radius;
			float rotY;
			int blue;
			sscanf_s(szTemp, "%*s %f %f %f %f %f %f %i",
				&position.x,
				&position.y,
				&position.z,
				&scale,
				&radius,
				&rotY,
				&blue);
			fgets(szTemp, 1024, fp);
			sscanf_s(szTemp, "%s", &name, sizeof(name));

			temp->Setup(name, blue, scale);
			*temp->getPositionPointer() = position;
			temp->SetRadius(radius);
			temp->SetRotY(rotY);

			m_vecObject.push_back(temp);
		}
	}

	fclose(fp);

	
}

void cObjectManager::Release()
{
	for (int i = 0; i < m_vecObject.size(); ++i)
	{
		m_vecObject[i]->Release();
	}
}

void cObjectManager::Update()
{
	m_vecAllEnemy.clear();
	for (int i = 0; i < m_vecObject.size(); ++i)
	{
		m_vecObject[i]->Update();
		if (!((cObject*)m_vecObject[i])->getBlue())
		{
			m_vecAllEnemy.push_back(m_vecObject[i]);
		}
	}
}

void cObjectManager::Render()
{
	for (int i = 0; i < m_vecObject.size(); ++i)
	{
		m_vecObject[i]->Render();
	}
}
