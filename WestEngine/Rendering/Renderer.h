#pragma once
#include "Common.h"
#include "Renderer.h"
#include <list>
#include <vector>

namespace WestEngine
{
	struct MaterialProperty
	{	
		std::string name;
		unsigned int id;
		void* value;
		GLenum type;
		MaterialProperty() : name("sadlynull"), id(0), type(0) {}
		MaterialProperty(string _name, unsigned int _id, GLenum _type)
			: name(_name), id(_id), type(_type) {}
	};

	class Material
	{
		MaterialProperty* properties;
		unsigned short propertyCount;
		unsigned char* container;
	public:
		Material(Shader* shader);
		template<typename T>
		void SetProperty(const string& name, const T& value);
		void ShowProperties() const;
		void UploadValue(int index) const;
		Shader* shader;
	};

	class Renderer
	{
		std::list<Mesh> meshes;
	public:
		static void Render();
	};
}