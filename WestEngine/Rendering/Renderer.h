#pragma once
#include "Common.h"
#include "Renderer.h"
#include "Camera.h"
#include <list>
#include <vector>
#include <MeshRenderer.h>
#include <unordered_map>

namespace WestEngine
{
	struct MaterialProperty
	{	
		const char* name;
		unsigned int id;
		void* value;
		GLenum type;
		MaterialProperty() : name("sadlynull"), id(0), type(0) {}
		MaterialProperty(const char* _name, unsigned int _id, GLenum _type)
			: name(_name), id(_id), type(_type) {}
	};

	class Material
	{
		MaterialProperty* properties;
		unsigned short propertyCount;
		Texture* textures;
	public:
		Material(Shader* shader, Texture* _textures);
		void ShowProperties();
		void UploadAllProperties() const;
		Shader* shader;
	};

	class Renderer
	{
		static std::list<MeshRenderer*> renderers;
		static std::unordered_map<Material*, std::list<MeshRenderer*>> materialPair;
	public:
		static void AddMeshRenderer(MeshRenderer* renderer, Material* material);
		static void Render(const Camera* camera);
	};
}