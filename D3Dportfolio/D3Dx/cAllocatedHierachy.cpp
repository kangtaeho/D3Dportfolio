#include "stdafx.h"
#include "cAllocatedHierachy.h"


cAllocatedHierachy::cAllocatedHierachy()
{
}


cAllocatedHierachy::~cAllocatedHierachy()
{
}

STDMETHODIMP cAllocatedHierachy::CreateFrame(LPCSTR Name, LPD3DXFRAME * ppNewFrame)
{
	ST_BONE* pBone = new ST_BONE;
	ZeroMemory(pBone, sizeof(ST_BONE));

	if (Name)
	{
		pBone->Name = new char[strlen(Name) + 1];
		UINT length = lstrlen(Name) + 1;
		strcpy_s(pBone->Name, length * sizeof(TCHAR), Name);
	}

	D3DXMatrixIdentity(&pBone->CombinedTransformationMatrix);
	D3DXMatrixIdentity(&pBone->TransformationMatrix);

	*ppNewFrame = pBone;

	return S_OK;
}

STDMETHODIMP cAllocatedHierachy::CreateMeshContainer(
	LPCSTR Name,
	const D3DXMESHDATA * pMeshData,
	const D3DXMATERIAL * pMaterials,
	const D3DXEFFECTINSTANCE * pEffectInstances,
	DWORD NumMaterials,
	const DWORD * pAdjacency,
	LPD3DXSKININFO pSkinInfo,
	LPD3DXMESHCONTAINER * ppNewMeshContainer)
{
	ST_BONE_MESH* pBoneMesh = new ST_BONE_MESH;

	ZeroMemory(pBoneMesh, sizeof(ST_BONE_MESH));

	for (DWORD i = 0; i < NumMaterials; i++)
	{
		pBoneMesh->vecMtl.push_back(pMaterials[i].MatD3D);
		std::string sFullPath = m_sFolder;
		sFullPath = sFullPath + std::string("/") + std::string(pMaterials[i].pTextureFilename);
		pBoneMesh->vecTex.push_back(g_pTextureManager->GetTexture(sFullPath.c_str()));
	}

	pSkinInfo->AddRef();
	pBoneMesh->pSkinInfo = pSkinInfo;

	pMeshData->pMesh->AddRef();
	pBoneMesh->MeshData.pMesh = pMeshData->pMesh;
	pMeshData->pMesh->CloneMeshFVF(
		pMeshData->pMesh->GetOptions(),
		pMeshData->pMesh->GetFVF(),
		g_pD3DDevice,
		&pBoneMesh->pOrigMesh);

	DWORD dwNumBones = pSkinInfo->GetNumBones();
	pBoneMesh->ppBoneMatrixPtrs = new D3DXMATRIX*[dwNumBones];
	pBoneMesh->pBoneOffsetMatrices = new D3DXMATRIX[dwNumBones];
	pBoneMesh->pCurrentBoneMatrices = new D3DXMATRIX[dwNumBones];

	for (DWORD i = 0; i < dwNumBones; i++)
	{
		pBoneMesh->pBoneOffsetMatrices[i] =
			*(pSkinInfo->GetBoneOffsetMatrix(i));
	}

	*ppNewMeshContainer = pBoneMesh;

	return S_OK;
}

STDMETHODIMP cAllocatedHierachy::DestroyFrame(
	LPD3DXFRAME pFrameToFree)
{
	ST_BONE* pBone = (ST_BONE*)pFrameToFree;

	SAFE_DELETE_ARRAY(pBone->Name);
	SAFE_DELETE(pBone);

	return S_OK;
}

STDMETHODIMP cAllocatedHierachy::DestroyMeshContainer(LPD3DXMESHCONTAINER pMeshContainerToFree)
{
	ST_BONE_MESH* pBoneMesh = (ST_BONE_MESH*)pMeshContainerToFree;

	SAFE_RELEASE(pBoneMesh->pSkinInfo);
	SAFE_RELEASE(pBoneMesh->MeshData.pMesh);
	SAFE_RELEASE(pBoneMesh->pOrigMesh);

	SAFE_DELETE_ARRAY(pBoneMesh->ppBoneMatrixPtrs);
	SAFE_DELETE_ARRAY(pBoneMesh->pBoneOffsetMatrices);
	SAFE_DELETE_ARRAY(pBoneMesh->pCurrentBoneMatrices);

	SAFE_DELETE(pBoneMesh);

	return S_OK;
}
