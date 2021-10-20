#include "MeshRenderer.h"

namespace WestEngine
{
	MeshRenderer::MeshRenderer(const Entity* entity, const Mesh* _mesh, int _meshCount, 
		Material* _material, bool _singleMaterial) : Companent(entity), mesh(mesh), 
		meshCount(_meshCount), material(_material)
	{
		Renderer::AddMeshRenderer(this, material);
	}

	void MeshRenderer::OnRender(bool shadowPass = false) const {
		
		material->shader->setMat4("model", entity->transform->matrix);

		for (unsigned short i = 0; i < meshCount; i++)
		{
			mesh[i].Draw();
		}
	}

	void MeshRenderer::OnImgui()
	{
		// draw drag and drop material, mesh, texture
		// draw material properties
		if (ImGui::CollapsingHeader("MeshRenderer"))
		{
			ImGui::Text("Mesh Name");
			ImGui::SameLine();
			ImGui::Text(mesh->name.c_str());
			material->ShowProperties();
		}
	}
	
	void MeshRenderer::OnValidate() { }
	
	void MeshRenderer::Update(const float& dt) { }
	void MeshRenderer::Start() { }
}
