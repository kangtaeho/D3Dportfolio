#include "stdafx.h"
#include "cAStar.h"


cAStar::cAStar()
{
}


cAStar::~cAStar()
{
}

bool cAStar::Update(D3DXVECTOR3& position, D3DXVECTOR3 NextPosition, float & rotY, float speed, float radius, float fRange, D3DXVECTOR3 * pEnemyPos, float fEnemyradius)
{
	if (pEnemyPos)
	{
		NextPosition = position;
		D3DXVECTOR3 tempnextposition = position - *pEnemyPos;
		if (D3DXVec3Length(&(tempnextposition)) > fRange)
		{
			D3DXVec3Normalize(&tempnextposition, &tempnextposition);
			tempnextposition *= (fRange - 10);
			NextPosition = *pEnemyPos + tempnextposition;
		}
	}
	position = g_pCollisionManager->getVector2(position);
	D3DXVECTOR3 tempend = g_pCollisionManager->getVector2(NextPosition);
	m_vNextPosition = g_pCollisionManager->getVector2(m_vNextPosition);
	if (position == tempend)
	{
		position = g_pCollisionManager->SetHeight(position);
		return false;
	}
	if (m_vFinalDestination != NextPosition)
	{
		m_vFinalDestination = NextPosition;
		tempend = FindNextPosition(position, m_vFinalDestination, radius);
		m_vNextPosition = tempend;
	}
	if (D3DXVec3Length(&(m_vNextPosition - position)) < 1.0f)
	{
		tempend = FindNextPosition(position, m_vFinalDestination, radius);
		m_vNextPosition = tempend;
	}

	position.y = 5000.0f;
	m_vNextPosition = PushDestination(m_vNextPosition, radius);
	D3DXVECTOR3 tempNextPosition = m_vNextPosition;
	tempNextPosition = tempNextPosition - position;
	D3DXVec3Normalize(&tempNextPosition, &tempNextPosition);
	tempNextPosition *= speed;
	if (pEnemyPos)
	{
		if (D3DXVec3Length(&(*pEnemyPos - position)) < speed)
		{
			tempNextPosition = *pEnemyPos - position;
		}
	}
	if (D3DXVec3Length(&(m_vNextPosition - position)) < speed)
	{
		tempNextPosition = m_vNextPosition - position;
	}
	tempNextPosition += position;

	STCollisionMapTool temptemptemp = g_pCollisionManager->getCollisionMapTool();
	for (int i = 0; i < g_pCollisionManager->getCollisionMapTool().vecCircle.size(); ++i)
	{
		if (g_pCollisionManager->NextTickInCircle(
			tempNextPosition,
			radius,
			g_pCollisionManager->getCollisionMapTool().vecCircle[i]->mPosition,
			g_pCollisionManager->getCollisionMapTool().vecCircle[i]->fRadius))
		{
			tempNextPosition = g_pCollisionManager->MoveInCircle(
				position,
				tempNextPosition,
				radius,
				speed,
				g_pCollisionManager->getCollisionMapTool().vecCircle[i]->mPosition,
				g_pCollisionManager->getCollisionMapTool().vecCircle[i]->fRadius);
			tempNextPosition.y = 0;
		}
	}
	std::vector<STCIRCLE*> tempObjectCircle = g_pCollisionManager->GetvecObject();
	for (int i = 0; i < g_pCollisionManager->GetvecObject().size(); ++i)
	{
		if (g_pCollisionManager->NextTickInCircle(
			tempNextPosition,
			radius,
			g_pCollisionManager->GetvecObject()[i]->mPosition,
			g_pCollisionManager->GetvecObject()[i]->fRadius))
		{
			tempNextPosition = g_pCollisionManager->MoveInCircle(
				position,
				tempNextPosition,
				radius,
				speed,
				g_pCollisionManager->GetvecObject()[i]->mPosition,
				g_pCollisionManager->GetvecObject()[i]->fRadius);
			tempNextPosition.y = 0;
		}
	}

	tempNextPosition = g_pCollisionManager->SetHeight(tempNextPosition);

	rotY = g_pCollisionManager->getDirectionAngle(tempNextPosition - position);
	rotY += D3DX_PI / 2;
	position = tempNextPosition;
	position = PushDestination(position, radius);
	position = g_pCollisionManager->SetHeight(position);
	return true;
}

