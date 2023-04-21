#include "firstPersonCamera.h"



FirstPersonCamera::FirstPersonCamera(float cameraSpeed, int keyForward,
int keyBack, int keyLeft, int keyRight, int keyUp, int keyDown )
{
	this->cameraSpeed = cameraSpeed;
	
	this->keyForward = keyForward;
	this->keyBack = keyBack;
	this->keyLeft = keyLeft;
	this->keyRight= keyRight;
	this->keyUp   = keyUp;
	this->keyDown = keyDown;

}

FirstPersonCamera::~FirstPersonCamera()
{
}

void FirstPersonCamera::rotateFirstPersonCamera(bool rotWithCursor, float sensitivityX, float sensitivityY, int keyRotLeft, int keyRotRight, int keyRotForward, int keyRotBack)
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
		else if(Input::getKeyPressed(keyRotRight))
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

void FirstPersonCamera::updateFirstPersonCamera()
{
	moveForward();
	moveBack();
	moveUp();
	moveDown();
	moveRight();
	moveLeft();

	Renderer::getRenderer()->view = glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);
}

DllExport void FirstPersonCamera::moveForward()
{
	if (Input::getKeyPressed(keyForward))
	{
		cameraPos += cameraSpeed * cameraFront * Timer::getTimer()->timeBetweenFrames();
	}
}

DllExport void FirstPersonCamera::moveBack()
{
	if (Input::getKeyPressed(keyBack))
	{
		cameraPos -= cameraSpeed * cameraFront * Timer::getTimer()->timeBetweenFrames();
	}
}

DllExport void FirstPersonCamera::moveUp()
{
	if (Input::getKeyPressed(keyUp))
	{
		cameraPos += cameraSpeed * cameraUp * Timer::getTimer()->timeBetweenFrames();
	}
}

DllExport void FirstPersonCamera::moveDown()
{
	if (Input::getKeyPressed(keyDown))
	{
		cameraPos -= cameraSpeed * cameraUp * Timer::getTimer()->timeBetweenFrames();
	}
}

DllExport void FirstPersonCamera::moveRight()
{
	if (Input::getKeyPressed(keyRight))
	{
		cameraPos += glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed * Timer::getTimer()->timeBetweenFrames();
	}
}

DllExport void FirstPersonCamera::moveLeft()
{
	if (Input::getKeyPressed(keyLeft))
	{
		cameraPos -= glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed * Timer::getTimer()->timeBetweenFrames();
	}
}
