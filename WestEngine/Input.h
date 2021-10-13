#pragma once
#include "GLFW/glfw3.h"

namespace WestEngine
{
	class Input
	{
		static GLFWwindow* window;
	public:
		static void Initialize(GLFWwindow* _window);
		static const bool GetKey(const int key);
		static const bool GetKeyDown(const int key);
		static const bool GetKeyUp(const int key);
	};
}
