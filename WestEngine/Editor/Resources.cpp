#include "Editor.h"
#include "Common.h"
#include <filesystem>
#include "AssetManager.h"

namespace WestEngine
{
	void ResourcesWindow::Initialize()
	{
	
	}

	void ResourcesWindow::DrawWindow()
	{
		static unsigned int fileIcon   = Texture::CreateIcon("file.png");
		static unsigned int folderIcon = Texture::CreateIcon("folder.png");
		static unsigned int meshIcon   = Texture::CreateIcon("mesh.png");
		
		ImGui::Begin("Resources");
		
		auto path = Helper::AssetsPath();

		ImGui::Separator();
		for (auto& directory : std::filesystem::directory_iterator(path))
		{
			const char* fileName = directory.path().filename().u8string().c_str();

			if (directory.is_directory()) {
				ImGui::BeginGroup();
				GUI::ImageButton(folderIcon);
				ImGui::Text(fileName);
				ImGui::EndGroup();
			}
			else  
			{ // file
				ImGui::BeginGroup();
				GUI::ImageButton(fileIcon);
				ImGui::Text(fileName);
				ImGui::EndGroup();
			}
			ImGui::SameLine();
		}

		ImGui::End();
	}
}