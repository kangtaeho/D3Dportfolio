#pragma once
class cAStar
{
private:
	std::vector<D3DXVECTOR3> FinalAStar;

public:
	cAStar();
	~cAStar();
	
	//셋업으로 에이스타 지정
	void Setup(D3DXVECTOR3 position, float radius, D3DXVECTOR3 destination);
	//계속 업데이트 돌려서 캐릭터 포지션, RotY 지정
	void Update(D3DXVECTOR3& position, float& rotY, float speed, float radius);

	//충돌맵과 충돌되면 목적지를 밖으로 이동시켜서 리턴
	D3DXVECTOR3 PushDestination(D3DXVECTOR3 destination, float characterradius);

	//이동경로에 걸치는 선들 중 가장 가까운 것 찾기
	STLINE* FindFirstLine(D3DXVECTOR3 position, D3DXVECTOR3 destination);
	//제일 먼 원 찾기
	STCIRCLE FindEndCircle(D3DXVECTOR3 position, STCIRCLE nowcircle, STLINE* nowline);
	//다름 위치 찾기(원 기준으로 접선)
	D3DXVECTOR3 FindNextPosition(D3DXVECTOR3 position, STCIRCLE nowcircle, float radius, bool lr);
};

//AStar 변수 만들어서 사용하시면 됩니다~
//private에 있는 FinalAStar가 중요한 백터입니다
//아직 완벽하게 움직이진 않아요.... 다만 다른것도 해야하니 시간 조절해서 일단 여기까지 하려고요....