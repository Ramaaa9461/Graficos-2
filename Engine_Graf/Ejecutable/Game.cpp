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
	shader = initShader();

	//Material ORO
	material = new Material(glm::vec3(0.24725f, 0.1995f, 0.0745f), glm::vec3(0.75164f, 0.60648f, 0.22648f), glm::vec3(0.628281f, 0.555802f, 0.366065f), 0.4f);

	//Pearl
	material1 = new Material(glm::vec3(0.25f, 0.20725f, 0.20725f), glm::vec3(1.0f, 0.829f, 0.829f), glm::vec3(0.296648f, 0.296648f, 0.296648f), 0.088f);

	//RED Rubben
	material2 = new Material(glm::vec3(0.05f, 0.0f, 0.0f), glm::vec3(0.5f, 0.4f, 0.4f), glm::vec3(0.7f, 0.04f, 0.04f), 0.078125f);

	camera = new FirstPersonCamera(10.0f);
	//camera = new ThirdPersonCamera();

	cube = new Cube(-5, 0, 0, shader);
	cube1 = new Cube(0, 0, 0, shader);
	cube2 = new Cube(5, 0, 0, shader);

	cube->setMaterial(material2);
	cube1->setMaterial(material);
	cube2->setMaterial(material1);

	ligth = new Cube(0, 2, 0, shader);
	ligth->setScale(glm::vec3(0.3f, 0.3f, 0.3f));

	model = new Model("res/models/StoneBridge.fbx", 0.0f, 0.0f, 4.0f, shader);
	model->setTexture("StoneBridge.png");
	model->setScale(glm::vec3(0.05f));

	spotLight = new SpotLight();
	spotLight2 = new SpotLight();

	pointLight = new PointLight();
	pointLight2 = new PointLight();

	directionalLight = new DirectionalLight();
	directionalLight2 = new DirectionalLight();
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
		spotLight->setPosition(ligth->getPosition());
		ligth->setPosition(spotLight->getPosition());

		//ligth->draw();

		model->draw();

		//cube->draw();
		//cube1->draw();
		//cube2->draw();
		updateShader(shader, glm::vec3(1.0f, 0.0f, 0.0f), camera->getCameraPositon(), ligth->getPosition());

		((FirstPersonCamera*)camera)->updateFirstPersonCamera();
		((FirstPersonCamera*)camera)->rotateFirstPersonCamera(false, 1.0f, 1.0f);

		//((ThirdPersonCamera*)camera)->updateThirdPersonCamera(cube1->getPosition());
		//((ThirdPersonCamera*)camera)->rotateThirdPersonCamera(false, 1.0f, 1.0f);
	}
}

void Game::DeInit()
{
	delete camera;

	delete model;

	delete cube;
	delete cube1;
	delete cube2;

	delete ligth;

	delete spotLight;
	delete spotLight2;

	delete pointLight;
	delete pointLight2;

	delete directionalLight;
	delete directionalLight2;


	delete material;
	delete material1;
	delete material2;

	delete shader;
}

Shader* Game::initShader()
{
	shader = new Shader(ShaderType::noTexture);

	return shader;
}

void Game::updateShader(Shader* shader, glm::vec3 color, glm::vec3 cameraPosition, glm::vec3 ligthPosition)
{
	shader->Bind();

	shader->SetUniforms3f("viewPos", cameraPosition.x, cameraPosition.y, cameraPosition.z);

	shader->Unbind();

	spotLight->setUniforms(shader);
	spotLight2->setUniforms(shader);

	pointLight->setUniforms(shader);
	pointLight2->setUniforms(shader);

	directionalLight->setUniforms(shader);
	//directionalLight2->setUniforms(shader);
}
