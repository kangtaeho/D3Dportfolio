#pragma once
#define	CYLINDERHEIGHT 300.0f
#define g_pCollisionManager cCollisionManager::GetInstance()

struct STLINE;
struct STCIRCLE
{
	D3DXVECTOR3				mPosition;
	float					fRadius;
	std::vector<STLINE*>	vecLines;
	int						iIndex;
};

struct STLINE
{
	STCIRCLE*				pCircles[2];
	D3DXVECTOR3				vCrossVector;
};

struct STCollisionMapTool
{
	std::vector<STCIRCLE*>			vecCircle;
	std::vector<STLINE*>			vecLine;
};

class cCollisionManager
{
	SINGLETONE(cCollisionManager)
private:
	LPD3DXMESH						m_pMapMesh;
	LPD3DXMESH						m_pCylinder;

	STCollisionMapTool				m_stMap;

public:
	void Setup();
	void Release();

	//높이맵 매쉬 불러오기
	LPD3DXMESH getGround() { return m_pMapMesh; }
	//충돌용맵 불러오기
	STCollisionMapTool getCollisionMapTool() { return m_stMap; }
	
	//충돌용맵 파일에서 불러오기
	void LoadMap();
	
	//실린더 와이어 그리기
	void CylinderRender(D3DXVECTOR3 position, float radius);
	//바닥맵 그리기
	void MapRender();

	//포지션 넣으면 높이를 넣어 포지션을 리턴
	D3DXVECTOR3 SetHeight(D3DXVECTOR3 position);
	//isIntersect에 int를 넣으면 (아마)맞으면 1, 안맞으면 0을 줍니다.
	//매쉬에 부딫힐 매쉬를 넣으면 그것과 충돌처리, 아니면 맵과 충돌처리
	D3DXVECTOR3 getRayPosition(int isIntersect, LPD3DXMESH Mesh = NULL);

	//이 밑에 건 설명하기 힘드네요... 계속 수정될수도 있는 A*용 함수들입니다.
	D3DXVECTOR3 NextPositionPerTick(D3DXVECTOR3 position, D3DXVECTOR3 nextposition, float speed);

	float getDirectionWithCircle(D3DXVECTOR3 position, D3DXVECTOR3 nextposition, D3DXVECTOR3 circleposition);

	bool NextTickInCircle(D3DXVECTOR3 tickposition, float radius, D3DXVECTOR3 circleposition, float circleradius);
	
	D3DXVECTOR3 MoveInCircle(D3DXVECTOR3 position, D3DXVECTOR3 tickposition, float radius, float speed, D3DXVECTOR3 circleposition, float circleradius);
	
	bool CollisionUnit(D3DXVECTOR3 tickposition, float radius, D3DXVECTOR3 unitposition, float unitradius);

	bool WherePositionLR(D3DXVECTOR3 position, D3DXVECTOR3 vecterStart, D3DXVECTOR3 vecterEnd);
	bool WherePositionInVector(D3DXVECTOR3 position, D3DXVECTOR3 vecterStart, D3DXVECTOR3 vecterEnd);
	D3DXVECTOR3 WherePositionposition(D3DXVECTOR3 position, D3DXVECTOR3 vecterStart, D3DXVECTOR3 vecterEnd);//망한거
	bool IsCrossingVector(D3DXVECTOR3 position1_1, D3DXVECTOR3 position1_2, D3DXVECTOR3 position2_1, D3DXVECTOR3 position2_2);
	D3DXVECTOR3 CrossingVectorPosition(D3DXVECTOR3 position1_1, D3DXVECTOR3 position1_2, D3DXVECTOR3 position2_1, D3DXVECTOR3 position2_2);
	float CrossingVectorLength(D3DXVECTOR3 position1_1, D3DXVECTOR3 position1_2, D3DXVECTOR3 position2_1, D3DXVECTOR3 position2_2);

	D3DXVECTOR3 getVector2(D3DXVECTOR3 v) { return D3DXVECTOR3(v.x, 0, v.z); }
	float getDirectionAngle(D3DXVECTOR3 v);
	float getAngleWithVecters(D3DXVECTOR3 first, D3DXVECTOR3 mid, D3DXVECTOR3 end);

};

