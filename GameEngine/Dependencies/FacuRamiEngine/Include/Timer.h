#pragma once

#include <time.h>
#include "DDLExport.h"

class Timer
{
private:

	float deltaTime = 0.0f;
	float oldTime = 0.0f;


	DllExport Timer();
	static Timer* S_Timer;

public:

	DllExport ~Timer();

	DllExport static Timer* getTimer();

	DllExport float timeBetweenFrames();

	DllExport void updateDeltaTime();

};

