#pragma once

#include "Camera.h"

#include "Input.h"
#include "Timer.h"

#include "DDLExport.h"


class FirstPersonCamera : public Camera
{

private: 

	float cameraSpeed;

	int keyForward;
	int keyBack;
	int keyLeft;
	int keyRight;
	int keyUp;
	int keyDown;


	DllExport void moveForward();
	DllExport void moveBack();
	DllExport void moveUp();
	DllExport void moveDown();
	DllExport void moveRight();
	DllExport void moveLeft();

public:
	
	DllExport FirstPersonCamera( float cameraSpeed = 1.0f, int keyForward = GLFW_KEY_W, int keyBack = GLFW_KEY_S, int keyLeft = GLFW_KEY_A, int keyRight = GLFW_KEY_D, int keyUp = GLFW_KEY_E, int keyDown = GLFW_KEY_Q);
	DllExport ~FirstPersonCamera();

	DllExport void rotateFirstPersonCamera(bool rotWithCursor, float sensitivityX, float sensitivityY,
		int keyRotLeft = GLFW_KEY_J, int keyRotRight = GLFW_KEY_L, int keyRotForward = GLFW_KEY_I, int keyRotBack = GLFW_KEY_K);


	DllExport void updateFirstPersonCamera();
};



