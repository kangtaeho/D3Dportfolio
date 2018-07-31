#include "stdafx.h"
#include "cAStar.h"
#include "cCharacter.h"


cAStar::cAStar()
{
}


cAStar::~cAStar()
{
}

bool cAStar::Update(D3DXVECTOR3& position, D3DXVECTOR3 NextPosition, float & rotY, float speed, float radius, float fRange, D3DXVECTOR3 * pEnemyPos, float fEnemyradius)
{
	if (pEnemyPos)															//적의 포지션이 있으면
	{
		NextPosition = position;											//일단 임시로 현재 위치 저장
		D3DXVECTOR3 tempnextposition = position - *pEnemyPos;				//적의 위치와 현재 위치 사이의 벡터 구하기
		if (D3DXVec3Length(&(tempnextposition)) > fRange)					//사거리보다 적과의 벡터 길이가 길면
		{
			D3DXVec3Normalize(&tempnextposition, &tempnextposition);		//적과의 벡터 길이를 1로 만들어주고
			tempnextposition *= (fRange - radius);							//사거리 안까지의 길이를 적과의 벡터에 곱해주기
			NextPosition = *pEnemyPos + tempnextposition;					//사거리를 기준으로 가야할 다음 포지션 설정
		}
	}
	position = g_pCollisionManager->getVector2(position);					//포지션을 x, 0, z로 만들어주기
	D3DXVECTOR3 tempend = g_pCollisionManager->getVector2(NextPosition);	//다음 포지션을 x, 0, z로 만들어주기
	m_vNextPosition = g_pCollisionManager->getVector2(m_vNextPosition);		//저장해둔 다음 보지션을 x, 0, z로 만들어주기
	if (D3DXVec3Length(&(position - tempend)) < 0.001f)						//다음 포지션과 현재 위치 사이의 길이가 0.001f 이하면
	{
		position = g_pCollisionManager->SetHeight(position);				//현재 포지션을 높이맵에 맞춰주고 저장
		return false;														//이동 하지 않았다고 리턴
	}
	if (m_vFinalDestination != NextPosition)								//다음 포지션이 저장된 마지막 포지션과 다르면
	{
		m_vFinalDestination = NextPosition;									//저장된 마지막 포지션에 다음 포지션을 넣어주기
		tempend = FindNextPosition(position, m_vFinalDestination, radius);	//다음 포지션을 찾는다
		m_vNextPosition = tempend;											//저장된 다음 포지션에 다음 포지션을 저장한다
	}
	if (D3DXVec3Length(&(m_vNextPosition - position)) < 1.0f)				//저장된 다음 포지션과 현재 포지션의 길이가 1.0f 이하일때
	{
		tempend = FindNextPosition(position, m_vFinalDestination, radius);	//다음 포지션 찾기
		m_vNextPosition = tempend;											//저장된 다음 포지션에 다음 포지션 저장
	}

	position.y = 5000.0f;													//현재 위치의 y값을 5000에 고정
	m_vNextPosition = PushDestination(m_vNextPosition, radius);				//다음 포지션을 벽과의 충돌을 시켜 밀어내기
	D3DXVECTOR3 tempNextPosition = m_vNextPosition;							//임시 다음 포지션을 만들어 다음 포지션 저장
	tempNextPosition = tempNextPosition - position;							//임시 다음 포지션과 현재 포지션 벡터 구하기
	D3DXVec3Normalize(&tempNextPosition, &tempNextPosition);				//임시 다음 포지션을 길이 1로 만들기
	tempNextPosition *= speed;												//임시 다음 포지션에 스피드를 곱해준다
	if (pEnemyPos)															//적 포지션이 있으면
	{
		if (D3DXVec3Length(&(*pEnemyPos - position)) - radius < speed)		//적 포지션과 현재 포지션 벡터의 길이에서 자신의 반지름을 빼 속도보다 작으면
		{
			tempNextPosition = *pEnemyPos - position;						//임시 다음 포지션을 적포지션과 현재 포지션을 뺴서 구한다.
		}
	}
	if (D3DXVec3Length(&(m_vNextPosition - position)) < speed)				//저장된 다음 포지션까지의 거리가 속도보다 작으면
	{
		tempNextPosition = m_vNextPosition - position;						//임시 다음 포지션에 저장된 다음 포지션과 현재 포지션의 벡터를 저장
	}
	tempNextPosition += position;											//임시 저장 포지션에 현재 포지션을 더해서 다음 갈 포지션을 저장

	STCollisionMapTool temptemptemp = g_pCollisionManager->getCollisionMapTool();			//이동중 맵과의 충돌 처리
	for (int i = 0; i < g_pCollisionManager->getCollisionMapTool().vecCircle.size(); ++i)
	{
		if (g_pCollisionManager->NextTickInCircle(
			tempNextPosition,
			radius,
			g_pCollisionManager->getCollisionMapTool().vecCircle[i]->mPosition,
			g_pCollisionManager->getCollisionMapTool().vecCircle[i]->fRadius))				//다음 이동이 원과 충동했을 경우
		{
			tempNextPosition = g_pCollisionManager->MoveInCircle(
				position,
				tempNextPosition,
				radius,
				speed,
				g_pCollisionManager->getCollisionMapTool().vecCircle[i]->mPosition,
				g_pCollisionManager->getCollisionMapTool().vecCircle[i]->fRadius);			//다음 포지션을 밀어낸다
			tempNextPosition.y = 0;
		}
	}
	std::vector<STCIRCLE*> tempObjectCircle = g_pCollisionManager->GetvecObject();			//오브젝트(포탑, 억제기, 넥서스) 정보 가져오기
	for (int i = 0; i < g_pCollisionManager->GetvecObject().size(); ++i)					//위의 벽과의 충돌가 같음
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

	rotY = g_pCollisionManager->getDirectionAngle(tempNextPosition - position);				//각도 구해서
	rotY += D3DX_PI / 2;																	//거기에 90도를 더해준다.
	position = tempNextPosition;															//현재 포지션을 임시 다음 포지션으로 바꿔주고
	position = PushDestination(position, radius);											//벽과의 충돌 해주고
	position = g_pCollisionManager->SetHeight(position);									//높이맵에 맞춰준다.
	return true;
}

