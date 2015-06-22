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
using namespace std;

// Forward declarations
class GameLogic;
class Map;
class Player;
class Enemy;
class Weapon;
class Projectile;

// short type names
typedef unsigned int uint;
typedef Enemy Unit;
typedef vector <Unit *> UnitVector;

// Singletons
extern Map * g_Map;
extern Player * g_Player;
extern GameLogic * g_GameLogic;

// Custom math
#define RADIAN_TO_DEGREE(X) (180.0f / M_PI * (X))

#define RND_FLOAT ((float)rand() / 32768.f)
#define RND_INTERVAL(FROM, TO) ((FROM) + (RND_FLOAT * ((TO) - (FROM))))


// general utils
unsigned int TimeInMilliseconds();


#endif // #ifndef __pch_h_included__