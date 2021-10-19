#include "AssetManager.h"

namespace WestEngine
{
	void AssetManager::AddTexture(Texture* texture) { textures.push_back(texture); }
	void AssetManager::AddMesh(Mesh* mesh) { meshes.push_back(mesh); }
}