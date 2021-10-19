#pragma once
#include "Common.h"
#include "Companent.h"
#include "Mesh.h"
#include <Entity.h>

namespace WestEngine
{
	class MeshRenderer : public Companent 
	{
		Entity* entity;
		Mesh* mesh;
		int meshCount;
	public:
		MeshRenderer(const Entity& entity, const Mesh* mesh, int meshCount);
		void OnRender() const;
	};
}

