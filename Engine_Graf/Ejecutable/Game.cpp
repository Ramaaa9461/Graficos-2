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
	rectangleShape = new RectangleShape(0, 0);


	rectangleShape->setScale(glm::vec3(0.05f, 0.05f, 1.0f));

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


	if (Input::getKeyPressed(GLFW_KEY_LEFT))
	{
		rectangleShape->addPosition(glm::vec3(-5, 0, 0));
	}
	else if (Input::getKeyPressed(GLFW_KEY_DOWN))
	{
		rectangleShape->addPosition(glm::vec3(0, -5, 0));
	}
	else if (Input::getKeyPressed(GLFW_KEY_RIGHT))
	{
		rectangleShape->addPosition(glm::vec3(5, 0, 0));
	}
	else if (Input::getKeyPressed(GLFW_KEY_UP))
	{
		rectangleShape->addPosition(glm::vec3(0, 5, 0));
	}

	/*rectangleShape->setPosition(glm::vec3(Input::getMousePosition().x, -Input::getMousePosition().y, 0.0f));

	if (Input::getMouseButtonPressed(0))
	{
		animation1->setPosition(glm::vec3(Input::getMousePosition().x, -Input::getMousePosition().y, 0.0f));
	}
	if (Input::getMouseButtonPressed(1))
	{
		animation->setPosition(glm::vec3(Input::getMousePosition().x, -Input::getMousePosition().y, 0.0f));
	}*/
}

void Game::Update()
{
	Input();

	//Render here-------------------------
	{
		rectangleShape->draw();
		camera->thirdPersonCamera(rectangleShape->getPosition());
		//camera->firstPersonCamera();
	}
	//------------------------------------

	//ImGui visual sliders



}

void Game::DeInit()
{

	delete camera;
	delete rectangleShape;
}
