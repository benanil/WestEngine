
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
		unsigned int* indices;
		
		unsigned int indexCount;
		unsigned int vertexCount;
		unsigned int vao, vbo, ebo;
		
		Mesh(const aiMesh& aimesh);

		void Invalidate();
		void Draw()	const;
	};

	class MeshLoader
	{
	public:
		static Mesh* Load(const std::string& path, int&  meshCount);
	};
}




