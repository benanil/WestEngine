
#include "Input.h"

namespace WestEngine
{
	GLFWwindow* Input::window = NULL;

	void Input::Initialize(GLFWwindow* _window) {
		window = _window;
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
}

