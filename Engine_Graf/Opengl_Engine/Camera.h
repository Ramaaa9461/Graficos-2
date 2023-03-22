#pragma once

#include "Renderer.h"
#include "glm/glm.hpp"

#include "DDLExport.h"

class Camera
{

private:

	glm::vec3 cameraPos;
	glm::vec3 cameraFront;
	glm::vec3 cameraUp;
	glm::vec3 cameraRight;

	glm::vec3 cameraWorldUp;

	glm::vec3 cameraTarget;
	glm::vec3 cameraDirection;

	float Yaw;
	float Pitch;

	float cameraSpeed;
	float MouseSensitivity;
	float Zoom;


	void updateCameraVectors();

public:

	DllExport Camera() ;
	DllExport ~Camera();


	DllExport void firstPersonCamera();
	DllExport void thirdPersonCamera(glm::vec3 target);
	
	
	DllExport void moveForward();
	DllExport void moveBack();
	DllExport void moveRight();
	DllExport void moveLeft();


};

