#include "Timer.h"

#include "glfw3.h"

Timer* Timer::S_Timer = nullptr;

Timer::Timer(){}

Timer::~Timer(){}

DllExport Timer* Timer::getTimer()
{
	if (S_Timer == nullptr) {
		S_Timer = new Timer();
	}
	return S_Timer;
}

DllExport float Timer::timeBetweenFrames()
{
	return deltaTime;
}

DllExport void Timer::updateDeltaTime()
{
	deltaTime = glfwGetTime() - oldTime;
	oldTime = glfwGetTime();
}

