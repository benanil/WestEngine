#pragma once
#include <Texture.h>
#include <Mesh.h>

namespace WestEngine
{
	class AssetManager abstract
	{
		static std::list<Texture*> textures;
		static std::list<Mesh*> meshes;
		static std::list<Shader*> shaders;
	public:
		static void AddTexture(Texture* texture);
		static void AddMesh(Mesh* mesh);
	
		static Texture* GetTexture(const std::string& path, bool generateMipMap);
		static Mesh* GetMesh(const std::string& path);
		static Shader* GetShader(const std::string& vertexPath, const std::string& fragmentPath);
	};
}

