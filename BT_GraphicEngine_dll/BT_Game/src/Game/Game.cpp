#include "Game.h"

Game::Game()
{
	player = nullptr;
	floor = nullptr;
	model1 = nullptr;
	model2 = nullptr;
	directionalLight = nullptr;
	pointLight = nullptr;
	spotLight = nullptr;
}

Game::~Game()
{
	if (player != nullptr)
	{
		delete player;
		player = nullptr;
	}

	if (floor != nullptr)
	{
		delete floor;
		floor = nullptr;
	}

	if (model1 != nullptr)
	{
		delete model1;
		model1 = nullptr;
	}

	if (directionalLight != nullptr)
	{
		directionalLight = nullptr;
		delete directionalLight;
	}

	if (pointLight != nullptr)
	{
		pointLight = nullptr;
		delete pointLight;
	}

	if (spotLight != nullptr)
	{
		spotLight = nullptr;
		delete spotLight;
	}
}

void Game::Begin()
{
	renderer->SetDepth();

	//----------------------------PLAYER---------------------------------
	player = new Player(renderer);
	player->Init(camera, 5.f, 75.f);
	player->SetPosition(glm::vec3(-2.5f, 5.0f, 10.0f));

	camera->SetTarget(player);
	camera->SetOffset(10.f);

	//----------------------------OBJECTS---------------------------------
	floor = new Sprite(renderer);
	floor->Init(SPRITE_TYPE::QUAD);
	floor->LoadTexture("res/floor.png", false, TEXTURE_TYPE::BASE);
	floor->SetPosition(glm::vec3(0.0f, -0.5f, 0.0f));
	floor->SetRotationX(90.f);
	floor->SetScale(50.0f, 50.0f, 1.0f);

	model1 = new Entity3D(renderer);
	model1 = ModelImporter::LoadModel(renderer, "res/Models/guitarBackpack/backpack.obj");
	model1->SetPosition(glm::vec3(0.0f, 2.0f, 0.0f));

	model2 = new Entity3D(renderer);
	model2 = ModelImporter::LoadModel(renderer, "res/Models/guitarBackpack/backpack.obj");
	model2->SetPosition(glm::vec3(0.0f, 2.0f, 10.0f));
	model2->SetRotation(glm::vec3(0.0f, 180.0f, 0.0f));

	//----------------------------LIGHTS---------------------------------

#pragma region DirectionalLightValues
	directionalLight = new DirectionalLight(renderer);

	directionalLight->SetDirection(glm::vec3(-0.2f, -1.0f, -0.3f));

	directionalLight->SetAmbient(glm::vec3(0.2f));
	directionalLight->SetDiffuse(glm::vec3(0.5f));
	directionalLight->SetSpecular(glm::vec3(1.0f));
#pragma endregion

#pragma region PointLightValues

	pointLight = new PointLight(renderer);

	pointLight->SetPosition(glm::vec3(0.0f, 2.0f, 2.0f));
	pointLight->SetAmbient(glm::vec3(0.2f));
	pointLight->SetDiffuse(glm::vec3(0.5f));
	pointLight->SetSpecular(glm::vec3(1.0f));

	pointLight->SetConstant(1.0f);
	pointLight->SetLinear(0.09f);
	pointLight->SetQuadratic(0.032f);

#pragma endregion

#pragma region SpotLightValues

	spotLight = new SpotLight(renderer);

	spotLight->SetPosition(glm::vec3(0.0f, 2.0f, 2.0f));
	spotLight->SetDirection(glm::vec3(0.0f, 0.0f, -1.0f));

	spotLight->SetCutOff(12.5f);
	spotLight->SetOuterCutOff(17.5f);

	spotLight->SetAmbient(glm::vec3(0.2f));
	spotLight->SetDiffuse(glm::vec3(0.5f));
	spotLight->SetSpecular(glm::vec3(1.0f));

	spotLight->SetConstant(1.0f);
	spotLight->SetLinear(0.09f);
	spotLight->SetQuadratic(0.032f);

#pragma endregion
}

void Game::Update()
{
	player->Update();
	camera->Update();

	directionalLight->UseLight();
	pointLight->UseLight();
	spotLight->UseLight();

	model1->Update();
	model2->Update();

	Inputs();
}

void Game::Draw()
{
	floor->Draw();
	model1->Draw();
	model2->Draw();
	player->Draw();
}

void Game::End()
{
	player->DeInit();
	floor->DeInit();
	model1->DeInit();
	model2->DeInit();
}

void Game::Inputs()
{
	//----------------------------LIGHTS---------------------------------
	if (Input::IsKeyDown(KEY_1))
	{
		directionalLight->SetEnabled(!directionalLight->IsEnabled());
	}
	if (Input::IsKeyDown(KEY_2))
	{
		pointLight->SetEnabled(!pointLight->IsEnabled());
	}
	if (Input::IsKeyDown(KEY_3))
	{
		spotLight->SetEnabled(!spotLight->IsEnabled());
	}

	//----------------------------TRANSFORMS---------------------------------

#pragma region Input_Model

	if (Input::IsKeyPressed(GLFW_KEY_KP_1))
	{
		glm::vec3 modelScale = model1->GetScale();
		modelScale -= glm::vec3(1) * Timer::GetDeltaTime();
		model1->SetScale(modelScale);
	}
	if (Input::IsKeyPressed(GLFW_KEY_KP_2))
	{
		glm::vec3 modelScale = model1->GetScale();
		modelScale += glm::vec3(1) * Timer::GetDeltaTime();
		model1->SetScale(modelScale);
	}
	if (Input::IsKeyPressed(GLFW_KEY_KP_7))
	{
		float modelRotX = model1->GetRotationX();
		modelRotX -= 15.f * Timer::GetDeltaTime();
		model1->SetRotationX(modelRotX);
	}
	if (Input::IsKeyPressed(GLFW_KEY_KP_9))
	{
		float modelRotX = model1->GetRotationX();
		modelRotX += 15.f * Timer::GetDeltaTime();
		model1->SetRotationX(modelRotX);
	}
	if (Input::IsKeyPressed(GLFW_KEY_KP_4))
	{
		float modelPosX = model1->GetPositionX();
		modelPosX -= 10.f * Timer::GetDeltaTime();
		model1->SetPositionX(modelPosX);
	}
	if (Input::IsKeyPressed(GLFW_KEY_KP_6))
	{
		float modelPosX = model1->GetPositionX();
		modelPosX += 10.f * Timer::GetDeltaTime();
		model1->SetPositionX(modelPosX);
	}
	if (Input::IsKeyPressed(GLFW_KEY_KP_8))
	{
		float modelPosZ = model1->GetPositionZ();
		modelPosZ -= 10.f * Timer::GetDeltaTime();
		model1->SetPositionZ(modelPosZ);
	}
	if (Input::IsKeyPressed(GLFW_KEY_KP_5))
	{
		float modelPosZ = model1->GetPositionZ();
		modelPosZ += 10.f * Timer::GetDeltaTime();
		model1->SetPositionZ(modelPosZ);
	}
#pragma endregion

	if (Input::IsKeyDown(KEY_P))
	{
		bool follow = !camera->GetFollowStatus();

		camera->SetFollowStatus(follow);

		if (follow)
		{
			camera->SetTarget(model1);
		}
		else
		{
			camera->SetTarget(player);
		}

	}
}