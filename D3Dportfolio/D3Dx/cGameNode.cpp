#include "stdafx.h"
#include "cGameNode.h"


cGameNode::cGameNode()
{
}

cGameNode::~cGameNode()
{
	// �Ҹ��ڴ� ���߾� �ϴ���
	// �ڽ� ���� �����ǰ� ���������� �θ� �����(Ȯ���غ�)
	// �Ҹ��ڸ� Release�� ���
	g_pSceneManager->Release();

	g_pFontManager->Destroy();
	g_pDeviceManager->Destroy();
}

HRESULT cGameNode::Setup()
{
	g_pDeviceManager->Setup();
	g_pFontManager->Setup();
	g_pKeyManager->Setup();
	g_pSceneManager->Setup();

	return S_OK;

}

void cGameNode::Update()
{
	g_pTimeManager->Update();
	g_pKeyManager->Update();
}

void cGameNode::Render()
{

}
