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

	void render()
	{
		D3DXVECTOR3 tempposition(0, 0, 0);
		D3DXMATRIX WorldMatrix, matProj, matViewPort, matView;
		D3DXMatrixTranslation(&WorldMatrix, mPosition.x, mPosition.y, mPosition.z);
		D3DVIEWPORT9 tempViewPort;
		g_pD3DDevice->GetViewport(&tempViewPort);
		D3DXMatrixIdentity(&matViewPort);
		matViewPort._11 = tempViewPort.Width / (float)2;
		matViewPort._22 = -(int)tempViewPort.Height / (float)2;
		matViewPort._33 = tempViewPort.MaxZ - tempViewPort.MinZ;
		matViewPort._41 = tempViewPort.X + tempViewPort.Width / (float)2;
		matViewPort._42 = tempViewPort.Y + tempViewPort.Height / (float)2;
		matViewPort._43 = tempViewPort.MinZ;
		g_pD3DDevice->GetTransform(D3DTS_PROJECTION, &matProj);
		g_pD3DDevice->GetTransform(D3DTS_VIEW, &matView);

		WorldMatrix = WorldMatrix * matView * matProj * matViewPort;
		D3DXVec3TransformCoord(&tempposition, &tempposition, &WorldMatrix);

		g_pFontManager->TextFont(tempposition.x, tempposition.y, "radius : %f", fRadius);
		g_pFontManager->TextFont(tempposition.x, tempposition.y + 20, "position : %f, %f", mPosition.x, mPosition.z);
	}

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

	std::vector<std::string>		AllFileName;
	std::vector<int>				AllFileSize;
	std::vector<int>				LoadFileSize;

	std::vector<D3DXVECTOR3>	vecSurface;
	std::vector<D3DXVECTOR3>	vecV;


public:
	bool Setup(int& allfilesize, int& loadfilesize);
	void Release();
	void Render();

	LPD3DXMESH getGround() { return m_pMapMesh; }
	STCollisionMapTool getCollisionMapTool() { return m_stMap; }

	void LoadMap();

	void CylinderRender(D3DXVECTOR3 position, float radius);
	void MapRender();

	D3DXVECTOR3 SetHeight(D3DXVECTOR3 position);
	D3DXVECTOR3 getRayPosition(int& isIntersect, D3DXVECTOR3 position = D3DXVECTOR3(0, 0, 0), float TargetRadius = 0);

	D3DXVECTOR3 NextPositionPerTick(D3DXVECTOR3 position, D3DXVECTOR3 nextposition, float speed);

	float getDirectionWithCircle(D3DXVECTOR3 position, D3DXVECTOR3 nextposition, D3DXVECTOR3 circleposition);

	bool NextTickInCircle(D3DXVECTOR3 tickposition, float radius, D3DXVECTOR3 circleposition, float circleradius);
	
	D3DXVECTOR3 MoveInCircle(D3DXVECTOR3 position, D3DXVECTOR3 tickposition, float radius, float speed, D3DXVECTOR3 circleposition, float circleradius);
	
	bool CollisionUnit(D3DXVECTOR3 tickposition, float radius, D3DXVECTOR3 unitposition, float unitradius);

	bool WherePositionLR(D3DXVECTOR3 position, D3DXVECTOR3 vecterStart, D3DXVECTOR3 vecterEnd);
	bool WherePositionInVector(D3DXVECTOR3 position, D3DXVECTOR3 vecterStart, D3DXVECTOR3 vecterEnd);
	D3DXVECTOR3 WherePositionposition(D3DXVECTOR3 position, D3DXVECTOR3 vecterStart, D3DXVECTOR3 vecterEnd);//¸ÁÇÑ°Å
	bool IsCrossingVector(D3DXVECTOR3 position1_1, D3DXVECTOR3 position1_2, D3DXVECTOR3 position2_1, D3DXVECTOR3 position2_2);
	D3DXVECTOR3 CrossingVectorPosition(D3DXVECTOR3 position1_1, D3DXVECTOR3 position1_2, D3DXVECTOR3 position2_1, D3DXVECTOR3 position2_2);
	float CrossingVectorLength(D3DXVECTOR3 position1_1, D3DXVECTOR3 position1_2, D3DXVECTOR3 position2_1, D3DXVECTOR3 position2_2);

	D3DXVECTOR3 getVector2(D3DXVECTOR3 v) { return D3DXVECTOR3(v.x, 0, v.z); }
	float getDirectionAngle(D3DXVECTOR3 v);
	float getAngleWithVecters(D3DXVECTOR3 first, D3DXVECTOR3 mid, D3DXVECTOR3 end);

};

