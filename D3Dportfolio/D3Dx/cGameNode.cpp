#include "stdafx.h"
#include "cGameNode.h"


cGameNode::cGameNode()
{
}

cGameNode::~cGameNode()
{
	// �Ҹ��ڴ� ���߾� �ϴ���
	// �ڽ� ���� �����ǰ� ���������� �θ� �����(Ȯ���غ�)
	g_pFontManager->Destroy();
	g_pDeviceManager->Destroy();
}

void cGameNode::Setup()
{
	g_pDeviceManager->Setup();
	g_pFontManager->Setup();
	g_pKeyManager->Setup();
}

void cGameNode::Update()
{
	g_pTimeManager->Update();
	g_pKeyManager->Update();
}

void cGameNode::Render()
{

}
