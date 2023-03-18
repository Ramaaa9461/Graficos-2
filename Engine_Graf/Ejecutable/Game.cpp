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
	animation = new Sprite("Characters.png", 200, 200);
	
	animation1 = new Sprite("Mario.png", 400, 200);
	sprite1 = new Sprite("Logo.jpg", 300, 200);
	rectangleShape = new RectangleShape(200, 300);


	((Sprite*)animation)->CreateAnimation(9, 7, 1, 12, 8, 3);
	((Sprite*)animation1)->CreateAnimation(0, 0, 1, 4, 4);
	rectangleShape->setScale(glm::vec3(0.2f, 0.2f, 1.0f));
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


	if (Input::getKeyPressed(GLFW_KEY_LEFT))
	{
		animation1->addPosition(glm::vec3(-5, 0, 0));
	}
	else if (Input::getKeyPressed(GLFW_KEY_DOWN))
	{
		animation1->addPosition(glm::vec3(0, -5, 0));
	}
	else if (Input::getKeyPressed(GLFW_KEY_RIGHT))
	{
		animation1->addPosition(glm::vec3(5, 0, 0));
	}
	else if (Input::getKeyPressed(GLFW_KEY_UP))
	{
		animation1->addPosition(glm::vec3(0, 5, 0));
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
	//CalculateVertices----------------------------------------
	{
		animation->calculateVertices();
		animation1->calculateVertices();
	}
	//Update animation-------------------------

	((Sprite*)animation)->updateAnimation(1.0f);
//	((Sprite*)animation1)->updateAnimation(1.0f);

	//Render here-------------------------
	{
		((Sprite*)animation)->drawTexture();
		((Sprite*)animation1)->drawTexture();
		((Sprite*)sprite1)->drawTexture();
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