bool cAStar::UpdateForEnemy(D3DXVECTOR3 & position, D3DXVECTOR3 NextPosition, float & rotY, float speed, float radius, float fRange, D3DXVECTOR3 * pEnemyPos, float fEnemyradius)
{
	if (pEnemyPos)
	{
		NextPosition = position;
		D3DXVECTOR3 tempnextposition = position - *pEnemyPos;
		if (D3DXVec3Length(&(tempnextposition)) > fRange)
		{
			D3DXVec3Normalize(&tempnextposition, &tempnextposition);
			tempnextposition *= fRange;
			NextPosition = *pEnemyPos + tempnextposition;
		}
	}
	position = g_pCollisionManager->getVector2(position);
	D3DXVECTOR3 tempend = g_pCollisionManager->getVector2(NextPosition);
	m_vNextPosition = g_pCollisionManager->getVector2(m_vNextPosition);
	if (position == tempend)
	{
		position = g_pCollisionManager->SetHeight(position);
		return false;
	}
	if (m_vFinalDestination != NextPosition)
	{
		m_vFinalDestination = NextPosition;
		tempend = FindNextPosition(position, m_vFinalDestination, radius);
		m_vNextPosition = tempend;
	}
	if (D3DXVec3Length(&(m_vNextPosition - position)) < 1.0f)
	{
		tempend = FindNextPosition(position, m_vFinalDestination, radius);
		m_vNextPosition = tempend;
	}

	position.y = 5000.0f;
	m_vNextPosition = PushDestination(m_vNextPosition, radius);
	D3DXVECTOR3 tempNextPosition = m_vNextPosition;
	tempNextPosition = tempNextPosition - position;
	D3DXVec3Normalize(&tempNextPosition, &tempNextPosition);
	tempNextPosition *= speed;
	if (pEnemyPos)
	{
		if (D3DXVec3Length(&(*pEnemyPos - position)) < speed)
		{
			tempNextPosition = *pEnemyPos - position;
		}
	}
	if (D3DXVec3Length(&(m_vNextPosition - position)) < speed)
	{
		tempNextPosition = m_vNextPosition - position;
	}
	tempNextPosition += position;

	std::vector<STCIRCLE*> tempObjectCircle = g_pCollisionManager->GetvecObject();
	for (int i = 0; i < tempObjectCircle.size(); ++i)
	{
		D3DXVECTOR3 tempobjectposition = tempObjectCircle[i]->mPosition;
		tempobjectposition.y = 5000.0f;
		if (position == tempobjectposition)continue;
		if (g_pCollisionManager->NextTickInCircle(
			tempNextPosition,
			radius,
			tempObjectCircle[i]->mPosition,
			tempObjectCircle[i]->fRadius))
		{
			tempNextPosition = g_pCollisionManager->MoveInCircle(
				position,
				tempNextPosition,
				radius,
				speed,
				tempObjectCircle[i]->mPosition,
				tempObjectCircle[i]->fRadius);
			tempNextPosition.y = 0;
		}
	}

	tempNextPosition = g_pCollisionManager->SetHeight(tempNextPosition);

	rotY = g_pCollisionManager->getDirectionAngle(tempNextPosition - position);
	rotY += D3DX_PI / 2;
	position = tempNextPosition;
	position = g_pCollisionManager->SetHeight(position);
	return true;
}

