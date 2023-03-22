#ifndef GAME_H
#define GAME_H

#include "BaseGame.h"

#include "Shape.h"
#include "RectangleShape.h"
#include "TriangleShape.h"
#include "Sprite.h"
#include "ImGuiEngine.h"
#include "CollisionManager.h"

#include "Camera.h"

class Game : public BaseGame
{

private:

	Camera* camera;
	Entity2d* rectangleShape;

public:

	Game();
	~Game();

	void Init();
	void Input();
	void Update();
	void DeInit();

};

#endif