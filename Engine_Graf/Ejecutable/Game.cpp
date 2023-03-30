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
	falloutSprite = new Sprite("Logo.jpg", 10, 0);
	falloutSprite2 = new Sprite("Logo.jpg", -10, 0);


	falloutSprite->setScale(glm::vec3(0.05f, 0.05f, 1.0f));
	//falloutSprite->setRotation(glm::vec3(70.0f, 60.0f, 0.0f));
	
	falloutSprite2->setScale(glm::vec3(0.05f, 0.05f, 1.0f));

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

	if (Input::getKeyPressed(GLFW_KEY_Q) || Input::getKeyPressed(GLFW_KEY_Q + 32))
	{
		radius += 10.0f * Timer::getTimer()->timeBetweenFrames();
	}
	else if (Input::getKeyPressed(GLFW_KEY_E) || Input::getKeyPressed(GLFW_KEY_E + 32))
	{
		radius -= 10.0f * Timer::getTimer()->timeBetweenFrames();
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

}

void Game::Update()
{
	Input();

	//Render here-------------------------
	{
		rectangleShape->draw();
		falloutSprite->drawTexture();
		falloutSprite2->drawTexture();
		
		camera->thirdPersonCamera(rectangleShape->getPosition(), radius);
		

		//camera->firstPersonCamera();
		camera->followCursor(Input::getMousePosition() * Timer::getTimer()->timeBetweenFrames(), 0.08f, 0.1f);
	
		//camera->cameraRotationX(Input::getMousePosition().x * Timer::getTimer()->timeBetweenFrames(), 0.01f);
		//camera->cameraRotationY(Input::getMousePosition().y * Timer::getTimer()->timeBetweenFrames(), 0.1f);
		//camera->cameraRotationZ(Input::getMousePosition().x * Timer::getTimer()->timeBetweenFrames(), 0.01f);
	}
	//------------------------------------

	//ImGui visual sliders



}

void Game::DeInit()
{
	delete camera;
	delete falloutSprite;
	delete falloutSprite2;
	delete rectangleShape;
}