D3DXVECTOR3 cAStar::FindNextPosition(D3DXVECTOR3 position, D3DXVECTOR3 NextPosition, float radius)
{
	D3DXVECTOR3 tempend = g_pCollisionManager->getVector2(NextPosition);
	tempend.y = 5000.0f;
	position.y = 5000.0f;

	STCollisionMapTool tempmaptool = g_pCollisionManager->getCollisionMapTool();

	STLINE* tempLine = FindFirstLine(position, tempend);

	if (tempLine)
	{
		STCIRCLE tempcircle[2];
		D3DXVECTOR3 tempcircleposition[2];
		for (int i = 0; i < 2; ++i)
		{
			tempcircle[i] = FindEndCircle(position, *tempLine->pCircles[i], tempLine);
			tempcircleposition[i] = FindEndPositionWithCircle(position, tempend, tempcircle[i], tempLine, radius);
		}
		float tempZ1 = D3DXVec3Length(&(tempcircle[0].mPosition - tempend)) + D3DXVec3Length(&(tempcircle[0].mPosition - position));
		float tempZ2 = D3DXVec3Length(&(tempcircle[1].mPosition - tempend)) + D3DXVec3Length(&(tempcircle[1].mPosition - position));
		//float tempZ1 = abs(g_pCollisionManager->WherePositionposition(tempcircleposition[0], position, tempend).z);
		//float tempZ2 = abs(g_pCollisionManager->WherePositionposition(tempcircleposition[1], position, tempend).z);
		if (tempZ1 > tempZ2)
		{
			tempend = tempcircleposition[1];
			bool lr = !g_pCollisionManager->WherePositionLR(tempcircle[0].mPosition, position, tempend);
			return FindNextPosition(position, tempend, tempcircle[1], radius, lr);
		}
		else
		{
			tempend = tempcircleposition[0];
			bool lr = !g_pCollisionManager->WherePositionLR(tempcircle[1].mPosition, position, tempend);
			return FindNextPosition(position, tempend, tempcircle[0], radius, lr);
		}
	}
	else tempend = NextPosition;
	tempend.y = 5000.0f;

	STCIRCLE* tempCircle = NULL;
	for (int i = 0; i < tempmaptool.vecCircle.size(); ++i)
	{
		if (abs(g_pCollisionManager->WherePositionposition(tempmaptool.vecCircle[i]->mPosition, position, tempend).z) < radius + tempmaptool.vecCircle[i]->fRadius)
		{
			if (tempCircle)
			{
				if (D3DXVec3Length(&(tempCircle->mPosition - position)) > D3DXVec3Length(&(tempmaptool.vecCircle[i]->mPosition - position)))
				{
					tempCircle = tempmaptool.vecCircle[i];
				}
			}
			else
			{
				tempCircle = tempmaptool.vecCircle[i];
			}
		}
	}
	if (tempCircle)
	{
		if (abs(g_pCollisionManager->WherePositionposition(tempCircle->mPosition, position, tempend).z) < tempCircle->fRadius + radius &&
			g_pCollisionManager->WherePositionposition(position, tempCircle->mPosition, tempend).x < 0)
		{
			bool lr = !g_pCollisionManager->WherePositionLR(tempCircle->mPosition, position, tempend);
			return FindNextPosition(position, tempend, *tempCircle, radius, lr);
		}
	}


	return tempend;
}

