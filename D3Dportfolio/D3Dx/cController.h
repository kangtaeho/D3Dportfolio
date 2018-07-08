#pragma once

class cCollisionMap;

class cController
{
private:
	POINT			m_ptMouse;
	D3DXVECTOR3		m_vOriginal;
	D3DXVECTOR3		m_vDirection;

	SYNTHESIZE(D3DXVECTOR3*, m_vControlPos, ControlPos); // ��Ʈ���� ��ǥ

	cCollisionMap* m_pCM;								 // �浹�� ������

public:
	cController();
	~cController();

	HRESULT Setup();
	void Release();
	void Update();
	void Render();

	void Check2DMousePointer();		// 2D ȭ����� ���콺 ������ üũ
	void Check3DMousePointer();		// 3D ȭ�鿡�� �ʰ� ���콺 ������ üũ

	void MouseAtWorldSpace();		// ���콺 3D����� ����

	void SetCMMemoryAddressLink(cCollisionMap* cm) { m_pCM = cm; }



};

