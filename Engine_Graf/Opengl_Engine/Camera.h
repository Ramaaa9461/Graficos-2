#pragma once

#include "Renderer.h"
#include "glm/glm.hpp"

#include "Entity.h"

#include "DDLExport.h"

class Camera
{

protected:

	glm::vec3 cameraPos;
	glm::vec3 cameraFront;
	glm::vec3 cameraUp;
	glm::vec3 cameraRight;

	float Yaw;
	float Pitch;
	float Roll;

	void updateCameraVectors();

public:

	DllExport Camera() ;
	DllExport ~Camera();

	DllExport void thirdPersonCamera(glm::vec3 target, float radiusCameraOrbit);
		
	DllExport void cameraRotationX(float rotationValue);
	DllExport void cameraRotationY(float rotationValue);
	DllExport void cameraRotationZ(float rotationValue);

	DllExport glm::vec3 getCameraPositon();
};

