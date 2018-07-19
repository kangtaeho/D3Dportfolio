#pragma once
class cAStar
{
private:
	std::vector<D3DXVECTOR3> FinalAStar;

public:
	cAStar();
	~cAStar();
	
	//�¾����� ���̽�Ÿ ����
	void Setup(D3DXVECTOR3 position, float radius, D3DXVECTOR3 destination);
	//��� ������Ʈ ������ ĳ���� ������, RotY ����
	void Update(D3DXVECTOR3& position, float& rotY, float speed, float radius);

	//�浹�ʰ� �浹�Ǹ� �������� ������ �̵����Ѽ� ����
	D3DXVECTOR3 PushDestination(D3DXVECTOR3 destination, float characterradius);

	//�̵���ο� ��ġ�� ���� �� ���� ����� �� ã��
	STLINE* FindFirstLine(D3DXVECTOR3 position, D3DXVECTOR3 destination);
	//���� �� �� ã��
	STCIRCLE FindEndCircle(D3DXVECTOR3 position, STCIRCLE nowcircle, STLINE* nowline);
	//�ٸ� ��ġ ã��(�� �������� ����)
	D3DXVECTOR3 FindNextPosition(D3DXVECTOR3 position, STCIRCLE nowcircle, float radius, bool lr);
};

//AStar ���� ���� ����Ͻø� �˴ϴ�~
//private�� �ִ� FinalAStar�� �߿��� �����Դϴ�
//���� �Ϻ��ϰ� �������� �ʾƿ�.... �ٸ� �ٸ��͵� �ؾ��ϴ� �ð� �����ؼ� �ϴ� ������� �Ϸ����....