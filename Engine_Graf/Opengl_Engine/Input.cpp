#include "Input.h"
#include "Window.h"


double Input::xScroll = 0;
double Input::yScroll = 0;

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

DllExport float Input::getScrollImpl()
{
	Window* window = Window::getWindow();
	int scale_factor = 20;

	static double scroll_yoffset = 0.0;

	glfwSetScrollCallback(window->getNativeWindow(), [](GLFWwindow* window, double xoffset, double yoffset)
	{
		scroll_yoffset = yoffset;
	});

	if (scroll_yoffset == 0.0)
	{
		return 0.0;
	}
	else
	{
		double input = scroll_yoffset * scale_factor;
		scroll_yoffset = 0.0;
		return -input;
	}
}
