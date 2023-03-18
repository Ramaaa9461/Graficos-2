#ifndef BASE_GAME_H
#define BASE_GAME_H

#include "GL/glew.h"
#include "glfw3.h"

#include "DDLExport.h"

#include "Renderer.h"
#include "window.h"
#include "Timer.h"
#include "ImGuiEngine.h"

	class BaseGame
	{

	private:

		Window* window;
		Renderer* renderer;

	public:

		DllExport BaseGame();
		DllExport ~BaseGame();
		DllExport void run();


		DllExport virtual void Init() = 0;
		DllExport virtual void Update() = 0;
		DllExport virtual void DeInit() = 0;
	};



#endif
