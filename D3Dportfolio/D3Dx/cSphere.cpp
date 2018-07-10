#include "stdafx.h"
#include "cSphere.h"


cSphere::cSphere()
	:m_fRadius(2.0f)
	,m_vPos(0,0,0)
	,m_bIsShow(true)
	
{
}


cSphere::~cSphere()
{
}

void cSphere::Setup(D3DXVECTOR3 pos, float radius)
{
	m_fRadius = radius;
	D3DXCreateSphere(
		g_pD3DDevice,
		m_fRadius,
		10,
		10,
		&m_pMesh,
		NULL
	);

	m_vPos = pos;

	LPDIRECT3DVERTEXBUFFER9	pVB;
	m_pMesh->GetVertexBuffer(&pVB);

}

void cSphere::Update()
{
	
}

void cSphere::Render()
{
	//if (!m_bIsShow) return;

	g_pD3DDevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_WIREFRAME);

	D3DXMATRIX matT;
	D3DXMatrixIdentity(&matT);
	g_pD3DDevice->SetTexture(0, NULL);
	D3DXMatrixTranslation(&matT, m_vPos.x, m_vPos.y, m_vPos.z);
	g_pD3DDevice->SetTransform(D3DTS_WORLD, &matT);
	m_pMesh->DrawSubset(0);

	g_pD3DDevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_SOLID);

}