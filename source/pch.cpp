#include "pch.h"


unsigned int TimeInMilliseconds()
{
	cc_timeval timeNow;
	CCTime::gettimeofdayCocos2d(&timeNow, NULL);

	return ((1000 * timeNow.tv_sec) + (int)(0.001f * timeNow.tv_usec));
}