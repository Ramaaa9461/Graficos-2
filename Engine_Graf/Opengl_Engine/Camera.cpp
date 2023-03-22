#include "Camera.h"


DllExport Camera::Camera()
{
	//cameraPos = glm::vec3(0.0f, 0.0f, -10.0f);
	//cameraTarget = glm::vec3(0.0f, 0.0f, 0.0f);
	//cameraDirection = glm::normalize(cameraPos - cameraTarget);

	//glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f);

	//cameraRight = glm::normalize(glm::cross(up, cameraDirection));
	//cameraUp = glm::cross(cameraDirection, cameraRight);

	cameraPos = glm::vec3(0.0f, 0.0f, 3.0f);
	cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);
	cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
	cameraWorldUp = cameraUp;

	cameraSpeed = 2.5f;
	MouseSensitivity = 0.1f;
	Zoom = 45.0f;
	Yaw = -90.0f;
	Pitch = 0.0f;

	updateCameraVectors();
}

DllExport Camera::~Camera()
{

}

DllExport void Camera::firstPersonCamera()
{
	Renderer::getRenderer()->view = glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);
}

DllExport void Camera::thirdPersonCamera(glm::vec3 target)
{
	const float radius = 10.0f;
	float camX = sin(glfwGetTime()) * radius;
	float camZ = cos(glfwGetTime()) * radius;

	cameraPos.x = camX;
	cameraPos.z = camZ;

	Renderer::getRenderer()->view = glm::lookAt(cameraPos, target, cameraUp);
}

DllExport void Camera::moveForward()
{
	cameraPos += cameraSpeed * cameraFront;
}

DllExport void Camera::moveBack()
{
	cameraPos -= cameraSpeed * cameraFront;
}

DllExport void Camera::moveRight()
{
	cameraPos += glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
}

DllExport void Camera::moveLeft()
{
	cameraPos -= glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
}


void Camera::updateCameraVectors()
{
	// calculate the new Front vector
	glm::vec3 front;
	front.x = cos(glm::radians(Yaw)) * cos(glm::radians(Pitch));
	front.y = sin(glm::radians(Pitch));
	front.z = sin(glm::radians(Yaw)) * cos(glm::radians(Pitch));
	cameraFront = glm::normalize(front);
	// also re-calculate the Right and Up vector
	cameraRight = glm::normalize(glm::cross(cameraFront, cameraWorldUp));  // normalize the vectors, because their length gets closer to 0 the more you look up or down which results in slower movement.
	cameraUp = glm::normalize(glm::cross(cameraRight, cameraFront));
}
