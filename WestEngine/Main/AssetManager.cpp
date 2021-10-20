#include "AssetManager.h"

namespace WestEngine
{
	void AssetManager::AddTexture(Texture* texture) { textures.push_back(texture); }
	void AssetManager::AddMesh(Mesh* mesh) { meshes.push_back(mesh); }

	Texture* AssetManager::GetTexture(const std::string& path, bool generateMipMap)
	{
		// search in assets
		for (auto& texture : textures) 
		{
			if (texture->path == path)
			{
				return texture;
			}
		}
		// texture is not exist create new one
		textures.push_back(new Texture(generateMipMap, path.c_str()));
		return textures.back();
	}

	/// <summary> gets mesh if its not exist creates new one </summary>
	/// <param name="path"> this could be identifier: path + :name </param>
	Mesh* AssetManager::GetMesh(const std::string& path)
	{
		// search in assets
		for (auto& mesh : meshes)
		{
			if (mesh->path == path)
			{
				return mesh;
			}
		}

		// mesh is not exist create new one
		int count = 0;
		Mesh* mesh =  MeshLoader::Load(path, count);

		for (unsigned short i = 0; i < count; i++) {
			meshes.push_back(mesh + i);
		}

		return GetMesh(path);
	}
	
	Shader* AssetManager::GetShader(const std::string& vertexPath, const std::string& fragmentPath)
	{
		for (auto& shader : shaders)
		{
			if (shader->vertexPath == vertexPath && shader->fragmentPath == fragmentPath)
			{
				return shader;
			}
		}

		Shader* shader = new Shader(vertexPath, fragmentPath);
		shaders.push_back(shader);
		return shader;
	}
}