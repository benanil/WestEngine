#pragma once
#include "Common.h"
#include "Mesh.h"
#include "Entity.h"
#include "Component.h"
#include <Renderer.h>

namespace WestEngine
{
	class Material;

	class MeshRenderer : public Companent 
	{
		Mesh* mesh;
		Material* material;
		int meshCount;
	public:
		~MeshRenderer();
		MeshRenderer(const Entity* entity, Mesh* _mesh, int meshCount,
					Material* material, bool singleMaterial);
		void OnRender(bool shadowPass = false) const;
		void Update(const float& dt) override;
		void Start() override;
		void Save() override;
		void Load() override;
		void OnValidate() override;
		void OnImgui() override;
	};
}

