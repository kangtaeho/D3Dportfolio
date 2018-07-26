#include "stdafx.h"
#include "cSkinnedMesh.h"
#include "cAllocatedHierachy.h"

cSkinnedMesh::cSkinnedMesh()
	: m_pRoot(NULL)
	, m_pAnimController(NULL)
	, m_fBlendTime(1.0f)
	, m_fPassedBlendTime(0.0f)
	, m_bBlend(false)
{
}

cSkinnedMesh::~cSkinnedMesh()
{
	Release(m_pRoot);
	SAFE_RELEASE(m_pAnimController);
	SAFE_RELEASE(m_pAnimControllerParent);
}

void cSkinnedMesh::Release(LPD3DXFRAME pFrame)
{
	cAllocatedHierachy ah;
	D3DXFrameDestroy(m_pRoot, &ah);
}

void cSkinnedMesh::Setup(const char* szFolder, const char* szFile)
{
	std::string sFullPath(szFolder);

	cAllocatedHierachy ah;
	ah.SetFolder(sFullPath);

	sFullPath = sFullPath + std::string("/") + std::string(szFile);

	D3DXLoadMeshHierarchyFromX(sFullPath.c_str(),
		D3DXMESH_MANAGED | D3DXMESH_32BIT,
		g_pD3DDevice,
		&ah,
		0,
		&m_pRoot,
		&m_pAnimController);

	SetupBoneMatrixPtrs(m_pRoot); 

	m_pAnimController->CloneAnimationController(m_pAnimController->GetMaxNumAnimationOutputs(), m_pAnimController->GetMaxNumAnimationSets(), m_pAnimController->GetMaxNumTracks(), m_pAnimController->GetMaxNumEvents(), &m_pAnimControllerParent);
}

void cSkinnedMesh::Update(LPD3DXANIMATIONCONTROLLER pAnimController)
{
	m_pAnimController = pAnimController;
	Update(m_pRoot, NULL);
	UpdateSkinnedMesh(m_pRoot);
	Render(m_pRoot);
}

void cSkinnedMesh::Update(LPD3DXFRAME pFrame, LPD3DXFRAME pParent)
{
	ST_BONE* pBone = (ST_BONE*)pFrame;
	pBone->CombinedTransformationMatrix = pBone->TransformationMatrix;

	if (pBone == m_pRoot && pParent == NULL)
	{

	}
	else if (pParent)
	{
		pBone->CombinedTransformationMatrix *=
			((ST_BONE*)pParent)->CombinedTransformationMatrix;
	}

	if (pFrame->pFrameSibling)
	{
		Update(pFrame->pFrameSibling, pParent);
	}

	if (pFrame->pFrameFirstChild)
	{
		Update(pFrame->pFrameFirstChild, pFrame);
	}
}

void cSkinnedMesh::UpdateSkinnedMesh(LPD3DXFRAME pFrame)
{
	// TODO 1 : pCurrentBoneMatrices를 계산
	// pCurrentBoneMatrices = pBoneOffsetMatrices * ppBoneMatrixPtrs
	if (pFrame && pFrame->pMeshContainer)
	{
		ST_BONE_MESH* pBoneMesh = (ST_BONE_MESH*)pFrame->pMeshContainer;

		if (pBoneMesh->pSkinInfo)
		{
			DWORD dwNumBones = pBoneMesh->pSkinInfo->GetNumBones();
			for (DWORD i = 0; i < dwNumBones; i++)
			{
				pBoneMesh->pCurrentBoneMatrices[i] =
					pBoneMesh->pBoneOffsetMatrices[i] *
					*(pBoneMesh->ppBoneMatrixPtrs[i]);
			}

			// TODO 2 : Mesh 정보를 업데이트
			BYTE*	src = NULL;
			BYTE*	dst = NULL;

			pBoneMesh->pOrigMesh->LockVertexBuffer(D3DLOCK_READONLY, (void**)&src);
			pBoneMesh->MeshData.pMesh->LockVertexBuffer(0, (void**)&dst);

			pBoneMesh->pSkinInfo->UpdateSkinnedMesh(
				pBoneMesh->pCurrentBoneMatrices,
				NULL, src, dst);

			pBoneMesh->pOrigMesh->UnlockVertexBuffer();
			pBoneMesh->MeshData.pMesh->UnlockVertexBuffer();
		}
	}

	// TODO 3 : 재귀함수 호출
	if (pFrame->pFrameSibling)
	{
		UpdateSkinnedMesh(pFrame->pFrameSibling);
	}

	if (pFrame->pFrameFirstChild)
	{
		UpdateSkinnedMesh(pFrame->pFrameFirstChild);
	}
}

