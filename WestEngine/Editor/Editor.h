#pragma once
#include "imgui/backends/imgui_impl_glfw.h"
#include "imgui/backends/imgui_impl_opengl3.h"
#include "Event.h"

namespace WestEngine::Editor
{
	static void Create(GLFWwindow* window);
	static void AddOnEditor(const Action& action);
	static void Begin();
	static void Render();
	static void HalfLifeTheme();
	static void DarkTheme();
	static void Destroy();
}