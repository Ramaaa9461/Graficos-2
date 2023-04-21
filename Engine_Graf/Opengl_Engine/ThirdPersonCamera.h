#pragma once

#include "Camera.h"

#include "Input.h"
#include "Timer.h"

#include "DDLExport.h"

class ThirdPersonCamera : public Camera
{
private:

	float radiusCameraOrbit = 0;

public:

	DllExport ThirdPersonCamera();
	DllExport ~ThirdPersonCamera();

	DllExport void rotateThirdPersonCamera(bool rotWithCursor, float sensitivityX, float sensitivityY,
		int keyRotLeft = GLFW_KEY_Q, int keyRotRight = GLFW_KEY_E, int keyRotForward = GLFW_KEY_Z, int keyRotBack = GLFW_KEY_X);


	DllExport void updateThirdPersonCamera(glm::vec3 target);
};

