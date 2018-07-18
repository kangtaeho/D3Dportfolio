#include "stdafx.h"
#include "cGameNode.h"


cGameNode::cGameNode()
{
}

cGameNode::~cGameNode()
{

}

HRESULT cGameNode::Setup()
{
	g_pDeviceManager->Setup();
	g_pFontManager->Setup();
	g_pKeyManager->Setup();
	g_pSceneManager->Setup();
	g_pCameraManager->Setup();
	g_pProgreesBar->setup();

	return S_OK;

}

void cGameNode::Update()
{
	g_pCameraManager->Update();
	g_pTimeManager->Update();
	g_pKeyManager->Update();
	g_pSkillManager->Update();
}

void cGameNode::Release()
{
	
	g_pSceneManager->Release();
	g_pFontManager->Destroy();
	g_pTextureManager->release();
	g_pXfileManager->Release();
	g_pProgreesBar->Release();


	//--디바이스는 마지막에 릴리즈 시켜야함--//
	g_pDeviceManager->Destroy();
}

void cGameNode::Render()
{

}

void cGameNode::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	g_pCameraManager->WndProc(hWnd, message, wParam, lParam);
}