void cSkinnedMesh::Render(LPD3DXFRAME pFrame)
{
	if (pFrame == NULL)
		pFrame = m_pRoot;

	ST_BONE* pBone = (ST_BONE*)pFrame;

	if (pBone->pMeshContainer)
	{
		ST_BONE_MESH* pBoneMesh = (ST_BONE_MESH*)pBone->pMeshContainer;
		if (pBoneMesh->MeshData.pMesh)
		{
			for (DWORD i = 0; i < pBoneMesh->vecMtl.size(); i++)
			{
				g_pD3DDevice->SetTexture(0, pBoneMesh->vecTex[i]);
				g_pD3DDevice->SetMaterial(&pBoneMesh->vecMtl[i]);
				pBoneMesh->MeshData.pMesh->DrawSubset(i);
			}
		}
	}

	if (pFrame->pFrameSibling)
	{
		Render(pFrame->pFrameSibling);
	}

	if (pFrame->pFrameFirstChild)
	{
		Render(pFrame->pFrameFirstChild);
	}
}

void cSkinnedMesh::SetupBoneMatrixPtrs(LPD3DXFRAME pFrame)
{
	if (pFrame && pFrame->pMeshContainer)
	{
		ST_BONE_MESH* pBoneMesh = (ST_BONE_MESH*)pFrame->pMeshContainer;
		if (pBoneMesh->pSkinInfo)
		{
			DWORD dwNumBones = pBoneMesh->pSkinInfo->GetNumBones();
			for (DWORD i = 0; i < dwNumBones; i++)
			{
				ST_BONE* pBone = (ST_BONE*)D3DXFrameFind(m_pRoot,
					pBoneMesh->pSkinInfo->GetBoneName(i));

				pBoneMesh->ppBoneMatrixPtrs[i] =
					&(pBone->CombinedTransformationMatrix);
			}
		}
	}

	if (pFrame->pFrameFirstChild)
	{
		SetupBoneMatrixPtrs(pFrame->pFrameFirstChild);
	}

	if (pFrame->pFrameSibling)
	{
		SetupBoneMatrixPtrs(pFrame->pFrameSibling);
	}
}

void cSkinnedMesh::SetAnimationIndexBlend(int nIndex)
{
	m_bBlend = true;
	m_fPassedBlendTime = 0.0f;

	int n = m_pAnimController->GetNumAnimationSets();
	if (nIndex > n)	nIndex = nIndex % n;

	LPD3DXANIMATIONSET	pPrevAniSet = NULL;
	LPD3DXANIMATIONSET	pNextAniSet = NULL;

	D3DXTRACK_DESC	stTrackDesc;
	m_pAnimController->GetTrackDesc(0, &stTrackDesc);
	m_pAnimController->GetTrackAnimationSet(0, &pPrevAniSet);

	m_pAnimController->SetTrackAnimationSet(1, pPrevAniSet);
	m_pAnimController->SetTrackDesc(1, &stTrackDesc);

	m_pAnimController->GetAnimationSet(nIndex, &pNextAniSet);
	m_pAnimController->SetTrackAnimationSet(0, pNextAniSet);

	m_pAnimController->SetTrackWeight(0, 0.0f);
	m_pAnimController->SetTrackWeight(1, 1.0f);

	SAFE_RELEASE(pPrevAniSet);
	SAFE_RELEASE(pNextAniSet);
}
