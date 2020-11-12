#pragma once
#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>

// Вообще ничего не нужно объявлять. Заголовок файла подключить и все
class __CCRTDebug {
public:
	__CCRTDebug() { _CrtSetDbgFlag( _CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF ); }
	~__CCRTDebug() { _CrtDumpMemoryLeaks(); }
}g_debug;