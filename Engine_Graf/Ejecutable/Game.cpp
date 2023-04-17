#include "Game.h"

#include "Input.h"

Game::Game()
{
	BaseGame::run();
}

Game::~Game()
{

}


void Game::Init()
{
	camera = new Camera();

	cube = new Cube(-5, 0, 0);
	cube1 = new Cube(0, 0, 0);
	cube2 = new Cube(5, 0, 0);

	cube->setColor( glm::vec4(0.2f, 0.6f, 0.f, 1.0f));
	cube1->setColor(glm::vec4(0.4f, 0.4f, 0.4f, 1.0f));
	cube2->setColor(glm::vec4(0.6f, 0.2f, 0.9f, 1.0f));
}

void Game::Input()
{
	if (Input::getKeyPressed(GLFW_KEY_A) || Input::getKeyPressed(GLFW_KEY_A + 32))
	{
		camera->moveLeft();
	}
	else if (Input::getKeyPressed(GLFW_KEY_S) || Input::getKeyPressed(GLFW_KEY_S + 32))
	{
		camera->moveBack();
	}
	else if (Input::getKeyPressed(GLFW_KEY_D) || Input::getKeyPressed(GLFW_KEY_D + 32))
	{
		camera->moveRight();
	}
	else if (Input::getKeyPressed(GLFW_KEY_W) || Input::getKeyPressed(GLFW_KEY_W + 32))
	{
		camera->moveForward();
	}

	if (Input::getKeyPressed(GLFW_KEY_Q) || Input::getKeyPressed(GLFW_KEY_Q + 32))
	{
		radius += 10.0f * Timer::getTimer()->timeBetweenFrames();
	}
	else if (Input::getKeyPressed(GLFW_KEY_E) || Input::getKeyPressed(GLFW_KEY_E + 32))
	{
		radius -= 10.0f * Timer::getTimer()->timeBetweenFrames();
	}

	radius += Input::getScrollInput() * Timer::getTimer()->timeBetweenFrames();
	
	if (radius < 8.0f)
	{
		radius = 8.1f;
	}
	else if (radius > 100.0f)
	{
		radius = 99.9f;
	}


	if (Input::getKeyPressed(GLFW_KEY_LEFT))
	{
		cube1->addPosition(glm::vec3(-5, 0, 0));
	}
	else if (Input::getKeyPressed(GLFW_KEY_DOWN))
	{
		cube1->addPosition(glm::vec3(0, -5, 0));
	}
	else if (Input::getKeyPressed(GLFW_KEY_RIGHT))
	{
		cube1->addPosition(glm::vec3(5, 0, 0));
	}
	else if (Input::getKeyPressed(GLFW_KEY_UP))
	{
		cube1->addPosition(glm::vec3(0, 5, 0));
	}	
}

void Game::Update()
{
	Input();

	//Render here-------------------------
	{
		cube->draw();
		cube1->draw();
		cube2->draw();
	

//		camera->thirdPersonCamera(cube1->getPosition(), radius);
		//camera->firstPersonCamera();
		
		camera->followCursor(Input::getMousePosition() * Timer::getTimer()->timeBetweenFrames(), 0.08f, 0.1f);
	}
	//------------------------------------

	//ImGui visual sliders
}

void Game::DeInit()
{
	delete camera;
	delete cube;
	delete cube1;
	delete cube2;
}
