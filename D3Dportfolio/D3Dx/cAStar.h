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
	
	//�¾����� ���̽�Ÿ ����
	void Setup(D3DXVECTOR3 position, float radius, D3DXVECTOR3 destination);
	//��� ������Ʈ ������ ĳ���� ������, RotY ����
	void Update(D3DXVECTOR3& position, float& rotY, float speed, float radius, D3DXVECTOR3* pEnemyPos = NULL);

	int getAStarSize() { return FinalAStar.size(); }

	bool Stop(D3DXVECTOR3 position, float Range, D3DXVECTOR3* EnemyPosition, float EnemyRadius);
	void Stop() { FinalAStar.clear(); }
	//�浹�ʰ� �浹�Ǹ� �������� ������ �̵����Ѽ� ����
	D3DXVECTOR3 PushDestination(D3DXVECTOR3 destination, float characterradius);

	//�̵���ο� ��ġ�� ���� �� ���� ����� �� ã��
	STLINE* FindFirstLine(D3DXVECTOR3 position, D3DXVECTOR3 destination);
	//���� �� �� ã��
	STCIRCLE FindEndCircle(D3DXVECTOR3 position, STCIRCLE nowcircle, STLINE* nowline);
	//�ٸ� ��ġ ã��(�� �������� ����)
	D3DXVECTOR3 FindNextPosition(D3DXVECTOR3 position, STCIRCLE nowcircle, float radius, bool lr);


	AStarFath* findAStar(D3DXVECTOR3 position, D3DXVECTOR3 destination, float radius, AStarFath* parent, int ChildNum);
	D3DXVECTOR3 getPositionOutCircle(D3DXVECTOR3 position, D3DXVECTOR3 destination, float radius, STCIRCLE* circle);
};

