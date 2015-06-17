#ifndef __pch_h_included__
#define __pch_h_included__


#ifdef WIN32

	#define WIN32_LEAN_AND_MEAN
	#include <windows.h>
	#include <tchar.h>

#endif // #ifdef WIN32


#include "CCStdC.h"
#include "cocos2d.h"
using namespace cocos2d;

// Forward declarations
class Map;
class Player;

// Singletons
extern Map * g_Map;

// Custom math
#define RADIAN_TO_DEGREE(X) (180.0f / M_PI * (X))


#endif // #ifndef __pch_h_included__