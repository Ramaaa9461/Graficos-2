#ifndef GAME_H
#define GAME_H

#include "BaseGame.h"

#include "Shape.h"
#include "RectangleShape.h"
#include "Sprite.h"
#include "ImGuiEngine.h"
#include "CollisionManager.h"

#include "Camera.h"
#include "FirstPersonCamera.h"
#include "ThirdPersonCamera.h"

#include "Material.h"

#include "SpotLight.h"
#include "PointLight.h"
#include "DirectionalLight.h"

#include "Cube.h"

#include <iostream>

class Game : public BaseGame
{

private:

	Camera* camera;

	Shader* shader;

	Material* material;
	Material* material1;
	Material* material2;

	SpotLight* spotLight;
	SpotLight* spotLight2;

	DirectionalLight* directionalLight;
	DirectionalLight* directionalLight2;

	PointLight* pointLight;
	PointLight* pointLight2;

	Cube* cube;
	Cube* cube1;
	Cube* cube2;
	Cube* ligth;

	//SpotLight spotlight;

	Shader* initShader();
	void updateShader(Shader* shader, glm::vec3 color, glm::vec3 cameraPosition, glm::vec3 ligthPosition);


public:

	Game();
	~Game();


	void Init();
	void Input();
	void Update();
	void DeInit();

};

#endif