D3DXVECTOR3 cAStar::PushDestination(D3DXVECTOR3 destination, float characterradius)
{
	STCollisionMapTool MapTool = g_pCollisionManager->getCollisionMapTool();

	characterradius += 1;

	destination = g_pCollisionManager->getVector2(destination);
	destination.y = 5000.0f;
	for (int i = 0; i < MapTool.vecLine.size(); ++i)
	{
		if (g_pCollisionManager->WherePositionLR(destination,
			MapTool.vecLine[i]->pCircles[0]->mPosition + MapTool.vecLine[i]->vCrossVector * MapTool.vecLine[i]->pCircles[0]->fRadius,
			MapTool.vecLine[i]->pCircles[1]->mPosition + MapTool.vecLine[i]->vCrossVector * MapTool.vecLine[i]->pCircles[1]->fRadius) &&
			!g_pCollisionManager->WherePositionLR(destination,
				MapTool.vecLine[i]->pCircles[0]->mPosition - MapTool.vecLine[i]->vCrossVector * MapTool.vecLine[i]->pCircles[0]->fRadius,
				MapTool.vecLine[i]->pCircles[1]->mPosition - MapTool.vecLine[i]->vCrossVector * MapTool.vecLine[i]->pCircles[1]->fRadius) &&
			g_pCollisionManager->WherePositionInVector(destination,
				MapTool.vecLine[i]->pCircles[0]->mPosition,
				MapTool.vecLine[i]->pCircles[1]->mPosition))
		{
			float wherex = g_pCollisionManager->WherePositionposition(destination,
				MapTool.vecLine[i]->pCircles[0]->mPosition,
				MapTool.vecLine[i]->pCircles[1]->mPosition).x;
			if (g_pCollisionManager->WherePositionLR(destination,
				MapTool.vecLine[i]->pCircles[0]->mPosition,
				MapTool.vecLine[i]->pCircles[1]->mPosition))
			{
				D3DXVECTOR3 goLine = (MapTool.vecLine[i]->pCircles[1]->mPosition - MapTool.vecLine[i]->vCrossVector * MapTool.vecLine[i]->pCircles[1]->fRadius) - (MapTool.vecLine[i]->pCircles[0]->mPosition - MapTool.vecLine[i]->vCrossVector * MapTool.vecLine[i]->pCircles[0]->fRadius);
				D3DXVec3Normalize(&goLine, &goLine);
				D3DXVECTOR3 crossvecLine;
				D3DXVec3Cross(&crossvecLine, &goLine, &D3DXVECTOR3(0, 1, 0));
				D3DXVec3Normalize(&crossvecLine, &crossvecLine);
				destination = (MapTool.vecLine[i]->pCircles[0]->mPosition - MapTool.vecLine[i]->vCrossVector * MapTool.vecLine[i]->pCircles[0]->fRadius) +
					goLine * wherex + crossvecLine * characterradius;
			}
			else
			{
				D3DXVECTOR3 goLine = (MapTool.vecLine[i]->pCircles[1]->mPosition + MapTool.vecLine[i]->vCrossVector * MapTool.vecLine[i]->pCircles[1]->fRadius) - (MapTool.vecLine[i]->pCircles[0]->mPosition + MapTool.vecLine[i]->vCrossVector * MapTool.vecLine[i]->pCircles[0]->fRadius);
				D3DXVec3Normalize(&goLine, &goLine);
				D3DXVECTOR3 crossvecLine;
				D3DXVec3Cross(&crossvecLine, &goLine, &D3DXVECTOR3(0, -1, 0));
				D3DXVec3Normalize(&crossvecLine, &crossvecLine);
				destination = (MapTool.vecLine[i]->pCircles[0]->mPosition + MapTool.vecLine[i]->vCrossVector * MapTool.vecLine[i]->pCircles[0]->fRadius) +
					goLine * wherex + crossvecLine * characterradius;
			}
		}
	}

	for (int i = 0; i < MapTool.vecCircle.size(); ++i)
	{
		if (g_pCollisionManager->NextTickInCircle(destination, characterradius, MapTool.vecCircle[i]->mPosition, MapTool.vecCircle[i]->fRadius))
		{
			D3DXVECTOR3 tempPosition;
			D3DXVec3Normalize(&tempPosition, &(destination - MapTool.vecCircle[i]->mPosition));
			destination = MapTool.vecCircle[i]->mPosition + tempPosition * (MapTool.vecCircle[i]->fRadius + characterradius);
		}
	}

	return destination;
}

STLINE * cAStar::FindFirstLine(D3DXVECTOR3 position, D3DXVECTOR3 destination)
{
	position.y = 5000.0f;
	destination.y = 5000.0f;
	STCollisionMapTool MapTool = g_pCollisionManager->getCollisionMapTool();
	STLINE* temp = NULL;
	float tempLength = 100000.0f;
	for (int i = 0; i < MapTool.vecLine.size(); ++i)
	{
		if (g_pCollisionManager->IsCrossingVector(position, 
			destination,
			MapTool.vecLine[i]->pCircles[0]->mPosition, 
			MapTool.vecLine[i]->pCircles[1]->mPosition))
		{
			if (tempLength > g_pCollisionManager->CrossingVectorLength(
				MapTool.vecLine[i]->pCircles[0]->mPosition,
				MapTool.vecLine[i]->pCircles[1]->mPosition,
				position,
				destination))
			{
				tempLength = g_pCollisionManager->CrossingVectorLength(
					MapTool.vecLine[i]->pCircles[0]->mPosition,
					MapTool.vecLine[i]->pCircles[1]->mPosition,
					position,
					destination);
				temp = MapTool.vecLine[i];
			}
		}
	}

	return temp;
}

