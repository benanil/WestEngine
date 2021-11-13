#include "Editor.h"
#include "Common.h"
#include <filesystem>
#include "AssetManager.h"
#include "spdlog/spdlog.h"
#include <vector>
#include <string>

namespace WestEngine
{
	void Click(const char*);

	void ResourcesWindow::Initialize()
	{
	
	}
	
	std::filesystem::path ResourcesWindow::currentPath = Helper::AssetsPath();

	void ResourcesWindow::DrawWindow()
	{
		static unsigned int fileIcon   = Texture::CreateIcon("file.png");
		static unsigned int folderIcon = Texture::CreateIcon("folder.png");
		static unsigned int meshIcon   = Texture::CreateIcon("mesh.png");
		static unsigned int fileBack   = Texture::CreateIcon("fileBack.png");

		ImGui::Begin("Resources");
		
		if (GUI::ImageButton(fileBack, miniSize))
		{
			currentPath = currentPath.parent_path();
		}

		// todo: make path static & add oppen close folders & back button & dragg and drop
		int id = 0; // for imgui push id

		ImGui::Separator();
		
#undef min

		for (auto& directory : std::filesystem::directory_iterator(currentPath))
		{
			std::string fileName = directory.path().filename().u8string();

			if (directory.is_directory()) {
				ImGui::PushID(id++);

				ImGui::BeginGroup();
				if (GUI::ImageButton(folderIcon))
				{
					spdlog::info("clicked {0}", fileName);
					currentPath = directory;
				}
				ImGui::TextWrapped(fileName.substr(0, 
					
					
					min<int>(10, fileName.length())).c_str());
				
				char num_char[5 + sizeof(char)];
				const int width = ImGui::GetColumnWidth();
				std::sprintf(num_char, "%i", width);
				
				ImGui::EndGroup();

				if (ImGui::IsItemHovered())
				{
					ImGui::BeginTooltip();
					ImGui::Text(fileName.c_str());
					ImGui::EndTooltip();
				}
				
				ImGui::PopID();
				
				if (width > filesize * 3) 
				ImGui::SameLine();
			}
		}

		for (auto& directory : std::filesystem::directory_iterator(currentPath))
		{
			std::string fileName = directory.path().filename().u8string();

			if (!directory.is_directory()) {
				ImGui::PushID(id++);

				unsigned int icon = fileIcon;

				std::string extension = directory.path().extension().u8string();

				static const std::string meshExtensions[]
				{
					".blend", ".fbx", "obj"
				};

				if (Helper::Contains(extension, meshExtensions , 3)) icon = meshIcon;

				ImGui::BeginGroup();
				if (GUI::ImageButton(icon)) {
					spdlog::info("clicked {0}", icon);
				}
				
				ImGui::TextWrapped(fileName.substr(0, Math::min<int>(10, fileName.length())).c_str());

				char num_char[5 + sizeof(char)];
				const int width = (int)ImGui::GetColumnWidth();
				std::sprintf(num_char, "%i", width);
				
				ImGui::EndGroup();
				
				GUI::DragUIElementString(fileName.c_str(), extension.c_str(),  icon);

				if (ImGui::IsItemHovered())
				{
					ImGui::BeginTooltip();
					ImGui::Text(fileName.c_str());
					ImGui::EndTooltip();
				}

				ImGui::PopID();
				if (width > filesize * 3)
				ImGui::SameLine();
			}
		}

		ImGui::End();
	}


	void Click(const char* call)
	{
		std::cout << "dropped " << call << std::endl;
	}
}