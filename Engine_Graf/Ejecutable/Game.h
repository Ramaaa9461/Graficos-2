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
#include "Cube.h"

#include <iostream>

class Game : public BaseGame
{

private:

	Camera* camera;

	Shader* shader;
	Shader* shader1;
	Shader* shader2;

	Material* material;
	Material* material1;
	Material* material2;
	Material* material3;

	SpotLight* spotLight;

	Cube* cube;
	Cube* cube1;
	Cube* cube2;
	Cube* ligth;

	//SpotLight spotlight;

	Shader* initShader(glm::vec3 color);
	void updateSpotLightValues(SpotLight* spotLight, Cube* lightObject, glm::vec3 color);
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