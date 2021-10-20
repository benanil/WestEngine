#pragma once
#include "imgui/backends/imgui_impl_glfw.h"
#include "imgui/backends/imgui_impl_opengl3.h"
#include "Event.h"
#include "Texture.h"

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

namespace WestEngine::GUI
{
	constexpr float filesize = 35;
	constexpr float miniSize = 12.5f;

	static void Header(const char* title);
	static void TextureField(const char* name, Texture** texture);
}