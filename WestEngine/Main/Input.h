#pragma once
#include "GLFW/glfw3.h"
#include "glm/glm.hpp"

#include <Windows.h>
#include <WinUser.h>

namespace WestEngine
{
	class Input
	{
		static glm::vec2 _MousePosition;
		static GLFWwindow* window;
		static void _SetCursorPos(const int& x, const int& y);
	public:
		static void MouseCallback(GLFWwindow* window, double xpos, double ypos);
		static void Initialize(GLFWwindow* _window);
		static const bool GetKey(const int key);
		static const bool GetKeyDown(const int key);
		static const bool GetKeyUp(const int key);
		static const bool GetMouseButtonRelease(const bool key);
		static const bool GetMouseButtonPress(const bool key);
		static void InfiniteMouse();
		/// <returns>mouse position that is not relative to glfw</returns>
		static const POINT& GeMouseRaw();
		static const glm::vec2& MousePos();
	};
}
