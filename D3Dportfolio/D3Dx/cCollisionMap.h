#pragma once

class cCollisionMap
{
private:
	std::vector<D3DXVECTOR3>	m_pVecSurface;
	std::vector<stCollisionMap>	m_pVecCollisionFace;

public:
	cCollisionMap();
	~cCollisionMap();

	void LoadSurface(OUT std::vector<D3DXVECTOR3>& vecSurface,
		IN const char* szFolder, IN const char* szFile,
		IN D3DXMATRIX* pMat = NULL);
	void LoadCollisionSurface(OUT std::vector<stCollisionMap>& VecCollisionFace, IN const char * szFolder, IN const char * szFile, IN D3DXMATRIX* pMat);

	std::vector<D3DXVECTOR3>* getMap() { return &m_pVecSurface; }
	std::vector<stCollisionMap>* getCollisionMap() { return &m_pVecCollisionFace; }
};

