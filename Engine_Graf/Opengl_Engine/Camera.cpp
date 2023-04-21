#include "Camera.h"

#include "Timer.h"


DllExport Camera::Camera()
{
	cameraPos = glm::vec3(0.0f, 0.0f, 10.0f);
	cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);
	cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);

	Yaw = -90.0f;
	Pitch = 0.0f;
	Roll = 0.0f;

	updateCameraVectors();
}

DllExport Camera::~Camera()
{

}

void Camera::cameraRotationX(float rotationValue )
{
	Yaw += rotationValue;

	if (this->Yaw > 360.0f || this->Yaw < -360.0f)
		this->Yaw = 0.0f;

	updateCameraVectors();
}

void Camera::cameraRotationZ(float rotationValue )
{
	Roll += rotationValue;

	if (this->Roll > 360.0f || this->Roll < -360.0f)
		this->Roll = 0.0f;

	updateCameraVectors();
}

void Camera::cameraRotationY(float rotationValue)
{
	Pitch += -rotationValue;

	if (this->Pitch > 360.0f || this->Pitch < -360.0f)
		this->Pitch = 0.0f;

	updateCameraVectors();
}

void Camera::updateCameraVectors()
{
	// calculate the new Front vector
	glm::vec3 front;
	front.x = cos(glm::radians(Yaw)) * cos(glm::radians(Pitch));
	front.y = sin(glm::radians(Pitch));
	front.z = sin(glm::radians(Yaw)) * cos(glm::radians(Pitch));

	cameraFront = glm::normalize(front);

	glm::mat4 roll_mat = glm::rotate(glm::mat4(1.0f), glm::radians(Roll), front);
	cameraUp = glm::normalize(glm::mat3(roll_mat) * cameraUp);

	cameraRight = glm::normalize(glm::cross(cameraFront, cameraUp));  // normalize the vectors, because their length gets closer to 0 the more you look up or down which results in slower movement.


}

DllExport glm::vec3 Camera::getCameraPositon()
{
	return cameraPos;
}



