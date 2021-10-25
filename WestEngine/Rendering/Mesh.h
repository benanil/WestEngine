
#pragma once

#include "Common.h"
#include "assimp/vector2.h"
#include "assimp/vector3.h"

#include <assimp/Importer.hpp>  
#include <assimp/scene.h>       
#include <assimp/postprocess.h> 

#include <iostream>
#include <Box.h>
#include <memory>

namespace WestEngine
{
	struct Vertex
	{
		aiVector3D position;
		aiVector3D normal;
		aiVector2D texCoord;
		aiVector3D tangent;
	};

	class Mesh
	{
	public:
		Vertex* vertices;
		const char* path;
		const char* name;
		Math::Box3 area;

		unsigned int* indices;
		
		unsigned int indexCount;
		unsigned int vertexCount;
		unsigned int vao, vbo, ebo;
		
		Mesh(Vertex* _vertices, unsigned int* _indices, int _vertexCount, int _indexCount)
			: vertices(_vertices), indices(_indices), vertexCount(_vertexCount), indexCount(_indexCount) {
			Invalidate();
		}

		Mesh(const aiMesh* aimesh, const std::string& path);

		char* GetIdentifier();

		void Invalidate();
		void Draw()	const;
		Math::Box3 CalculateArea();
	};

	class MeshLoader
	{
	public:
		static Mesh* Load(const std::string& path, unsigned short& meshCount);
	};
}




