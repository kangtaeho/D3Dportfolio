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

	//���̸� �Ž� �ҷ�����
	LPD3DXMESH getGround() { return m_pMapMesh; }
	//�浹��� �ҷ�����
	STCollisionMapTool getCollisionMapTool() { return m_stMap; }
	
	//�浹��� ���Ͽ��� �ҷ�����
	void LoadMap();
	
	//�Ǹ��� ���̾� �׸���
	void CylinderRender(D3DXVECTOR3 position, float radius);
	//�ٴڸ� �׸���
	void MapRender();

	//������ ������ ���̸� �־� �������� ����
	D3DXVECTOR3 SetHeight(D3DXVECTOR3 position);
	//isIntersect�� int�� ������ (�Ƹ�)������ 1, �ȸ����� 0�� �ݴϴ�.
	//�Ž��� �΋H�� �Ž��� ������ �װͰ� �浹ó��, �ƴϸ� �ʰ� �浹ó��
	D3DXVECTOR3 getRayPosition(int isIntersect, LPD3DXMESH Mesh = NULL);

	//�� �ؿ� �� �����ϱ� ����׿�... ��� �����ɼ��� �ִ� A*�� �Լ����Դϴ�.
	D3DXVECTOR3 NextPositionPerTick(D3DXVECTOR3 position, D3DXVECTOR3 nextposition, float speed);

	float getDirectionWithCircle(D3DXVECTOR3 position, D3DXVECTOR3 nextposition, D3DXVECTOR3 circleposition);

	bool NextTickInCircle(D3DXVECTOR3 tickposition, float radius, D3DXVECTOR3 circleposition, float circleradius);
	
	D3DXVECTOR3 MoveInCircle(D3DXVECTOR3 position, D3DXVECTOR3 tickposition, float radius, float speed, D3DXVECTOR3 circleposition, float circleradius);
	
	bool CollisionUnit(D3DXVECTOR3 tickposition, float radius, D3DXVECTOR3 unitposition, float unitradius);

	bool WherePositionLR(D3DXVECTOR3 position, D3DXVECTOR3 vecterStart, D3DXVECTOR3 vecterEnd);
	bool WherePositionInVector(D3DXVECTOR3 position, D3DXVECTOR3 vecterStart, D3DXVECTOR3 vecterEnd);
	D3DXVECTOR3 WherePositionposition(D3DXVECTOR3 position, D3DXVECTOR3 vecterStart, D3DXVECTOR3 vecterEnd);//���Ѱ�
	bool IsCrossingVector(D3DXVECTOR3 position1_1, D3DXVECTOR3 position1_2, D3DXVECTOR3 position2_1, D3DXVECTOR3 position2_2);
	D3DXVECTOR3 CrossingVectorPosition(D3DXVECTOR3 position1_1, D3DXVECTOR3 position1_2, D3DXVECTOR3 position2_1, D3DXVECTOR3 position2_2);
	float CrossingVectorLength(D3DXVECTOR3 position1_1, D3DXVECTOR3 position1_2, D3DXVECTOR3 position2_1, D3DXVECTOR3 position2_2);

	D3DXVECTOR3 getVector2(D3DXVECTOR3 v) { return D3DXVECTOR3(v.x, 0, v.z); }
	float getDirectionAngle(D3DXVECTOR3 v);
	float getAngleWithVecters(D3DXVECTOR3 first, D3DXVECTOR3 mid, D3DXVECTOR3 end);

};

