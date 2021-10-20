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
	
		static const Texture* GetTexture(const std::string& path, bool generateMipMap);
		static const Mesh* GetMesh(const std::string& path);
	};
}