STCIRCLE cAStar::FindEndCircle(D3DXVECTOR3 position, STCIRCLE nowcircle, STLINE* nowline)
{
	STCIRCLE	tempcircle = nowcircle;
	STLINE*		templine = nowline;

	while (tempcircle.vecLines.size())
	{
		std::vector<STLINE*> tempvecline;
		for (int i = 0; i < tempcircle.vecLines.size(); ++i)
		{
			if (templine == tempcircle.vecLines[i])continue;
			tempvecline.push_back(tempcircle.vecLines[i]);
		}
		tempcircle.vecLines = tempvecline;

		STCIRCLE tempnowcircle = tempcircle;
		STLINE* tempnowline = templine;
		for (int i = 0; i < tempcircle.vecLines.size(); ++i)
		{
			for (int i1 = 0; i1 < 2; ++i1)
			{
				if (templine->pCircles[i1]->mPosition == tempcircle.mPosition)continue;

				for (int i2 = 0; i2 < 2; i2++)
				{
					if (tempcircle.vecLines[i]->pCircles[i2]->mPosition == tempcircle.mPosition)continue;
					bool temp1 = g_pCollisionManager->WherePositionLR(tempcircle.vecLines[i]->pCircles[i2]->mPosition, position, tempcircle.mPosition);
					bool temp2 = g_pCollisionManager->WherePositionLR(templine->pCircles[i1]->mPosition, position, tempcircle.mPosition);
					bool temp3 = g_pCollisionManager->WherePositionLR(tempcircle.vecLines[i]->pCircles[i2]->mPosition, position, tempnowcircle.mPosition);
					
					if ((g_pCollisionManager->WherePositionLR(tempcircle.vecLines[i]->pCircles[i2]->mPosition, position, tempcircle.mPosition) !=
						g_pCollisionManager->WherePositionLR(templine->pCircles[i1]->mPosition, position, tempcircle.mPosition)) &&
						(g_pCollisionManager->WherePositionLR(tempcircle.vecLines[i]->pCircles[i2]->mPosition, position, tempnowcircle.mPosition) !=
						g_pCollisionManager->WherePositionLR(templine->pCircles[i1]->mPosition, position, tempcircle.mPosition)))
					{
						tempnowcircle = *tempcircle.vecLines[i]->pCircles[i2];
						tempnowline = tempcircle.vecLines[i];
					}

				}
			}
		}
		if (tempcircle.mPosition == tempnowcircle.mPosition)break;
		tempcircle = tempnowcircle;
		templine = tempnowline;
	}
	tempcircle.vecLines.push_back(templine);
	return tempcircle;
}

D3DXVECTOR3 cAStar::FindNextPosition(D3DXVECTOR3 position, D3DXVECTOR3 destination, STCIRCLE nowcircle, float radius, bool lr)
{
	float angle = acosf((radius + nowcircle.fRadius) / D3DXVec3Length(&(nowcircle.mPosition - position))) * (2 * lr - 1);
	D3DXVECTOR3 temp = position - nowcircle.mPosition;
	D3DXVec3Normalize(&temp, &temp);
	temp *= radius + nowcircle.fRadius;
	D3DXMATRIX mat;
	D3DXMatrixRotationY(&mat, angle);
	D3DXVec3TransformCoord(&temp, &temp, &mat);
	temp += nowcircle.mPosition;
	return PushDestination(temp, radius);
}

