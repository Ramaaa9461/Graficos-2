#include "baseGame.h" 

#include "ImGuiEngine.h"

DllExport BaseGame::BaseGame()
{

}

DllExport BaseGame::~BaseGame()
{

}

DllExport void BaseGame::run()
{
	Window* window = Window::getWindow();
	Renderer* renderer = Renderer::getRenderer();
	ImGuiEngine* imGuiEngine = ImGuiEngine::getImGuiEngine();
	Timer* timer = Timer::getTimer();

	Init();

	while (window->getWindowsShouldClose())
	{
		renderer->Clear();
		timer->updateDeltaTime();
		imGuiEngine->imGuiStartDraw();

		Update();

		imGuiEngine->imGuiEndDraw();
		glfwSwapBuffers(window->getNativeWindow());
		glfwPollEvents();
	}

	DeInit();

	delete imGuiEngine;

	delete window;

	delete renderer;

	//return 0;
}



