#pragma once
#include "Common.h"
#include "Mesh.h"
#include <ECS.h>
#include <Renderer.h>

namespace WestEngine
{
	class MeshRenderer : public Companent 
	{
		Mesh* mesh;
		Material* material;
		int meshCount;
	public:
		MeshRenderer(const Entity* entity, const Mesh* mesh, int meshCount, Material* material, bool singleMaterial);
		void OnRender(bool shadowPass = false) const;
		void Update(const float& dt) override;
		void Start() override;
		void Save() override;
		void Load() override;
		void OnValidate() override;
		void OnImgui() override;
	};
}

