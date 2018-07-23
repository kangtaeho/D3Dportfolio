#include "stdafx.h"
#include "cAStar.h"


cAStar::cAStar()
{
}


cAStar::~cAStar()
{
}

void cAStar::Setup(D3DXVECTOR3 position, float radius, D3DXVECTOR3 destination)
{
	FinalAStar.clear();

	std::vector<std::vector<D3DXVECTOR3>> TotalAStar;
	position.y = 5000.0f;
	FinalAStar.push_back(position);
	TotalAStar.push_back(FinalAStar);
	FinalAStar.clear();

	int EndingAStar = 0;
	while (EndingAStar != TotalAStar.size())
	{
		std::vector<D3DXVECTOR3> tempvecposition = TotalAStar.front();
		if (D3DXVec3Length(&(tempvecposition.back() - destination)) > 0.001f)
		{
			STLINE* tempLine = FindFirstLine(tempvecposition.back(), destination);
			if (tempLine == NULL)
			{
				tempvecposition.push_back(PushDestination(destination, radius));
				TotalAStar.push_back(tempvecposition);
			}
			else
			{
				STCIRCLE tempcircle[2];
				for (int i = 0; i < 2; ++i)
				{
					tempcircle[i] = *tempLine->pCircles[i];
				}
				for (int i = 0; i < 2; ++i)
				{
					D3DXVECTOR3 gocircle;
					D3DXMATRIX mat, matT, matR;
					tempvecposition = TotalAStar.front();
					tempcircle[i] = FindEndCircle(tempvecposition.back(), tempcircle[i], tempLine);
					D3DXVECTOR3 tempnextposition = FindNextPosition(tempvecposition.back(), tempcircle[i], radius, g_pCollisionManager->WherePositionLR(tempcircle[i].mPosition, tempvecposition.back(), destination));
					tempnextposition = PushDestination(tempnextposition, radius);
					tempvecposition.push_back(tempnextposition);
					if (g_pCollisionManager->getAngleWithVecters(tempvecposition[tempvecposition.size() - 2], tempcircle[i].mPosition, destination) < D3DX_PI / 2)
					{
						if (g_pCollisionManager->IsCrossingVector(tempvecposition[tempvecposition.size() - 2], destination, tempcircle[i].mPosition, tempcircle[(i + 1) % 2].mPosition))
						{
							for (int j = 0; j < 2; ++j)
							{
								if (D3DXVec3Length(&(tempcircle[i].mPosition - tempcircle[i].vecLines.front()->pCircles[j]->mPosition)) < 0.001f)continue;

								D3DXVECTOR3 tempendposition = tempcircle[i].vecLines.front()->pCircles[(j + 1) % 2]->mPosition - tempcircle[i].vecLines.front()->pCircles[j]->mPosition;
								D3DXVec3Normalize(&tempendposition, &tempendposition);
								tempendposition *= radius + tempcircle[i].fRadius;
								tempendposition += tempcircle[i].mPosition;
								tempvecposition.push_back(tempendposition);
							}
						}
					}
					TotalAStar.push_back(tempvecposition);
				}
			}
		}

		if (D3DXVec3Length(&(TotalAStar.front().back() - destination)) < 0.001f)break;// TotalAStar.push_back(TotalAStar.front());
		TotalAStar.erase(TotalAStar.begin());

		EndingAStar = 0;
		for (int i = 0; i < TotalAStar.size(); ++i)
		{
			if (D3DXVec3Length(&(TotalAStar[i].back() - destination)) < 0.001f)EndingAStar++;
		}
	}
	/*
	for (int i = 0; i < TotalAStar.size(); ++i)
	{
		if (D3DXVec3Length(&(TotalAStar[i].back() - destination)) > 0.001f)continue;
		if(!FinalAStar.size())FinalAStar = TotalAStar[i];
		else
		{
			float tempAllLength1 = 0;
			float tempAllLength2 = 0;
			for (int j = 1; j < FinalAStar.size(); ++j)
			{
				tempAllLength1 += D3DXVec3Length(&(FinalAStar[j] - FinalAStar[j - 1]));
			}
			for (int j = 1; j < TotalAStar[i].size(); ++j)
			{
				tempAllLength2 += D3DXVec3Length(&(TotalAStar[i][j] - TotalAStar[i][j - 1]));
			}
			if (tempAllLength1 > tempAllLength2)FinalAStar = TotalAStar[i];
		}
	}
*/
	FinalAStar = TotalAStar.front();

	////////////////////////////////////////////////////////////////
/*
	position.y = 5000.0f;
	vEndPosition = PushDestination(destination, radius);
	findAStar(position, destination, radius, NULL, 0);

	AStarFath* finalFath = AllEndAStarFath[0];

	for (int i = 0; i < AllEndAStarFath.size(); ++i)
	{
		if (finalFath->fDistance > AllEndAStarFath[i]->fDistance)finalFath = AllEndAStarFath[i];
	}

	FinalAStar.clear();
	FinalAStar.push_back(destination);

	while (finalFath->position != position)
	{
		FinalAStar.push_back(finalFath->position);
		finalFath = finalFath->pParent;
	}

	for (auto p : AllAStarFath)
	{
		SAFE_DELETE(p);
	}
	AllAStarFath.clear();
	AllEndAStarFath.clear();
	mapCircle.clear();
*/
}

