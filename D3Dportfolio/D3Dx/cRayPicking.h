#pragma once
class cRayPicking
{
private:
	D3DXVECTOR3		m_vDirection;

public:
	cRayPicking();
	~cRayPicking();

	//a, b, c에 백터 3개 넣고(삼각형), cameraEye에 카메라 현재 위치 백터 넣고, clickPoint에 아무거나 넣으시면 됩니다. clickPoint에 뽑혀져 나와요.
	//만약 그 삼각형 안이 아니라면 false값 리턴과 (0, 0, 0)을 clickPoint로 가져옵니다.
	bool PickTri(D3DXVECTOR3 a, D3DXVECTOR3 b, D3DXVECTOR3 c, D3DXVECTOR3 cameraEye, D3DXVECTOR3& clickPoint);
};

