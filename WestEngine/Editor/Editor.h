#pragma once
#include "imgui/backends/imgui_impl_glfw.h"
#include "imgui/backends/imgui_impl_opengl3.h"
#include "Event.h"
#include "Texture.h"
#include "Camera.h"
#include "Texture.h"
#include <iostream>
#include <functional>

typedef void(*FileCallback)(const char* ptr);

namespace WestEngine
{
	constexpr float filesize = 35;
	constexpr float miniSize = 12.5f;

	struct TitleAndAction
	{
		const char* title;
		Action action;
		TitleAndAction() : title("empty title"), action(nullptr) {}
		TitleAndAction(const char* _title, Action _action) : title(_title), action(_action) {}
	};

	class Editor
	{
	public:
		
		static void Create(GLFWwindow* window);
		static void AddOnEditor(const Action& action);
		static void Begin();
		static void Render();
		static void HalfLifeTheme();
		static void DarkTheme();
		static void Destroy();
	};

	class GUI
	{
	public:
		static void Header(const char* title);
		static void TextureField(const char* name, WestEngine::Texture** texture);
		static void TextureField(const char* name, const int& texture);
		static bool ImageButton(const unsigned int& texture, const float& size = filesize);

		static void EnumField(int& value, const char** names, const int& count, const char* label,
							  const Action& onSellect = NULL, const ImGuiComboFlags& flags = 0);

		static void RightClickPopUp(const char* name, const TitleAndAction* menuItems, const int& count);

		static bool DragUIElementString(const char* file, const char* type, const unsigned int& texture);
		static void DropUIElementString(const char* type, const FileCallback& callback);
		
		template<typename T>
		static bool DragUIElement(const char* file, const T& type, const unsigned int& texture);
		template<typename T>
		static void DropUIElement(const char* type, const std::function<T>& callback);
	};

	class ResourcesWindow
	{	
		// static Texture* fileIcon;
		// static Texture* folderIcon;
		// static Texture* meshIcon;
	public:
		static std::filesystem::path currentPath;
		static void Initialize();
		static void DrawWindow();
	};

	class SettingsWindow
	{
	public:

		static void DrawWindow(Camera& camera);
	};
}