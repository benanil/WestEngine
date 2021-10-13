#pragma once
#include "imgui/backends/imgui_impl_glfw.h"
#include "imgui/backends/imgui_impl_opengl3.h"

namespace WestEngine
{
	class Editor
	{
	public:
		static void HalfLifeTheme();
		static void DarkTheme();
		static void Create(GLFWwindow* window);
		static void Begin();
		static void Render();
		static void Destroy();
	};
}