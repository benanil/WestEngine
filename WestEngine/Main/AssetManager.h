#pragma once
#include <Texture.h>
#include <Mesh.h>

namespace WestEngine
{
	class AssetManager abstract
	{
		static std::list<Texture*> textures;
		static std::list<Mesh*> meshes;
	public:
		static void AddTexture(Texture* texture);
		static void AddMesh(Mesh* mesh);
	};
}

