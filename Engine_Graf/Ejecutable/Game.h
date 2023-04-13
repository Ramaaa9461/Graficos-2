#ifndef GAME_H
#define GAME_H

#include "BaseGame.h"

#include "Shape.h"
#include "RectangleShape.h"
#include "Sprite.h"
#include "ImGuiEngine.h"
#include "CollisionManager.h"

#include "Camera.h"
#include "Cube.h"

#include <iostream>

class Game : public BaseGame
{

private:

	Camera* camera;
	
	Cube* cube;
	Cube* cube1;
	Cube* cube2;

	float radius = 20.0f;

public:

	Game();
	~Game();

	void Init();
	void Input();
	void Update();
	void DeInit();

};

#endif