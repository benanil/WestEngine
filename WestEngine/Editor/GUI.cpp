#include "Editor.h"

namespace WestEngine::GUI
{
	void Header(const char* title)
	{
		
	}

	void TextureField(const char* name, Texture** texture)
	{
		ImGui::Image((void*)(*texture)->texID, { filesize, filesize }, { 0, 1 }, { 1, 0 });
		// ImGui::AcceptDragDropPayload("Texture");
	}
}