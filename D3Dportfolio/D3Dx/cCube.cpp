#include "stdafx.h"
#include "cCube.h"


cCube::cCube()
	: m_vPosition(0, 0, 0)
	, m_pMesh(NULL)
{
	D3DXMatrixIdentity(&m_matWorld);
}


cCube::~cCube()
{
}

void cCube::Setup(D3DXVECTOR3 size, LPCWSTR texName)
{

	D3DXCreateTextureFromFile(g_pD3DDevice, L"tex00.jpg", &m_pTexture[0]);
	D3DXCreateTextureFromFile(g_pD3DDevice, L"tex01.jpg", &m_pTexture[1]);
	D3DXCreateTextureFromFile(g_pD3DDevice, L"tex02.jpg", &m_pTexture[2]);


	ST_PNT_VERTEX v;
	v.p = D3DXVECTOR3(-0.5f*size.x, -0.5f*size.y, -0.5f*size.z);
	v.n = D3DXVECTOR3(0, 0, 0);
	m_vecVertex.push_back(v);


	v.p = D3DXVECTOR3(-0.5f*size.x, 0.5f*size.y, -0.5f*size.z);
	v.n = D3DXVECTOR3(0, 0, 0);
	m_vecVertex.push_back(v);


	v.p = D3DXVECTOR3(0.5f*size.x, 0.5f*size.y, -0.5f*size.z);
	v.n = D3DXVECTOR3(0, 0, 0);
	m_vecVertex.push_back(v);


	v.p = D3DXVECTOR3(0.5f*size.x, -0.5f*size.y, -0.5f*size.z);
	v.n = D3DXVECTOR3(0, 0, 0);
	m_vecVertex.push_back(v);


	v.p = D3DXVECTOR3(-0.5f*size.x, -0.5f*size.y, 0.5f*size.z);
	v.n = D3DXVECTOR3(0, 0, 0);
	m_vecVertex.push_back(v);


	v.p = D3DXVECTOR3(-0.5f*size.x, 0.5f*size.y, 0.5f*size.z);
	v.n = D3DXVECTOR3(0, 0, 0);
	m_vecVertex.push_back(v);


	v.p = D3DXVECTOR3(0.5f*size.x, 0.5f*size.y, 0.5*size.z);
	v.n = D3DXVECTOR3(0, 0, 0);
	m_vecVertex.push_back(v);

	v.p = D3DXVECTOR3(0.5f*size.x, -0.5*size.y, 0.5*size.z);
	v.n = D3DXVECTOR3(0, 0, 0);
	m_vecVertex.push_back(v);

	m_vecVertex[0].t = D3DXVECTOR2(0, 1);
	m_vecVertex[2].t = D3DXVECTOR2(1, 0);
	m_vecVertex[3].t = D3DXVECTOR2(1, 1);
	m_vecVertex[1].t = D3DXVECTOR2(0, 0);

	m_vecIndex.push_back(m_vecVertex[0]);
	m_vecIndex.push_back(m_vecVertex[2]);
	m_vecIndex.push_back(m_vecVertex[3]);
	m_vecIndex.push_back(m_vecVertex[0]);
	m_vecIndex.push_back(m_vecVertex[1]);
	m_vecIndex.push_back(m_vecVertex[2]);


	m_vecVertex[7].t = D3DXVECTOR2(0, 1);
	m_vecVertex[5].t = D3DXVECTOR2(1, 0);
	m_vecVertex[4].t = D3DXVECTOR2(1, 1);
	m_vecVertex[6].t = D3DXVECTOR2(0, 0);
	m_vecIndex.push_back(m_vecVertex[7]);
	m_vecIndex.push_back(m_vecVertex[5]);
	m_vecIndex.push_back(m_vecVertex[4]);
	m_vecIndex.push_back(m_vecVertex[7]);
	m_vecIndex.push_back(m_vecVertex[6]);
	m_vecIndex.push_back(m_vecVertex[5]);


	m_vecVertex[4].t = D3DXVECTOR2(0, 1);
	m_vecVertex[1].t = D3DXVECTOR2(1, 0);
	m_vecVertex[0].t = D3DXVECTOR2(1, 1);
	m_vecVertex[5].t = D3DXVECTOR2(0, 0);
	m_vecIndex.push_back(m_vecVertex[4]);
	m_vecIndex.push_back(m_vecVertex[1]);
	m_vecIndex.push_back(m_vecVertex[0]);
	m_vecIndex.push_back(m_vecVertex[4]);
	m_vecIndex.push_back(m_vecVertex[5]);
	m_vecIndex.push_back(m_vecVertex[1]);


	m_vecVertex[3].t = D3DXVECTOR2(0, 1);
	m_vecVertex[6].t = D3DXVECTOR2(1, 0);
	m_vecVertex[7].t = D3DXVECTOR2(1, 1);
	m_vecVertex[2].t = D3DXVECTOR2(0, 0);
	m_vecIndex.push_back(m_vecVertex[3]);
	m_vecIndex.push_back(m_vecVertex[6]);
	m_vecIndex.push_back(m_vecVertex[7]);
	m_vecIndex.push_back(m_vecVertex[3]);
	m_vecIndex.push_back(m_vecVertex[2]);
	m_vecIndex.push_back(m_vecVertex[6]);


	m_vecVertex[1].t = D3DXVECTOR2(0, 1);
	m_vecVertex[6].t = D3DXVECTOR2(1, 0);
	m_vecVertex[2].t = D3DXVECTOR2(1, 1);
	m_vecVertex[5].t = D3DXVECTOR2(0, 0);
	m_vecIndex.push_back(m_vecVertex[1]);
	m_vecIndex.push_back(m_vecVertex[6]);
	m_vecIndex.push_back(m_vecVertex[2]);
	m_vecIndex.push_back(m_vecVertex[1]);
	m_vecIndex.push_back(m_vecVertex[5]);
	m_vecIndex.push_back(m_vecVertex[6]);

	m_vecVertex[4].t = D3DXVECTOR2(0, 1);
	m_vecVertex[3].t = D3DXVECTOR2(1, 0);
	m_vecVertex[7].t = D3DXVECTOR2(1, 1);
	m_vecVertex[0].t = D3DXVECTOR2(0, 0);
	m_vecIndex.push_back(m_vecVertex[4]);
	m_vecIndex.push_back(m_vecVertex[3]);
	m_vecIndex.push_back(m_vecVertex[7]);
	m_vecIndex.push_back(m_vecVertex[4]);
	m_vecIndex.push_back(m_vecVertex[0]);
	m_vecIndex.push_back(m_vecVertex[3]);

	D3DXCreateMeshFVF(
		12,
		36,
		D3DXMESH_MANAGED,
		ST_PNT_VERTEX::FVF,
		g_pD3DDevice,
		&m_pMesh
	);

	ST_PNT_VERTEX* vM;
	m_pMesh->LockVertexBuffer(0, (void**)&vM);

	for (int i = 0; i < m_vecIndex.size(); i++)
	{
		vM[i] = m_vecIndex[i];
	}

	m_pMesh->UnlockVertexBuffer();


	WORD * wM;
	m_pMesh->LockIndexBuffer(0, (void**)&wM);

	for (int i = 0; i < m_vecIndex.size(); i++)
	{
		wM[i] = i;
	}

	m_pMesh->UnlockIndexBuffer();


	DWORD* dW;
	m_pMesh->LockAttributeBuffer(0, &dW);

	for (int i = 0; i < 4; i++) dW[i] = 0;
	for (int i = 4; i < 8; i++) dW[i] = 1;
	for (int i = 8; i < 12; i++) dW[i] = 2;

	m_pMesh->UnlockAttributeBuffer();


}

void cCube::Update()
{

}

void cCube::Render()
{
	// g_pD3DDevice->SetTransform(D3DTS_WORLD, &m_matWorld);
	// g_pD3DDevice->SetFVF(ST_PNT_VERTEX::FVF);
	// g_pD3DDevice->SetTexture(0, m_pTexture);
	// g_pD3DDevice->DrawPrimitiveUP(D3DPT_TRIANGLELIST,
	// 	m_vecIndex.size() / 3,
	// 	&m_vecIndex[0],
	// 	sizeof(ST_PNT_VERTEX));


	for (int i = 0; i < 3; i++)
	{
		g_pD3DDevice->SetTexture(0, m_pTexture[i]);
		m_pMesh->DrawSubset(i);
	}

}
