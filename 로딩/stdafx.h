#pragma once
#include "targetver.h"

#define WIN32_LEAN_AND_MEAN             // 거의 사용되지 않는 내용은 Windows 헤더에서 제외합니다.
// Windows 헤더 파일:
#include <windows.h>

// C 런타임 헤더 파일입니다.
#include <stdlib.h>
#include <iostream>
#include <memory.h>
#include <tchar.h>

using namespace std;

#include "commonMacroFunction.h"
#include "randomFunction.h"
#include "imageManager.h"
#include "keyManager.h"
#include "soundManager.h"
#include "timeManager.h"
#include "effectManager.h"
#include "sceneManager.h"
#include "utils.h"
#include "collision.h"
#include "txtData.h"
#include "database.h"
#include "keyAniManager.h"
#include "iniDataManager.h"

using namespace OMICRON_UTIL;

//========================================
// ## 디파인 문 ## 17.07.03 ##
//========================================

#define WINNAME (LPTSTR)(TEXT("Omicron API"))
#define WINSTARTX 20
#define WINSTARTY 50
#define WINSIZEX 800
#define WINSIZEY 800
#define WINSTYLE WS_CAPTION | WS_SYSMENU


//=============================================================
// ## 17.07.06 ## Singleton Define ##
//=============================================================

#define RND randomFunction::getSingleton()
#define KEYMANAGER keyManager::getSingleton()
#define IMAGEMANAGER imageManager::getSingleton()
#define SOUNDMANAGER soundManager::getSingleton()
#define TIMEMANAGER timeManager::getSingleton()
#define EFFECTMANAGER effectManager::getSingleton()
#define SCENEMANAGER sceneManager::getSingleton()
#define KEYANIMANAGER keyAniManager::getSingleton()
#define TXTDATA txtData::getSingleton()
#define DATABASE database::getSingleton()
#define INIDATA iniDataManager::getSingleton()

//=============================================================
// ## 17.07.06 ## Macro ##
//=============================================================

#define SAFE_DELETE(p) {if(p) {delete(p); (p) = NULL;}}
#define SAFE_RELEASE(p) {if(p) {(p)->release(); (p)=NULL;}}
#define SAFE_DELETE_ARRAY(p) {if(p) { delete[](p); (p) = NULL;}}

//=============================================================
// ## 17.07.06 ## 전역변수 ##
//=============================================================

extern HINSTANCE _hInstance;
extern HWND _hWnd;
extern POINT _ptMouse;
extern BOOL _leftButtonDown;