#include "stdafx.h"
#include "cObjectManager.h"
#include "cObject.h"
#include "cEnemy.h"
#include "cPlayer.h"


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

			*temp->getPositionPointer() = position;
			temp->SetRadius(radius);
			temp->SetRotY(rotY);
			temp->Setup(name, blue, scale);

			temp->getCirclePointer()->fRadius = radius;
			temp->getCirclePointer()->mPosition = position;

			m_vecObject.push_back(temp);
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
			m_stMinionLine.vecCircle.push_back(temp);
		}
		else if (szTemp[0] == 'L')
		{
			int sour, dest;
			float x, y, z;
			sscanf_s(szTemp, "%*s %d %d %f %f %f", &sour, &dest, &x, &y, &z);
			STLINE* temp = new STLINE;
			temp->pCircles[0] = m_stMinionLine.vecCircle[sour];
			temp->pCircles[1] = m_stMinionLine.vecCircle[dest];
			temp->vCrossVector = D3DXVECTOR3(x, y, z);
			temp->pCircles[0]->vecLines.push_back(temp);
			temp->pCircles[1]->vecLines.push_back(temp);
			m_stMinionLine.vecLine.push_back(temp);
		}
	}

	fclose(fp);
	m_vecMinionLineIndex[0].push_back(0);
	m_vecMinionLineIndex[1].push_back(1);
	m_vecMinionLineIndex[2].push_back(2);
	bool tempCount[3] = { true, true, true };
	int tempCountount = 0;
	std::map<int, int> tempmap;
	tempmap.insert(std::make_pair(0, 0));
	tempmap.insert(std::make_pair(1, 1));
	tempmap.insert(std::make_pair(2, 2));
	while (tempCount[0] || tempCount[1] || tempCount[2])
	{
		for (int i = 0; i < 3; i++)
		{
			int tempIndex = m_vecMinionLineIndex[i].back();
			for (int j = 0; j < m_stMinionLine.vecCircle[tempIndex]->vecLines.size(); j++)
			{
				if (m_stMinionLine.vecCircle[tempIndex]->vecLines.size() == 1 && tempCountount != 0)
				{
					tempCount[i] = false;
					break;
				}
				for (int k = 0; k < 2; ++k)
				{
					if (m_stMinionLine.vecCircle[tempIndex]->vecLines[j]->pCircles[k]->iIndex == m_stMinionLine.vecCircle[tempIndex]->iIndex)continue;
					if (tempmap.find(m_stMinionLine.vecCircle[tempIndex]->vecLines[j]->pCircles[k]->iIndex) != tempmap.end())continue;
					m_vecMinionLineIndex[i].push_back(m_stMinionLine.vecCircle[tempIndex]->vecLines[j]->pCircles[k]->iIndex);
					tempmap.insert(std::make_pair(m_stMinionLine.vecCircle[tempIndex]->vecLines[j]->pCircles[k]->iIndex, m_stMinionLine.vecCircle[tempIndex]->vecLines[j]->pCircles[k]->iIndex));
				}
			}
		}
		tempCountount++;
	}
	MinionTimeCount = 0.0f;

	for (int i = 0; i < 2; ++i)
	{
		cEnemy* tempEnemy = new cEnemy;
		tempEnemy->SetRadius(10.0f);
		*tempEnemy->getPositionPointer() = m_stMinionLine.vecCircle[m_vecMinionLineIndex[1].front()]->mPosition;
		tempEnemy->setEnemy(&m_vecAllEnemy);
		if (!i)
		{
			*tempEnemy->getPositionPointer() = m_stMinionLine.vecCircle[m_vecMinionLineIndex[1].back()]->mPosition;
			tempEnemy->setEnemy(&m_vecAllBlue);
		}
		tempEnemy->setGoLine(m_vecMinionLineIndex[1]);
		tempEnemy->setCircleLine(m_stMinionLine);
		tempEnemy->Setup("Order_Minion_Melee_", i);

		m_vecMinion.push_back(tempEnemy);
	}
	MinionTimeCount = 0.0f;
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
	m_vecAllBlue.clear();
	m_vecALLObjectCircle.clear();
	for (int i = 0; i < m_vecObject.size(); ++i)
	{
		if (((cObject*)m_vecObject[i])->getBlue())
		{
			m_vecAllBlue.push_back(m_vecObject[i]);
		}
		else
		{
			m_vecAllEnemy.push_back(m_vecObject[i]);
		}
	}
	for (int i = 0; i < m_vecMinion.size(); ++i)
	{
		if (!((cEnemy*)m_vecMinion[i])->getLive())
		{
			SAFE_DELETE(m_vecMinion[i]);
			m_vecMinion.erase(m_vecMinion.begin() + i);
			i = 0;
		}
		if (((cEnemy*)m_vecMinion[i])->GetBlue())
		{
			m_vecAllBlue.push_back(m_vecMinion[i]);
		}
		else
		{
			m_vecAllEnemy.push_back(m_vecMinion[i]);
		}
	}

	m_vecAllBlue.push_back(m_pPlayer);
	for (int i = 0; i < m_vecObject.size(); ++i)
	{
		m_vecObject[i]->Update();
		m_vecALLObjectCircle.push_back(((cObject*)m_vecObject[i])->getCirclePointer());
	}

	MinionTimeCount += g_pTimeManager->GetElapsedTime();

	if (MinionTimeCount > 10)// && m_vecMinion.size() < 2)
	{
		for (int i = 0; i < 2; ++i)
		{
			cEnemy* tempEnemy = new cEnemy;
			tempEnemy->SetRadius(10.0f);
			*tempEnemy->getPositionPointer() = m_stMinionLine.vecCircle[m_vecMinionLineIndex[1].front()]->mPosition;
			tempEnemy->setEnemy(&m_vecAllEnemy);
			if (!i)
			{
				*tempEnemy->getPositionPointer() = m_stMinionLine.vecCircle[m_vecMinionLineIndex[1].back()]->mPosition;
				tempEnemy->setEnemy(&m_vecAllBlue);
			}
			tempEnemy->setGoLine(m_vecMinionLineIndex[1]);
			tempEnemy->setCircleLine(m_stMinionLine);
			tempEnemy->Setup("Order_Minion_Melee_", i);

			m_vecMinion.push_back(tempEnemy);
		}
		MinionTimeCount = 0.0f;
	}

	for (int i = 0; i < m_vecMinion.size(); ++i)
	{
		((cEnemy*)m_vecMinion[i])->Update();
		m_vecALLObjectCircle.push_back(((cEnemy*)m_vecMinion[i])->getCirclePointer());
	}


	g_pCollisionManager->SetvecObject(m_vecALLObjectCircle);
}

void cObjectManager::Render()
{
	for (int i = 0; i < m_vecObject.size(); ++i)
	{
		m_vecObject[i]->Render();
	}
	for (int i = 0; i < m_vecMinion.size(); ++i)
	{
		((cEnemy*)m_vecMinion[i])->Render();
	}
}

bool cObjectManager::getNexusLiving(bool Blue)
{
	cCharacter* tempNexus;
	std::string tempName;

	for (int i = 0; i < m_vecObject.size(); ++i)
	{
		tempName = ((cObject*)m_vecObject[i])->getName();
		if (tempName.c_str()[5] == 'N')
		{
			if (((cObject*)m_vecObject[i])->GetBlue() == Blue)
			{
				tempNexus = m_vecObject[i];
			}
		}
	}
	if (tempNexus->GetHP() > 0)return true;

	return false;
}