D3DXVECTOR3 cAStar::FindEndPositionWithCircle(D3DXVECTOR3 position, D3DXVECTOR3 destination, STCIRCLE& nowcircle, STLINE * nowline, float radius)
{
	STCIRCLE	tempcircle = nowcircle;
	STLINE*		templine = nowline;
	bool lr = g_pCollisionManager->WherePositionLR(nowcircle.mPosition, position, destination);

	D3DXVECTOR3 Nextposition = FindNextPosition(position, destination, tempcircle, radius, lr);
	
	while (tempcircle.vecLines.size())
	{
		std::vector<STLINE*> tempvecline;
		for (int i = 0; i < tempcircle.vecLines.size(); ++i)
		{
			if (templine == tempcircle.vecLines[i])continue;
			tempvecline.push_back(tempcircle.vecLines[i]);
		}
		tempcircle.vecLines = tempvecline;

		STCIRCLE tempnowcircle = tempcircle;
		STLINE* tempnowline = templine;
		for (int i = 0; i < tempcircle.vecLines.size(); ++i)
		{
			for (int i1 = 0; i1 < 2; ++i1)
			{
				if (templine->pCircles[i1]->mPosition == tempcircle.mPosition)continue;

				for (int i2 = 0; i2 < 2; i2++)
				{
					if (tempcircle.vecLines[i]->pCircles[i2]->mPosition == tempcircle.mPosition)continue;
					bool temp1 = g_pCollisionManager->WherePositionLR(tempcircle.vecLines[i]->pCircles[i2]->mPosition, position, tempcircle.mPosition);
					bool temp2 = g_pCollisionManager->WherePositionLR(templine->pCircles[i1]->mPosition, position, tempcircle.mPosition);
					bool temp3 = g_pCollisionManager->WherePositionLR(tempcircle.vecLines[i]->pCircles[i2]->mPosition, position, tempnowcircle.mPosition);

					if ((g_pCollisionManager->WherePositionLR(tempcircle.vecLines[i]->pCircles[i2]->mPosition, position, tempcircle.mPosition) !=
						g_pCollisionManager->WherePositionLR(templine->pCircles[i1]->mPosition, position, tempcircle.mPosition)) &&
						(g_pCollisionManager->WherePositionLR(tempcircle.vecLines[i]->pCircles[i2]->mPosition, position, tempnowcircle.mPosition) !=
						g_pCollisionManager->WherePositionLR(templine->pCircles[i1]->mPosition, position, tempcircle.mPosition)))
					{
						tempnowcircle = *tempcircle.vecLines[i]->pCircles[i2];
						tempnowline = tempcircle.vecLines[i];
					}

				}
			}
		}
		if (tempcircle.mPosition == tempnowcircle.mPosition)break;
		tempcircle = tempnowcircle;
		templine = tempnowline;
	}

/*
	while (tempcircle.vecLines.size())
	{
		std::vector<STLINE*> tempvecline;
		for (int i = 0; i < tempcircle.vecLines.size(); ++i)
		{
			if (templine == tempcircle.vecLines[i])continue;
			tempvecline.push_back(tempcircle.vecLines[i]);
		}
		tempcircle.vecLines = tempvecline;

		STCIRCLE tempnowcircle = tempcircle;
		STLINE* tempnowline = templine;
		for (int i = 0; i < tempcircle.vecLines.size(); ++i)
		{
			for (int i1 = 0; i1 < 2; ++i1)
			{
				if (templine->pCircles[i1]->mPosition == tempcircle.mPosition)continue;

				for (int i2 = 0; i2 < 2; i2++)
				{
					if (tempcircle.vecLines[i]->pCircles[i2]->mPosition == tempcircle.mPosition)continue;
					D3DXVECTOR3 tempposition1 = FindNextPosition(position, destination, *tempcircle.vecLines[i]->pCircles[i2], radius, lr);
					D3DXVECTOR3 tempposition2 = FindNextPosition(position, destination, tempcircle, radius, lr);
					D3DXVECTOR3 tempposition3 = FindNextPosition(position, destination, tempnowcircle, radius, lr);

					if ((g_pCollisionManager->WherePositionLR(tempposition1, position, tempposition2) == lr) &&
						(g_pCollisionManager->WherePositionLR(tempposition1, position, tempposition3) == lr))
					{
						tempnowcircle = *tempcircle.vecLines[i]->pCircles[i2];
						tempnowline = tempcircle.vecLines[i];
					}

				}
			}
		}
		if (tempcircle.mPosition == tempnowcircle.mPosition)break;
		tempcircle = tempnowcircle;
		templine = tempnowline;
	}

*/



	return FindNextPosition(position, destination, tempcircle, radius, lr);
}
