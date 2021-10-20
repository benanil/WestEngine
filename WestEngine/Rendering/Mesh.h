
#pragma once

#include "Common.h"
#include "glad.h"
#include "assimp/vector2.h"
#include "assimp/vector3.h"

#include <assimp/Importer.hpp>  
#include <assimp/scene.h>       
#include <assimp/postprocess.h> 

#include <iostream>
#include <vector>
#include <Box.h>

namespace WestEngine
{
	struct Vertex
	{
		aiVector3D position;
		aiVector3D normal;
		aiVector2D texCoord;
		aiVector3D tangent;
	};

	struct ShaderProperties
	{
		float roughness;
		float metalic;
		float specValue = 1;
		glm::vec3 sunColor = {1,1,1};
		glm::vec3 ambientColor = { 1,1,1 };
		float ambientStrength = .15f;
	};

	class Mesh
	{
	public:
		Vertex* vertices;
		std::string path;
		std::string name;
		Math::Box3 area;

		unsigned int* indices;
		
		unsigned int indexCount;
		unsigned int vertexCount;
		unsigned int vao, vbo, ebo;
		
		Mesh(Vertex* _vertices, unsigned int* _indices, int _vertexCount, int _indexCount)
			: vertices(_vertices), indices(_indices), vertexCount(_vertexCount), indexCount(_indexCount) {
			Invalidate();
		}

		Mesh(const aiMesh& aimesh, const string& path, const string& name);

		string GetIdentifier() { return path + ':' + name; }

		void Invalidate();
		void Draw()	const;
		Math::Box3 CalculateArea();
	};

	class MeshLoader
	{
	public:
		static Mesh* Load(const std::string& path, int&  meshCount);
	};
}




