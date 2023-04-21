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
	firstPersonCamera = new FirstPersonCamera(10.0f);
	thirdPersonCamera = new ThirdPersonCamera();

	cube = new Cube(-5, 0, 0);
	cube1 = new Cube(0, 0, 0);
	cube2 = new Cube(5, 0, 0);

	ligth = new Cube(0, 5, 0);
	ligth->setScale(glm::vec3(0.3f, 0.3f, 0.3f));

	cube->setColor( glm::vec4(1.0f, 0.0f, 0.0f, 1.0f));
	cube1->setColor(glm::vec4(0.0f, 1.0f, 0.0f, 1.0f));
	cube2->setColor(glm::vec4(0.0f, 0.0f, 1.0f, 1.0f));
}

void Game::Input()
{
	//Movimiento cubo -> usa WASD.
	/*
	if (Input::getKeyPressed(GLFW_KEY_A) || Input::getKeyPressed(GLFW_KEY_A + 32))
	{
		cube1->addPosition(glm::vec3(1.0f, 0.0f, 0.0f));
	}
	else if (Input::getKeyPressed(GLFW_KEY_S) || Input::getKeyPressed(GLFW_KEY_S + 32))
	{
		cube1->addPosition(glm::vec3(0.0f, -1.0f, 0.0f));
	}
	else if (Input::getKeyPressed(GLFW_KEY_D) || Input::getKeyPressed(GLFW_KEY_D + 32))
	{
		cube1->addPosition(glm::vec3(1.0f, 0.0f, 0.0f));
	}
	else if (Input::getKeyPressed(GLFW_KEY_W) || Input::getKeyPressed(GLFW_KEY_W + 32))
	{
		cube1->addPosition(glm::vec3(0.0f, 1.0f, 0.0f));
	}
	*/


	int ligthSpeed = 2;
	if (Input::getKeyPressed(GLFW_KEY_KP_4))
	{
		ligth->addPosition(glm::vec3(-ligthSpeed, 0, 0) * Timer::getTimer()->timeBetweenFrames());
	}
	else if (Input::getKeyPressed(GLFW_KEY_KP_6))
	{
		ligth->addPosition(glm::vec3(ligthSpeed, 0, 0) * Timer::getTimer()->timeBetweenFrames());
	}
	else if (Input::getKeyPressed(GLFW_KEY_KP_5))
	{
		ligth->addPosition(glm::vec3(0, 0, ligthSpeed) * Timer::getTimer()->timeBetweenFrames());
	}
	else if (Input::getKeyPressed(GLFW_KEY_KP_8))
	{
		ligth->addPosition(glm::vec3(0, 0, -ligthSpeed) * Timer::getTimer()->timeBetweenFrames());
	}	
	else if (Input::getKeyPressed(GLFW_KEY_KP_7))
	{
		ligth->addPosition(glm::vec3(0, -ligthSpeed, 0) * Timer::getTimer()->timeBetweenFrames());
	}
	else if (Input::getKeyPressed(GLFW_KEY_KP_9))
	{
		ligth->addPosition(glm::vec3(0, ligthSpeed, 0) * Timer::getTimer()->timeBetweenFrames());
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

		ligth->draw();
	
		cube->updateCameraPos(firstPersonCamera->getCameraPositon());
		cube1->updateCameraPos(firstPersonCamera->getCameraPositon());
		cube2->updateCameraPos(firstPersonCamera->getCameraPositon());

		cube->updateLigthPos(ligth->getPosition());
		cube1->updateLigthPos(ligth->getPosition());
		cube2->updateLigthPos(ligth->getPosition());
		
		firstPersonCamera->updateFirstPersonCamera();
		firstPersonCamera->rotateFirstPersonCamera(false, 1.0f, 1.0f);

		//thirdPersonCamera->updateThirdPersonCamera(cube1->getPosition());
		//thirdPersonCamera->rotateThirdPersonCamera(false, 1.0f, 1.0f);
	}
	//------------------------------------

	//ImGui visual sliders
}

void Game::DeInit()
{
	delete firstPersonCamera;
	delete thirdPersonCamera;

	delete cube;
	delete cube1;
	delete cube2;

	delete ligth;
}
