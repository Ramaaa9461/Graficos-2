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

	ligth = new Cube(0, 5, 0);
	ligth->setScale(glm::vec3(0.3f, 0.3f, 0.3f));

	cube->setColor( glm::vec4(1.0f, 0.0f, 0.0f, 1.0f));
	cube1->setColor(glm::vec4(0.0f, 1.0f, 0.0f, 1.0f));
	cube2->setColor(glm::vec4(0.0f, 0.0f, 1.0f, 1.0f));
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
	else if (Input::getKeyPressed(GLFW_KEY_X) || Input::getKeyPressed(GLFW_KEY_X + 32))
	{
		camera->moveUp();
	}
	else if (Input::getKeyPressed(GLFW_KEY_Z) || Input::getKeyPressed(GLFW_KEY_Z + 32))
	{
		camera->moveDown();
	}


	if (Input::getKeyPressed(GLFW_KEY_Q) || Input::getKeyPressed(GLFW_KEY_Q + 32))
	{
		camera->cameraRotationY(10.0f, 0.2f);
			
	}
	else if (Input::getKeyPressed(GLFW_KEY_E) || Input::getKeyPressed(GLFW_KEY_E + 32))
	{
		camera->cameraRotationY(-10.0f, 0.2f);
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
		ligth->addPosition(glm::vec3(-1, 0, 0));
	}
	else if (Input::getKeyPressed(GLFW_KEY_RIGHT))
	{
		ligth->addPosition(glm::vec3(1, 0, 0));
	}
	else if (Input::getKeyPressed(GLFW_KEY_DOWN))
	{
		ligth->addPosition(glm::vec3(0, 0, 1));
	}
	else if (Input::getKeyPressed(GLFW_KEY_UP))
	{
		ligth->addPosition(glm::vec3(0, 0, -1));
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
	
		cube->updateCameraPos(camera->getCameraPositon());
		cube1->updateCameraPos(camera->getCameraPositon());
		cube2->updateCameraPos(camera->getCameraPositon());

		cube->updateLigthPos(ligth->getPosition());
		cube1->updateLigthPos(ligth->getPosition());
		cube2->updateLigthPos(ligth->getPosition());
		
		
		//camera->thirdPersonCamera(cube1->getPosition(), radius);
		camera->firstPersonCamera();
		
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

	delete ligth;
}