bool cAStar::UpdateForEnemy(D3DXVECTOR3 & position, D3DXVECTOR3 NextPosition, float & rotY, float speed, float radius, float fRange, D3DXVECTOR3 * pEnemyPos, cCharacter* enemy)
{
	if (pEnemyPos)
	{
		NextPosition = position;
		D3DXVECTOR3 tempnextposition = position - *pEnemyPos;
		if (D3DXVec3Length(&(tempnextposition)) > fRange + enemy->GetRadius())
		{
			D3DXVec3Normalize(&tempnextposition, &tempnextposition);
			tempnextposition *= fRange + enemy->GetRadius();
			NextPosition = *pEnemyPos + tempnextposition;
		}
	}

	std::vector<STCIRCLE*> tempObjectCircle = g_pCollisionManager->GetvecObject();
	position = g_pCollisionManager->getVector2(position);
	D3DXVECTOR3 tempend = g_pCollisionManager->getVector2(NextPosition);
	m_vNextPosition = g_pCollisionManager->getVector2(m_vNextPosition);
	if (D3DXVec3Length(&(position - tempend)) < 1.0f)
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
	D3DXVECTOR3 tempend = g_pCollisionManager->getVector2(NextPosition);			//y를 0으로 맞춰준다.
	tempend.y = 5000.0f;
	position.y = 5000.0f;

	STCollisionMapTool tempmaptool = g_pCollisionManager->getCollisionMapTool();	//벽정보 가져오기

	STLINE* tempLine = FindFirstLine(position, tempend);							//가는 길의 첫 라인을 찾는다.

	if (tempLine)																	//라인과 부딛히면(첫 라인이 있으면)
	{
		STCIRCLE tempcircle[2];														//임시로 저장할 써클 생성
		D3DXVECTOR3 tempcircleposition[2];											//임시로 저장할 포지션 생성
		for (int i = 0; i < 2; ++i)
		{
			tempcircle[i] = FindEndCircle(position, *tempLine->pCircles[i], tempLine);									//각도로 끝 써클 찾기
			tempcircleposition[i] = FindEndPositionWithCircle(position, tempend, tempcircle[i], tempLine, radius);		//써클 기준으로 위치 찾기
		}
		float tempZ1 = D3DXVec3Length(&(tempcircle[0].mPosition - tempend)) + D3DXVec3Length(&(tempcircle[0].mPosition - position));	//총길이 저장
		float tempZ2 = D3DXVec3Length(&(tempcircle[1].mPosition - tempend)) + D3DXVec3Length(&(tempcircle[1].mPosition - position));	//총길이 저장
		//float tempZ1 = abs(g_pCollisionManager->WherePositionposition(tempcircleposition[0], position, tempend).z);
		//float tempZ2 = abs(g_pCollisionManager->WherePositionposition(tempcircleposition[1], position, tempend).z);
		if (tempZ1 > tempZ2)
		{
			tempend = tempcircleposition[1];
			bool lr = !g_pCollisionManager->WherePositionLR(tempcircle[0].mPosition, position, tempend);				//왼쪽인지 오른쪽인지 저장
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

	//std::vector<STCIRCLE*> tempObjectCircle = g_pCollisionManager->GetvecObject();
	//for (int i = 0; i < tempObjectCircle.size(); ++i)
	//{
	//	if (g_pCollisionManager->NextTickInCircle(destination, characterradius, tempObjectCircle[i]->mPosition, tempObjectCircle[i]->fRadius))
	//	{
	//		D3DXVECTOR3 tempPosition;
	//		D3DXVec3Normalize(&tempPosition, &(destination - tempObjectCircle[i]->mPosition));
	//		destination = tempObjectCircle[i]->mPosition + tempPosition * (tempObjectCircle[i]->fRadius + characterradius);
	//	}
	//}

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
