#include "Game.h"

Game::Game()
{
	player = nullptr;
	floor = nullptr;
	model1 = nullptr;
	model2 = nullptr;
	directionalLight = nullptr;
	pointLight1 = nullptr;
	pointLight2 = nullptr;
	spotLight1 = nullptr;
	spotLight2 = nullptr;
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

	if (pointLight1 != nullptr)
	{
		pointLight1 = nullptr;
		delete pointLight1;
	}
	
	if (pointLight2 != nullptr)
	{
		pointLight2 = nullptr;
		delete pointLight2;
	}

	if (spotLight1 != nullptr)
	{
		spotLight1 = nullptr;
		delete spotLight1;
	}

	if (spotLight2 != nullptr)
	{
		spotLight2 = nullptr;
		delete spotLight2;
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
	model1 = ModelImporter::LoadModel(renderer, "res/Models/guitarBackpack/backpack.obj", true);
	model1->SetPosition(glm::vec3(0.0f, 2.0f, 0.0f));
	
	model3 = new Entity3D(renderer);
	model3 = ModelImporter::LoadModel(renderer, "res/Models/Rana/RataEnemyV2.fbx", false);
	model3->SetPosition(glm::vec3(-10.0f, 0.0f, 10.0f));
	model3->SetRotation(glm::vec3(0.0f, 90.0f, 0.0f));

	//model4 = new Entity3D(renderer);
	//model4 = ModelImporter::LoadModel(renderer, "res/Models/Dummy/CH_Dummy_HurtV2.fbx", false);
	//model4->SetPosition(glm::vec3(10.0f, 105.0f, 10.0f));
	//model4->SetScale(glm::vec3(3));
	//model4->SetRotation(glm::vec3(0.0f, -90.0f, 0.0f));

	model2 = new Entity3D(renderer);
	model2 = ModelImporter::LoadModel(renderer, "res/Models/Rana/RanaLaserV2.fbx", false);
	model2->SetPosition(glm::vec3(0.0f, 0.0f, 20.0f));
	model2->SetRotation(glm::vec3(0.0f, 90.0f, 0.0f));

	//----------------------------LIGHTS---------------------------------

#pragma region DirectionalLightValues
	directionalLight = new DirectionalLight(renderer);

	directionalLight->SetDirection(glm::vec3(-0.2f, -1.0f, -0.3f));

	directionalLight->SetAmbient(glm::vec3(0.2f));
	directionalLight->SetDiffuse(glm::vec3(0.5f));
	directionalLight->SetSpecular(glm::vec3(1.0f));
#pragma endregion

#pragma region PointLightValues

	pointLight1 = new PointLight(renderer);

	pointLight1->SetPosition(glm::vec3(0.0f, 2.0f, 2.0f));
	pointLight1->SetAmbient(glm::vec3(0.2f));
	pointLight1->SetDiffuse(glm::vec3(0.5f));
	pointLight1->SetSpecular(glm::vec3(1.0f));

	pointLight1->SetConstant(1.0f);
	pointLight1->SetLinear(0.09f);
	pointLight1->SetQuadratic(0.032f);

	pointLight2 = new PointLight(renderer);

	pointLight2->color =  Color(255,0,0,1);
	
	pointLight2->SetPosition(glm::vec3(0.0f, 2.0f, 15.0f));
	pointLight2->SetAmbient(glm::vec3(0.2f));
	pointLight2->SetDiffuse(glm::vec3(0.5f));
	pointLight2->SetSpecular(glm::vec3(1.0f));
			  
	pointLight2->SetConstant(1.0f);
	pointLight2->SetLinear(0.09f);
	pointLight2->SetQuadratic(0.032f);

#pragma endregion

#pragma region SpotLightValues

	spotLight1 = new SpotLight(renderer);

	spotLight1->SetPosition(glm::vec3(0.0f, 2.0f, 2.0f));
	spotLight1->SetDirection(glm::vec3(0.0f, -1.0f, 0.0f));

	spotLight1->SetCutOff(12.5f);
	spotLight1->SetOuterCutOff(17.5f);

	spotLight1->SetAmbient(glm::vec3(0.2f));
	spotLight1->SetDiffuse(glm::vec3(0.5f));
	spotLight1->SetSpecular(glm::vec3(1.0f));

	spotLight1->SetConstant(1.0f);
	spotLight1->SetLinear(0.09f);
	spotLight1->SetQuadratic(0.032f);

	spotLight2 = new SpotLight(renderer);
	spotLight2->color = Color(255, 0, 0, 1);

	spotLight2->SetPosition(glm::vec3(0.0f, 2.0f, 15.0f));
	spotLight2->SetDirection(glm::vec3(0.0f, -1.0f, 0.0f));
			 
	spotLight2->SetCutOff(12.5f);
	spotLight2->SetOuterCutOff(17.5f);
			 
	spotLight2->SetAmbient(glm::vec3(0.2f));
	spotLight2->SetDiffuse(glm::vec3(0.5f));
	spotLight2->SetSpecular(glm::vec3(1.0f));
			 
	spotLight2->SetConstant(1.0f);
	spotLight2->SetLinear(0.09f);
	spotLight2->SetQuadratic(0.032f);

#pragma endregion
}

void Game::Update()
{
	player->Update();
	camera->Update();

	directionalLight->UseLight();
//	pointLight1->UseLight();
//	pointLight2->UseLight();
	spotLight1->UseLight();
	spotLight2->UseLight();

	model1->Update();
	model2->Update();
	model3->Update();
	//model4->Update();

	Inputs();
}

void Game::Draw()
{
	floor->Draw();
	model1->Draw();
	model2->Draw();
	model3->Draw();
	//model4->Draw();

	player->Draw();
}

void Game::End()
{
	player->DeInit();
	floor->DeInit();
	model1->DeInit();
	model2->DeInit();
	model3->DeInit();
	///model4->DeInit();
	
	directionalLight->DeInit();
	pointLight1->DeInit();
	pointLight2->DeInit();
	spotLight1->DeInit();
	spotLight2->DeInit();
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
		pointLight1->SetEnabled(!pointLight1->IsEnabled());
	}
	if (Input::IsKeyDown(KEY_3))
	{
		pointLight2->SetEnabled(!pointLight2->IsEnabled());
	}
	if (Input::IsKeyDown(KEY_4))
	{
		spotLight1->SetEnabled(!spotLight1->IsEnabled());
	}
	if (Input::IsKeyDown(KEY_5))
	{
		spotLight2->SetEnabled(!spotLight2->IsEnabled());
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