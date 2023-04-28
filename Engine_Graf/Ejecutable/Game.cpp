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
	shader =  initShader(glm::vec3(1.0f, 0.0f, 0.0f));
	shader2 = initShader(glm::vec3(0.0f, 1.0f, 0.0f));
	shader1 = initShader(glm::vec3(0.0f, 0.0f, 1.0f));

	camera = new FirstPersonCamera(10.0f);
	//camera = new ThirdPersonCamera();


	cube =  new Cube(-5, 0, 0, shader);
	cube1 = new Cube(0, 0, 0, shader1);
	cube2 = new Cube(5, 0, 0, shader2);

	ligth = new Cube(0, 5, 0, shader);
	ligth->setScale(glm::vec3(0.3f, 0.3f, 0.3f));
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

	//Render here----------------------------
	{

		ligth->draw();
	
		updateShader(shader,  glm::vec3(1.0f, 0.0f, 0.0f), camera->getCameraPositon(), ligth->getPosition());
		 cube->draw();
		updateShader(shader1, glm::vec3(0.0f, 1.0f, 0.0f), camera->getCameraPositon(), ligth->getPosition());
		cube1->draw();
		updateShader(shader2, glm::vec3(0.0f, 0.0f, 1.0f), camera->getCameraPositon(), ligth->getPosition());
		cube2->draw();


		((FirstPersonCamera*)camera)->updateFirstPersonCamera();
		((FirstPersonCamera*)camera)->rotateFirstPersonCamera(false, 1.0f, 1.0f);


		//((ThirdPersonCamera*)camera)->updateThirdPersonCamera(cube1->getPosition());
		//((ThirdPersonCamera*)camera)->rotateThirdPersonCamera(false, 1.0f, 1.0f);
	}
}

void Game::DeInit()
{
	delete camera;

	delete cube;
	delete cube1;
	delete cube2;

	delete ligth;

	delete shader;
	delete shader1;
	delete shader2;
}

Shader* Game::initShader(glm::vec3 color)
{
	shader = new Shader(ShaderType::noTexture);

	shader->Bind();
	shader->SetUniforms4f("u_Color", color.x, color.y, color.z, 1.0f);
	shader->SetUniforms4f("lightColor", 1.0f, 1.0f, 1.0f, 1.0f);
	shader->SetUniforms4f("lightPos", -10.0f, 0.0f, 0.0f, 1.0f);
	shader->SetUniforms4f("viewPos", 0.0f, 0.0f, 10.0f, 1.0f);
	shader->SetUniforms1f("ambientStrength", 0.2f);
	shader->SetUniforms1f("specularStrength", 10.0f);
	shader->Unbind();

	return shader;
}

void Game::updateShader(Shader* shader, glm::vec3 color ,glm::vec3 cameraPosition, glm::vec3 ligthPosition)
{
	shader->Bind();

	shader->SetUniforms4f("u_Color", color.x, color.y, color.z, 1.0f);
	shader->SetUniforms4f("lightColor", 1.0f, 1.0f, 1.0f, 1.0f);
	shader->SetUniforms1f("ambientStrength", 0.2f);
	shader->SetUniforms1f("specularStrength", 10.0f);

	shader->SetUniforms4f("viewPos", cameraPosition.x, cameraPosition.y, cameraPosition.z, 1.0f);
	shader->SetUniforms4f("lightPos", ligthPosition.x, ligthPosition.y, ligthPosition.z, 1.0f);

	shader->Unbind();
}
