#include "Editor.h"
#include "Common.h"
#include <filesystem>
#include "AssetManager.h"
#include "spdlog/spdlog.h"

namespace WestEngine
{
	void Click();

	void ResourcesWindow::Initialize()
	{
	
	}

	void ResourcesWindow::DrawWindow()
	{
		static unsigned int fileIcon   = Texture::CreateIcon("file.png");
		static unsigned int folderIcon = Texture::CreateIcon("folder.png");
		static unsigned int meshIcon   = Texture::CreateIcon("mesh.png");
		
		ImGui::Begin("Resources");
		
		// todo: make path static & add oppen close folders & back button & dragg and drop
		auto path = Helper::AssetsPath();
		int id = 0; // for imgui push id

		ImGui::Separator();
		
		for (auto& directory : std::filesystem::directory_iterator(path))
		{
			std::string fileName = directory.path().filename().u8string();

			if (directory.is_directory()) {
				ImGui::PushID(id++);

				ImGui::BeginGroup();
				if (GUI::ImageButton(folderIcon))
				{
					spdlog::info("clicked {0}", fileName);
				}
				ImGui::TextWrapped(fileName.c_str());
				ImGui::EndGroup();
				if (ImGui::IsItemHovered())
				{
					ImGui::BeginTooltip();
					ImGui::Text(fileName.c_str());
					ImGui::EndTooltip();
				}
				
				ImGui::PopID();
			}

			ImGui::SameLine();
		}

		for (auto& directory : std::filesystem::directory_iterator(path))
		{
			std::string fileName = directory.path().filename().u8string();

			if (!directory.is_directory()) {
				ImGui::PushID(id++);

				ImGui::BeginGroup();
				if (GUI::ImageButton(fileIcon)) {
					spdlog::info("clicked {0}", fileName);
				}
				ImGui::TextWrapped(fileName.c_str());
				ImGui::EndGroup();

				if (ImGui::IsItemHovered())
				{
					ImGui::BeginTooltip();
					ImGui::Text(fileName.c_str());
					ImGui::EndTooltip();
				}

				ImGui::PopID();
			}
			ImGui::SameLine();
		}

		ImGui::End();
	}

	void Click()
	{
		std::cout << "right click pressed !" << std::endl;
	}
}