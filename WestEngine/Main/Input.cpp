
#include "Input.h"
#include "Device.h"

namespace WestEngine
{
	
	
	
	vec2 Input::_MousePosition = Math::vec2(0.0f, 0.0f);
	static float lastX = 0, lastY = 0;

	GLFWwindow* Input::window = NULL;

	void Input::Initialize(GLFWwindow* _window) {
		window = _window;
		double tempX, tempY;
		glfwGetCursorPos(window, &tempX, &tempY);
		_MousePosition.x = tempX;
		_MousePosition.y = tempY;
	}

	void Input::MouseCallback(GLFWwindow* _window, double xpos, double ypos)
	{
		_MousePosition.x = xpos;
		_MousePosition.y = ypos;
	}

	const bool Input::GetKey(const int key) {
		return glfwGetKey(window, key) == GLFW_PRESS;
	}

    const bool Input::GetKeyDown(const int key) {
		return glfwGetKey(window, key) != GLFW_PRESS 
			&& glfwGetKey(window, key) != GLFW_RELEASE;
	}

	const bool Input::GetKeyUp(const int key){
		return glfwGetKey(window, GLFW_RELEASE);
	}

	const bool Input::GetMouseButtonRelease(const bool key)
	{
		return glfwGetMouseButton(window, key) == GLFW_RELEASE;
	}

	const bool Input::GetMouseButtonPress(const bool key)
	{
		return glfwGetMouseButton(window, key) == GLFW_PRESS;
	}

	void Input::InfiniteMouse()
	{
		POINT point;
		GetCursorPos(&point);
		const Math::vec2 monitorScale = Device::GetMonitorScale();

		if (point.x > monitorScale.x - 2) { _SetCursorPos(2, point.y); }
		if (point.y > monitorScale.y - 2) { _SetCursorPos(point.x, 2); }
		if (point.x < 2) { _SetCursorPos(monitorScale.x - 3, point.y); }
		if (point.y < 2) { _SetCursorPos(point.x, monitorScale.y - 3); }
	}

	void Input::_SetCursorPos(const int& x, const int& y) {
		SetCursorPos(x, y);
		glfwSetCursorPos(window, x, y);
	}

	const POINT& Input::GeMouseRaw()
	{
		POINT point;
		GetCursorPos(&point);
		return point;
	}

	const Math::vec2& Input::MousePos() { return _MousePosition; }
}

