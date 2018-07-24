#pragma once

struct AStarFath
{
	D3DXVECTOR3					position;
	float						fDistance;
	STLINE*						pFirstLine;

	AStarFath*					pParent;
	//std::vector<AStarFath*>		vecChild;
	std::vector<D3DXVECTOR3>	vecChild;
	std::vector<STCIRCLE*>		vecChildCircle;
	std::vector<int>			vecChildNum;
	std::map<int, STCIRCLE*>	mapCircle;


	AStarFath():position(0, 0, 0), fDistance(0), pFirstLine(NULL), pParent(NULL){}
};

class cAStar
{
private:
	std::vector<D3DXVECTOR3>	FinalAStar;

	std::vector<AStarFath*>		AllAStarFath;
	std::vector<AStarFath*>		AllEndAStarFath;
	D3DXVECTOR3					vEndPosition;
	std::map<int, STCIRCLE*>	mapCircle;
	std::vector<D3DXVECTOR3>	tempNextPosition;

public:
	cAStar();
	~cAStar();
	
	//셋업으로 에이스타 지정
	void Setup(D3DXVECTOR3 position, float radius, D3DXVECTOR3 destination);
	//계속 업데이트 돌려서 캐릭터 포지션, RotY 지정
	void Update(D3DXVECTOR3& position, float& rotY, float speed, float radius, D3DXVECTOR3* pEnemyPos = NULL);

	int getAStarSize() { return FinalAStar.size(); }

	bool Stop(D3DXVECTOR3 position, float Range, D3DXVECTOR3* EnemyPosition, float EnemyRadius);
	void Stop() { FinalAStar.clear(); }
	//충돌맵과 충돌되면 목적지를 밖으로 이동시켜서 리턴
	D3DXVECTOR3 PushDestination(D3DXVECTOR3 destination, float characterradius);

	//이동경로에 걸치는 선들 중 가장 가까운 것 찾기
	STLINE* FindFirstLine(D3DXVECTOR3 position, D3DXVECTOR3 destination);
	//제일 먼 원 찾기
	STCIRCLE FindEndCircle(D3DXVECTOR3 position, STCIRCLE nowcircle, STLINE* nowline);
	//다름 위치 찾기(원 기준으로 접선)
	D3DXVECTOR3 FindNextPosition(D3DXVECTOR3 position, STCIRCLE nowcircle, float radius, bool lr);


	AStarFath* findAStar(D3DXVECTOR3 position, D3DXVECTOR3 destination, float radius, AStarFath* parent, int ChildNum);
	D3DXVECTOR3 getPositionOutCircle(D3DXVECTOR3 position, D3DXVECTOR3 destination, float radius, STCIRCLE* circle);
};

