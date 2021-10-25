#include "Editor.h"
#include "GLFW/glfw3.h"

namespace WestEngine
{
	void SettingsWindow::DrawWindow(Camera& camera)
	{
		ImGui::Begin("Settings");

		ImGui::DragFloat("Camera Speed", &camera.MovementSpeed, .1f);
		ImGui::DragFloat("Camera Senstivity", &camera.MouseSensitivity, .1f);

		static bool vsync = true;

		if (ImGui::RadioButton("Vsync", vsync))
		{
			vsync = !vsync;
			glfwSwapInterval(vsync);
		}

		ImGui::End();
	}
}