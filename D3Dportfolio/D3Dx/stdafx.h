// stdafx.h : 자주 사용하지만 자주 변경되지는 않는
// 표준 시스템 포함 파일 또는 프로젝트 관련 포함 파일이
// 들어 있는 포함 파일입니다.
//

#pragma once

#include "targetver.h"

#define WIN32_LEAN_AND_MEAN             // 거의 사용되지 않는 내용은 Windows 헤더에서 제외합니다.
// Windows 헤더 파일:
#include <windows.h>

// C 런타임 헤더 파일입니다.
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>
#include <assert.h>
#include <vector>
#include <map>
#include <bitset>


// TODO: 프로그램에 필요한 추가 헤더는 여기에서 참조합니다.
#include <d3dx9.h>
#pragma comment(lib, "d3d9.lib")
#pragma comment(lib, "d3dx9.lib")

extern HWND g_hWnd;

#define SINGLETONE(class_name) \
private: \
	class_name(); \
	~class_name(); \
public: \
	static class_name* GetInstance() \
	{ \
		static class_name instance; \
		return &instance; \
	}


#define SYNTHESIZE(varType, varName, funName)\
protected: varType varName;\
public: varType Get##funName(void) { return varName; }\
public: void Set##funName(varType var) { varName = var; }

#define SYNTHESIZE_REF(varType, varName, funName)\
protected: varType varName;\
public: varType& Get##funName(void) { return varName; }\
public: void Set##funName(varType& var) { varName = var; }


struct ST_PC_VERTEX
{
	D3DXVECTOR3 p;
	D3DCOLOR	c;

	enum {
		FVF = D3DFVF_XYZ | D3DFVF_DIFFUSE
	};
};

struct ST_PNT_VERTEX
{
	D3DXVECTOR3 p;
	D3DXVECTOR3 n;
	D3DXVECTOR2 t;

	enum {
		FVF = D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_TEX1
	};
};

struct stCollisionMap
{
	std::string sObjName;
	D3DXVECTOR3 vPosition;
	std::vector<D3DXVECTOR3> vecTotalVertex;
};

struct ST_UI_SIZE
{
	int nWidth;
	int nHeight;
	ST_UI_SIZE() : nWidth(0), nHeight(0) {}
	ST_UI_SIZE(int _nWidth, int _nHeight)
		: nWidth(_nWidth), nHeight(_nHeight) {}
};
enum tagUiState
{
	UI = 1,
	UIANIMATION,
	SUBUI,
	PROGRESSBAR,
	BUTTON,
	ANIMATION,
	ITEM,
	STATUS,
	SCOREBOARD
};
enum tagItemState
{
	START_ITEM = 0,
	EARLY_ITEM,
	CORE_ITEM,
	BASIC_ITEM,
	STATE_END
};
enum tagItemInformation
{
	ACCESSORY,
	EQUIPABLE,
	CONSUME
};


#define WINSTARTX	50
#define WINSTARTY	50
#define WINSIZEX 1280
#define WINSIZEY 800
#define WINSTYLE WS_CAPTION | WS_SYSMENU

#define SAFE_DELETE(p){if(p) delete p; p=NULL;}
#define SAFE_DELETE_ARRAY(p){if(p) delete []p; p=NULL;}
#define SAFE_RELEASE(p){if(p) p->Release(); p=NULL;}

#include "cDeviceManager.h"
#include "cXManager.h"
#include "cFontManager.h"
#include "cTimeManager.h"
#include "cTextureManager.h"
#include "cKeyManager.h"
#include "cSceneManager.h"
#include "cCameraManager.h"
#include "cSkillManager.h"

#include "cCollisionManager.h"


// 매크로
#include "D3DMacroFunction.h"