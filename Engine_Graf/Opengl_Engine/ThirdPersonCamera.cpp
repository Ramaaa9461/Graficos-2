#include "ThirdPersonCamera.h"


ThirdPersonCamera::ThirdPersonCamera()
{

}

ThirdPersonCamera::~ThirdPersonCamera()
{

}

void ThirdPersonCamera::rotateThirdPersonCamera(bool rotWithCursor, float sensitivityX, float sensitivityY, int keyRotLeft, int keyRotRight, int keyRotForward, int keyRotBack)
{
	if (rotWithCursor)
	{
		glfwSetInputMode(Window::getWindow()->getNativeWindow(), GLFW_CURSOR, GLFW_CURSOR_DISABLED);
		glm::vec2 mousePosition = Input::getMousePosition() * Timer::getTimer()->timeBetweenFrames();

		cameraRotationX(mousePosition.x * (sensitivityX / 10));
		cameraRotationY(mousePosition.y * (sensitivityY / 10));
	}
	else
	{
		if (Input::getKeyPressed(keyRotLeft))
		{
			cameraRotationX(-sensitivityX);
		}
		else if (Input::getKeyPressed(keyRotRight))
		{
			cameraRotationX(sensitivityX);
		}
		else if (Input::getKeyPressed(keyRotForward))
		{
			cameraRotationY(-sensitivityY);
		}
		else if (Input::getKeyPressed(keyRotBack))
		{
			cameraRotationY(sensitivityY);
		}
	}
}

void ThirdPersonCamera::updateThirdPersonCamera(glm::vec3 target)
{
	radiusCameraOrbit += Input::getScrollInput() * Timer::getTimer()->timeBetweenFrames();

	if (radiusCameraOrbit < 8.0f)
	{
		radiusCameraOrbit = 8.1f;
	}
	else if (radiusCameraOrbit > 100.0f)
	{
		radiusCameraOrbit = 99.9f;
	}


	cameraPos = target + cameraFront * radiusCameraOrbit;

	Renderer::getRenderer()->view = glm::lookAt(cameraPos, target, cameraUp);
}
