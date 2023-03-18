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
	animation = new Sprite("Mario.png", 200, 200);
	animation1 = new Sprite("Mario.png", 400, 200);
	rectangleShape = new RectangleShape(200, 300);


	((Sprite*)animation)->CreateAnimation(0, 64, 1, 4, 4);
	((Sprite*)animation1)->CreateAnimation(0, 128, 2, 4, 4);
}

void Game::Input()
{
	if (Input::getKeyPressed(GLFW_KEY_A) || Input::getKeyPressed(GLFW_KEY_A + 32))
	{
		animation->addPosition(glm::vec3(-5, 0, 0));
	}
	else if (Input::getKeyPressed(GLFW_KEY_S) || Input::getKeyPressed(GLFW_KEY_S + 32))
	{
		animation->addPosition(glm::vec3(0, -5, 0));
	}
	else if (Input::getKeyPressed(GLFW_KEY_D) || Input::getKeyPressed(GLFW_KEY_D + 32))
	{
		animation->addPosition(glm::vec3(5, 0, 0));
	}
	else if (Input::getKeyPressed(GLFW_KEY_W) || Input::getKeyPressed(GLFW_KEY_W + 32))
	{
		animation->addPosition(glm::vec3(0, 5, 0));
	}
}

void Game::Update()
{
	Input();
	//CalculateVertices----------------------------------------
	{
		animation->calculateVertices();
		animation1->calculateVertices();
	}
	//Update animation-------------------------

	((Sprite*)animation)->updateAnimation();
	((Sprite*)animation1)->updateAnimation();

	//Render here-------------------------
	{
		animation->draw();
		animation1->draw();
		rectangleShape->draw();
	}
	//------------------------------------

	//ImGui visual sliders

	if (CollisionManager::IntersectPolygons(animation->getVertices(), 4, animation1->getVertices(), 4, normal, depth))
	{
		animation->addPosition(-normal * (depth / 2));
		animation1->addPosition(+normal * (depth / 2));
	}


}

void Game::DeInit()
{
	delete animation;
	delete animation1;
}
