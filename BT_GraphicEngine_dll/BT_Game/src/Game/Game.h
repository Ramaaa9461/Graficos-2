#ifndef GAME_H
#define GAME_H

#include "BaseGame/baseGame.h"
#include "Player/player.h"
#include "Camera/camera.h"
#include "Shape/shape.h"
#include "Light/light.h"
#include "Light/directionalLight.h"
#include "Light/pointLight.h"
#include "Light/spotLight.h"
#include "Entity3D/Entity3D.h"
#include "ModelImporter/ModelImporter.h"
#include "Sprite/Sprite.h"
#include "PlaneBSP/PlaneBSP.h"
#include <iostream>

class DllApi Game : public BaseGame
{
private:
	//----------PLAYER-----------
	Player* player;

	//----------OBJECTS----------
	Sprite* floor;
	Entity3D* model1;
	Entity3D* model2;

	//----------LIGHTS----------
	DirectionalLight* directionalLight;
	PointLight* pointLight;
	SpotLight* spotLight;

	void Inputs();

protected:
	void Begin() override;
	void Update() override;
	void Draw() override;
	void End() override;

public:
	Game();
	~Game();
};

#endif