void cAStar::Update(D3DXVECTOR3& position, float& rotY, float speed, float radius)
{
	position = g_pCollisionManager->getVector2(position);
	if (FinalAStar.size())
	{
		D3DXVECTOR3 tempend = g_pCollisionManager->getVector2(FinalAStar.front());
		tempend = PushDestination(tempend, radius);
		tempend.y = 0;
		D3DXVECTOR3 tempNextPosition = tempend;
		tempNextPosition = tempNextPosition - position;
		D3DXVec3Normalize(&tempNextPosition, &tempNextPosition);
		tempNextPosition *= speed;
		if (D3DXVec3Length(&(tempend - position)) < speed)
		{
			tempNextPosition = tempend - position;
		}
		tempNextPosition += position;

		if (D3DXVec3Length(&(g_pCollisionManager->getVector2(tempend) - g_pCollisionManager->getVector2(tempNextPosition))) < 0.001f)FinalAStar.erase(FinalAStar.begin());
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

		tempNextPosition = g_pCollisionManager->SetHeight(tempNextPosition);

		rotY = g_pCollisionManager->getDirectionAngle(tempNextPosition - position);
		rotY += D3DX_PI / 2;
		position = tempNextPosition;
	}
}

D3DXVECTOR3 cAStar::PushDestination(D3DXVECTOR3 destination, float characterradius)
{
	STCollisionMapTool MapTool = g_pCollisionManager->getCollisionMapTool();

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

D3DXVECTOR3 cAStar::FindNextPosition(D3DXVECTOR3 position, STCIRCLE nowcircle, float radius, bool lr)
{
	position.y = 0.0f;
	nowcircle.mPosition.y = 0.0f;
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

AStarFath* cAStar::findAStar(D3DXVECTOR3 position, D3DXVECTOR3 destination, float radius, AStarFath* parent, int ChildNum)
{
	if (vEndPosition == position)
	{
		return NULL;
	}
	D3DXVECTOR3 nextPosition = destination;
	AStarFath* tempFath = new AStarFath;
	tempFath->position = position;
	tempFath->pParent = parent;
	tempFath->pFirstLine = FindFirstLine(position, destination);
	if (tempFath->pParent)
	{
		tempFath->fDistance = D3DXVec3Length(&(tempFath->pParent->position - tempFath->position));
	}
	if (tempFath->pFirstLine)
	{
		for (int i = 0; i < 2; ++i)
		{
			STCIRCLE tempCircle = FindEndCircle(position, *tempFath->pFirstLine->pCircles[i], tempFath->pFirstLine);
			bool LR = g_pCollisionManager->WherePositionLR(tempCircle.mPosition, position, destination);
			nextPosition = FindNextPosition(position, tempCircle, radius, LR);
			if (tempFath->pParent)
			{
				std::map<int, STCIRCLE*>::iterator tempiter = mapCircle.find(tempFath->pFirstLine->pCircles[i]->iIndex);
				if (tempFath->pParent->vecChildCircle.size() > ChildNum &&
					tempCircle.iIndex == tempFath->pParent->vecChildCircle[ChildNum]->iIndex)
				{
					nextPosition = getPositionOutCircle(position, destination, radius, tempFath->pFirstLine->pCircles[i]);
				}
				else if (tempiter != mapCircle.end())
				{
					continue;
				}
			}
			tempFath->mapCircle.insert(std::make_pair(tempCircle.iIndex, g_pCollisionManager->getCollisionMapTool().vecCircle[tempCircle.iIndex]));
			mapCircle.insert(std::make_pair(tempCircle.iIndex, g_pCollisionManager->getCollisionMapTool().vecCircle[tempCircle.iIndex]));
			if (FindFirstLine(position, nextPosition))
			{
				findAStar(position, nextPosition, radius, tempFath, ChildNum);
			}
			else
			{
				tempFath->vecChild.push_back(nextPosition);
				if (tempFath->pParent && tempFath->pParent->vecChildCircle.size() > ChildNum)
				{
					if (tempCircle.iIndex != tempFath->pParent->vecChildCircle[ChildNum]->iIndex)
					{
						tempFath->vecChildCircle.push_back(g_pCollisionManager->getCollisionMapTool().vecCircle[tempCircle.iIndex]);
						tempFath->vecChildNum.push_back(tempFath->vecChildCircle.size() - 1);
					}
				}
				else
				{
					tempFath->vecChildCircle.push_back(g_pCollisionManager->getCollisionMapTool().vecCircle[tempCircle.iIndex]);
					tempFath->vecChildNum.push_back(tempFath->vecChildCircle.size() - 1);
				}
			}
		}
	}
	else
	{
		AllEndAStarFath.push_back(tempFath);
	}
	AllAStarFath.push_back(tempFath);

	for (int i = 0; i < tempFath->vecChild.size(); ++i)
	{
		findAStar(tempFath->vecChild[i], destination, radius, tempFath, i);
	}


	return tempFath;
}

D3DXVECTOR3 cAStar::getPositionOutCircle(D3DXVECTOR3 position, D3DXVECTOR3 destination, float radius, STCIRCLE * circle)
{
	bool tempbool = g_pCollisionManager->WherePositionLR(circle->mPosition, position, destination);
	D3DXVECTOR3 vecLR;
	D3DXVec3Cross(&vecLR, &(destination - position), &D3DXVECTOR3(0, 1 - 2 * tempbool, 0));
	D3DXVec3Normalize(&vecLR, &vecLR);
	vecLR *= radius + circle->fRadius;
	vecLR += circle->mPosition;

	return vecLR;
}
