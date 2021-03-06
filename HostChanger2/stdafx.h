// stdafx.h : include file for standard system include files,
// or project specific include files that are used frequently, but
// are changed infrequently
//

#pragma once

#include "targetver.h"

#define WIN32_LEAN_AND_MEAN             // Exclude rarely-used stuff from Windows headers
// Windows Header Files:
#include <windows.h>

// C RunTime Header Files
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>

#include <vector>
#include <string>
#include <iostream>
#include <windows.h>
#include <ShellAPI.h>

#include <vector>
using namespace std;
#include "xVariables.h"


#pragma comment(lib, "iphlpapi.lib")
#pragma comment(lib, "urlmon.lib")
#pragma comment(lib,"wininet.lib")

#define _MOD_CRYPT		(false)

#define _MOD_DECRYPT	(false)

#define _MOD_DEV		(true)

#define _MOD_PROD		(true)


#define _DEBUG_RUNTIME	(false)
#define _DEBUG_CONSOLE	(false)
#define _DEBUG_FILE		(false)

#define _SSL (false)

#if _SSL
const std::wstring http_prefix = L"https://";
#else
const std::wstring http_prefix = L"http://";
#endif

#define _REST_API_URI (L"rest")
#define _REST_API_VERSION (L"v5")

// AV FUD Check
// True		- enabled for Production mode
// False	- disabled for Developer mode
#define _ENABLE_Elevated			(true)
#define _ENABLE_RunKeeper			(true)
#define _ENABLE_initClient			(true)
#define _ENABLE_GetClientData		(true)
#define _ENABLE_CheckAgent			(true)
#define _ENABLE_DoCommands			(true)
#define _ENABLE_GetAttachments		(true)
#define _ENABLE_PostClientData		(true)


#if _MOD_CRYPT

#define _DEBUG_RUNTIME				(true)
#define _DEBUG_CONSOLE				(true)

#endif


#if _MOD_DECRYPT

#define _DEBUG_RUNTIME				(true)
#define _DEBUG_CONSOLE				(true)

#endif

#if _MOD_DEV

#define _DEBUG_RUNTIME				(false)
#define _DEBUG_CONSOLE				(true)
#define _DEBUG_FILE					(true)

#define _ENABLE_Elevated			(false)
#define _ENABLE_RunKeeper			(false)
#define _ENABLE_DoCommands			(false)
#define _ENABLE_CheckAgent			(false)

#endif