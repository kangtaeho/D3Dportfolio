#pragma once
class cRayPicking
{
private:
	D3DXVECTOR3		m_vDirection;

public:
	cRayPicking();
	~cRayPicking();

	//a, b, c�� ���� 3�� �ְ�(�ﰢ��), cameraEye�� ī�޶� ���� ��ġ ���� �ְ�, clickPoint�� �ƹ��ų� �����ø� �˴ϴ�. clickPoint�� ������ ���Ϳ�.
	//���� �� �ﰢ�� ���� �ƴ϶�� false�� ���ϰ� (0, 0, 0)�� clickPoint�� �����ɴϴ�.
	bool PickTri(D3DXVECTOR3 a, D3DXVECTOR3 b, D3DXVECTOR3 c, D3DXVECTOR3 cameraEye, D3DXVECTOR3& clickPoint);
};

