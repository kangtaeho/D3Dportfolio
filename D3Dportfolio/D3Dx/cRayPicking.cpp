#include "stdafx.h"
#include "cRayPicking.h"


cRayPicking::cRayPicking()
{
}


cRayPicking::~cRayPicking()
{
}

bool cRayPicking::PickTri(D3DXVECTOR3 a, D3DXVECTOR3 b, D3DXVECTOR3 c, D3DXVECTOR3 cameraEye, D3DXVECTOR3& clickPoint)
{
	D3DXMATRIX invProj, invViewPort;
	D3DVIEWPORT9 tempViewPort;
	g_pD3DDevice->GetViewport(&tempViewPort);
	g_pD3DDevice->GetTransform(D3DTS_PROJECTION, &invProj);

	POINT ptMouse;
	GetCursorPos(&ptMouse);
	ScreenToClient(g_hWnd, &ptMouse);

	m_vDirection.x = ((2.0f * ptMouse.x) / tempViewPort.Width - 1.0f) / invProj._11;
	m_vDirection.y = ((-2.0f * ptMouse.y) / tempViewPort.Height + 1.0f) / invProj._22;
	m_vDirection.z = 1.0f;

	D3DXMATRIX invView;
	g_pD3DDevice->GetTransform(D3DTS_VIEW, &invView);
	D3DXMatrixInverse(&invView, 0, &invView);

	D3DXVec3TransformNormal(&m_vDirection, &m_vDirection, &invView);
	D3DXVec3Normalize(&m_vDirection, &m_vDirection);
	float u, v, tmpLength;
	bool tmpBool;
	clickPoint = D3DXVECTOR3(0, 0, 0);
	tmpBool = D3DXIntersectTri(&a, &b, &c, &cameraEye, &m_vDirection, &u, &v, &tmpLength);
	if (tmpBool)
	{
		clickPoint = a + u * (b - a) + v * (c - a);
	}
	return tmpBool;
}