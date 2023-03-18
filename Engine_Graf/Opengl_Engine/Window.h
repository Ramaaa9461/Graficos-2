#ifndef WINDOW_H
#define WINDOW_H

#include <iostream>

#include "GL/glew.h"
#include "glfw3.h"

#include "DDLExport.h"


	class Window
	{
	private:

		GLFWwindow* window;

		DllExport Window();
		static Window* S_Window;


	public:

		static const int WINDOW_WIDTH = 1080;
		static const int WINDOW_HEIGHT = 720;

		DllExport static Window* getWindow();
		DllExport ~Window();

		DllExport int initGlfw();
		DllExport void initGlew();

		DllExport int createWindow();

		DllExport GLFWwindow* getNativeWindow();

		DllExport int GetScreenWidth();
		DllExport int GetScreenHeight();

		DllExport bool getWindowsShouldClose();

	};


#endif