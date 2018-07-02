#include "stdafx.h"
#include "cGameNode.h"


cGameNode::cGameNode()
{
}

cGameNode::~cGameNode()
{
	// 소멸자는 버추얼 하더라도
	// 자식 먼저 생성되고 마지막으로 부모가 선언됨(확인해봄)
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
