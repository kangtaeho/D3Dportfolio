#pragma once
class cMtlTex;

class cCollisionMap
{
private:
	std::map<std::string, cMtlTex*>	m_mapMtlTex;

public:
	cCollisionMap();
	~cCollisionMap();

	void LoadSurface(OUT std::vector<D3DXVECTOR3>& vecSurface,
		IN const char* szFolder, IN const char* szFile,
		IN D3DXMATRIX* pMat = NULL);
};

