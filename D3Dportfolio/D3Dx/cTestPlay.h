#pragma once

class cCube;
class cTestPlay
{
private:
	cCube* m_pCube;

	float	m_fRotY;

public:
	cTestPlay();
	~cTestPlay();

	HRESULT Setup();
	void Update();
	void Render();

};

