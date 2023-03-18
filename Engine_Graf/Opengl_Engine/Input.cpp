#include "Input.h"
#include "Window.h"



DllExport bool Input::IsKeyPressedImpl(int keycode)
{
	auto state = glfwGetKey(Window::getWindow()->getNativeWindow(), keycode);

	return (state == GLFW_PRESS || state == GLFW_REPEAT);
}

DllExport bool Input::IsMouseButtonPressedImpl(int button)
{
	auto state = glfwGetMouseButton(Window::getWindow()->getNativeWindow(), button);

	return state == GLFW_PRESS;
}

DllExport float  Input::GetMouseXImpl()
{
	glm::vec2 position = getMousePositionImpl();
	return position.x;
}

DllExport float  Input::GetMouseYImpl()
{
	glm::vec2 position = getMousePositionImpl();
	return position.y;
}

DllExport glm::vec2 Input::getMousePositionImpl()
{
	double xPos, yPos;
	Window* window = Window::getWindow();
	glfwGetCursorPos(window->getNativeWindow(), &xPos, &yPos);

	return glm::vec2((float)xPos, (float)yPos - window->GetScreenHeight());
}
