#pragma once

class cCollisionMap;

class cController
{
private:
	POINT			m_ptMouse;
	D3DXVECTOR3		m_vOriginal;
	D3DXVECTOR3		m_vDirection;

	SYNTHESIZE(D3DXVECTOR3*, m_vControlPos, ControlPos); // 컨트롤할 좌표

	cCollisionMap* m_pCM;								 // 충돌맵 포인터

public:
	cController();
	~cController();

	HRESULT Setup();
	void Release();
	void Update();
	void Render();

	void Check2DMousePointer();		// 2D 화면상의 마우스 포인터 체크
	void Check3DMousePointer();		// 3D 화면에서 맵과 마우스 포인터 체크

	void MouseAtWorldSpace();		// 마우스 3D월드로 변경

	void SetCMMemoryAddressLink(cCollisionMap* cm) { m_pCM = cm; }



};

