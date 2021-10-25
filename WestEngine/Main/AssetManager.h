#pragma once
#include <Texture.h>
#include <Mesh.h>
#include <Shader.h>
#include <list>

namespace WestEngine
{
	class AssetManager
	{
		std::list<Texture*> textures;
		std::list<Mesh*> meshes;
		std::list<Shader*> shaders;
		void _AddTexture(Texture* texture);
		void _AddMesh(Mesh* mesh);
		Texture* _GetTexture(const std::string& path, bool generateMipMap);
		Mesh* _GetMesh(const std::string& path);
		Shader* _GetShader(const std::string& vertexPath, const std::string& fragmentPath);
		Mesh* _GetBase(const std::string& path, unsigned short& size);
	public:
		static void AddTexture(Texture* texture) { Get()._AddTexture(texture); };
		static void AddMesh(Mesh* mesh) { Get()._AddMesh(mesh); };
		static Texture* GetTexture(const std::string& path, bool generateMipMap) { return Get()._GetTexture(path, generateMipMap); };
		static Mesh* GetMesh(const std::string& path) { return Get()._GetMesh(path); };
		
		/// <summary> gets mesh array and sub mesh size
		///			  this would be usefull when loading mesh in editor </summary>
		static Mesh* GetMeshBase(const std::string& path, unsigned short& size) { return Get()._GetBase(path, size); };
		
		static Shader* GetShader(const std::string& vertexPath, const std::string& fragmentPath) { return Get()._GetShader(vertexPath, fragmentPath); };
		
		static AssetManager& Get()
		{
			static AssetManager instance;
			return instance;
		}
	};
}

