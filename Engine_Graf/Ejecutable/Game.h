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

#include "Cube.h"

#include <iostream>

class Game : public BaseGame
{

private:

	Camera* camera;

	Shader* shader;
	Shader* shader1;
	Shader* shader2;

	Cube* cube;
	Cube* cube1;
	Cube* cube2;
	Cube* ligth;

	Shader* initShader(glm::vec3 color);
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