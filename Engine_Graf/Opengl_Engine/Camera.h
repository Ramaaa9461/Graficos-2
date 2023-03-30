#pragma once

#include "Renderer.h"
#include "glm/glm.hpp"

#include "Entity.h"
#include "Input.h"

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
	float Roll;

	float cameraSpeed;


	void updateCameraVectors();

public:

	DllExport Camera() ;
	DllExport ~Camera();


	DllExport void firstPersonCamera();
	DllExport void thirdPersonCamera(glm::vec3 target, glm::vec3 offsetCamera);
	
	DllExport void followCursor(glm::vec2 mousePosition, float mouseSensitivityX, float mouseSensitivityY);
	
	DllExport void cameraRotationX(float rotationValue, float sensitivity);
	DllExport void cameraRotationY(float rotationValue, float sensitivity);
	DllExport void cameraRotationZ(float rotationValue, float sensitivity);


	DllExport void moveForward();
	DllExport void moveBack();
	DllExport void moveRight();
	DllExport void moveLeft();

};

