#include "MeshRenderer.h"
#include "imgui/imgui.h"
#include "spdlog/spdlog.h"

namespace WestEngine
{
	MeshRenderer::~MeshRenderer()
	{
		RETURNIF(disposed)
		OnRemoved();
		Renderer::Get().RemoveMeshRenderer(this);
		disposed = true;
	}

	MeshRenderer::MeshRenderer(const Entity* entity, Mesh* _mesh, int _meshCount, 
		Material* _material, bool _singleMaterial) : Companent(entity, "Mesh Renderer"), mesh(_mesh),
		meshCount(_meshCount), material(_material)
	{
		spdlog::error("constructor of the mesh renderer");
		Renderer::Get().AddMeshRenderer(this, material);
	}

	void MeshRenderer::OnRender(bool shadowPass) const {
		
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
			ImGui::Text("First Mesh"); // ImGui::Text(mesh->name.c_str());
			material->ShowProperties();
		}
	}
	
	void MeshRenderer::OnValidate() { }
	void MeshRenderer::Save() {}
	void MeshRenderer::Load() {}

	void MeshRenderer::Update(const float& dt) { }
	void MeshRenderer::Start() { }
}
