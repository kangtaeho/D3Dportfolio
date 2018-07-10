#pragma once

class cCollisionMap
{
private:
	std::vector<D3DXVECTOR3>	m_pVecSurface;
	std::vector<stCollisionMap>	m_pVecCollisionFace;

public:
	cCollisionMap();
	~cCollisionMap();

	std::vector<D3DXVECTOR3>* getMap() { return &m_pVecSurface; }				// ǥ���� ���ؽ����� �ּҰ�
	std::vector<stCollisionMap>* getCollisionMap() { return &m_pVecCollisionFace; }

	void Render();
};

