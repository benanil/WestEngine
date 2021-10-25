#include "AssetManager.h"

namespace WestEngine
{
	void AssetManager::_AddTexture(Texture* texture) { textures.push_back(texture); }
	void AssetManager::_AddMesh(Mesh* mesh) { meshes.push_back(mesh); }

	Texture* AssetManager::_GetTexture(const std::string& path, bool generateMipMap)
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
	Mesh* AssetManager::_GetMesh(const std::string& identifier)
	{
		// search in assets
		for (auto& mesh : meshes)
		{
			char* otherID = mesh->GetIdentifier();
			
			if (identifier.compare(otherID) == 0) {
				delete otherID;
				return mesh;
			}

			delete otherID; // we need to delete identifier otherwise memory leak
		}

		// mesh is not exist create new one
		unsigned short count = 0;
		Mesh* mesh =  MeshLoader::Load(identifier, count);

		for (unsigned short i = 0; i < count; i++) {
			meshes.push_back(mesh + i); // registers to list for future usages
		}

		return GetMesh(identifier);
	}
	
	Mesh* AssetManager::_GetBase(const std::string& path, unsigned short& size)
	{
		Mesh* mesh = MeshLoader::Load(path, size);

		for (unsigned short i = 0; i < size; i++) {
			meshes.push_back(mesh + i); // registers to list for future usages
		}

		return mesh;
	}

	Shader* AssetManager::_GetShader(const std::string& vertexPath, const std::string& fragmentPath)
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