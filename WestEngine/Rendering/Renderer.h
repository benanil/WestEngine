#pragma once
#include "Common.h"
#include "Camera.h"
#include <MeshRenderer.h>
#include "Shader.h"
#include "Texture.h"

namespace WestEngine
{
	struct MaterialProperty
	{	
		const char* name;
		unsigned int location;
		float* value; // maximum 16 because of mat4
		GLenum type;
		MaterialProperty() : name("sadlynull"), location(0), type(0) {}
		MaterialProperty(const char* _name, unsigned int _id, GLenum _type)
			: name(_name), location(_id), type(_type) {}
	};

	class Material
	{
		MaterialProperty* properties;
		unsigned short propertyCount;
		Texture* textures;
	public:
		// index in the renderers array
		// you don't need to use it other than renderer 
		unsigned char index;
	public:
		Material(Shader* shader, Texture* _textures);
		void ShowProperties();
		
		void SetProperty(const char* name, void* value, const char& size);
		void SetProperty(const unsigned short& index, const void* value, const char& size);
		unsigned short GetPropertyIndex(const char* name) const;

		void UploadAllProperties() const;
		Shader* shader;
	};

	struct MaterialPair
	{
		Material* material;
		unsigned short indexCount;
		unsigned short indexes[1024]; // index of mesh renderers in renderer class

		void AddIndex(const unsigned short& index) {
			indexes[indexCount++] = index;
		}

		void RemoveAt(const short& index)
		{
			indexCount--;
			indexes[index] = indexes[indexCount];
			indexes[indexCount] = 0; // set old index to 0 its not necesary but however
		}
	};

	class MeshRenderer;
	class ComputeShader;
	class FrameBuffer;
	
	class Renderer
	{
		MeshRenderer* renderers[2048];
		unsigned short rendererCount;
		/// <summary> mesh indexes and materials </summary>
		MaterialPair materialPair[32];
		int materialCount;
		static ComputeShader* PostCompute;
		static FrameBuffer* PostFrameBuffer;

		inline short GetRendererIndex(const MeshRenderer* renderer);
	public:
		void AddMeshRenderer(MeshRenderer* renderer, Material* material);
		void Render(const Camera& camera);
		void RemoveMeshRenderer(const MeshRenderer* renderer);
		static void Initialize();
		static void Invalidate(const int* width, const int* height);
		/// <summary> dispose all of the mesh renderers
		/// use it when scene cleared</summary>
	    void ClearRenderers();

		static Renderer& Get()
		{
			static Renderer renderer;
			return renderer;
		}
	};
}