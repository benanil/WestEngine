#include "Mesh.h"
#include <iostream>
#include <filesystem>
#include <spdlog/spdlog.h>

namespace WestEngine
{
	Mesh* MeshLoader::Load(const std::string& path, unsigned short& meshCount)
	{
		Assimp::Importer importer;

		const aiScene* scene = importer.ReadFile(Helper::AssetsPath().append(path).u8string(), aiProcessPreset_TargetRealtime_MaxQuality | aiProcess_FlipUVs);

		spdlog::info("Mesh load");

		// If the import failed, report it
		if (scene == nullptr) {
			printf(importer.GetErrorString());
			assert(1);
		}

		spdlog::info("Mesh load1");

		meshCount = scene->mNumMeshes;
		Mesh* result = (Mesh*)malloc(sizeof(Mesh) * scene->mNumMeshes);

		for (unsigned short i = 0; i < scene->mNumMeshes; i++)
		{
			result[i] = Mesh(scene->mMeshes[i], path);
		}
		
		spdlog::info("Mesh load2");

		importer.FreeScene();

		return result;
	}

	Mesh::Mesh(const aiMesh* aimesh, const std::string& _path) 
		: path(_path.c_str()), name(aimesh->mName.C_Str())
	{
		spdlog::info("constructor start");

		indexCount = aimesh->mNumFaces * 3;
		vertexCount = aimesh->mNumVertices;

		// copy indices from aimesh's faces
		indices = (unsigned int*)malloc(sizeof(unsigned int) * aimesh->mNumFaces * 3);
		for (unsigned int i = 0; i < aimesh->mNumFaces; i++) {
		
			indices[i * 3 + 0] = aimesh->mFaces[i].mIndices[0];
			indices[i * 3 + 1] = aimesh->mFaces[i].mIndices[1];
			indices[i * 3 + 2] = aimesh->mFaces[i].mIndices[2];
		}

		vertices = (Vertex*)malloc(sizeof(Vertex) * vertexCount);

		for (unsigned int i = 0; i < vertexCount; i++) {
			vertices[i].position = aimesh->mVertices[i];
			vertices[i].normal   = aimesh->mNormals[i];
			vertices[i].texCoord.x = aimesh->mTextureCoords[0][i].x;
			vertices[i].texCoord.y = aimesh->mTextureCoords[0][i].y;
			vertices[i].tangent = aimesh->mTangents[i];
		}

		Invalidate();
	}

	char* Mesh::GetIdentifier()
	{
		char* identifier = (char*)malloc(strlen(path) + strlen(name)); // create new string for identifier
		memcpy(identifier, path, strlen(path));
		memcpy(identifier + strlen(path), name, strlen(name)); // means identifier = path + name  
		return identifier; 
	}

	void Mesh::Invalidate() {
		vao = 0;  vbo = 0;
		ebo = 0;
	
		glGenVertexArrays(1, &vao);
		glGenBuffers(1, &vbo);
		glGenBuffers(1, &ebo);
	
		glBindVertexArray(vao);
	
		glBindBuffer(GL_ARRAY_BUFFER, vbo);
		glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * vertexCount, vertices, GL_STATIC_DRAW);
	
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const void*)0);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_TRUE , sizeof(Vertex), (const void*)12);
		glVertexAttribPointer(2, 2, GL_FLOAT, GL_TRUE , sizeof(Vertex), (const void*)24); // 24 = 6 float 
		glVertexAttribPointer(3, 3, GL_FLOAT, GL_TRUE , sizeof(Vertex), (const void*)32);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * indexCount, indices, GL_STATIC_DRAW);
	
		glBindVertexArray(0);
		area = CalculateArea();
	}

	Math::Box3 Mesh::CalculateArea()
	{
		
		
		
		vec3 min = Math::vec3(Math::minf, Math::minf, Math::minf);
		Math::vec3 max = Math::vec3(Math::maxf, Math::maxf, Math::maxf);

		for (unsigned int i = 0; i < vertexCount; i++)  {
			if (vertices[i].position.x > max.x) max.x = vertices[i].position.x;
			if (vertices[i].position.y > max.y) max.y = vertices[i].position.y;
			if (vertices[i].position.x < min.x) min.x = vertices[i].position.x;
			if (vertices[i].position.y < min.y) min.y = vertices[i].position.y;
		}

		return Math::Box3(min, max);
	}

	void Mesh::Draw() const {
		glBindVertexArray(vao);
		
		glEnableVertexAttribArray(0);
		glEnableVertexAttribArray(1);
		glEnableVertexAttribArray(2);
		glEnableVertexAttribArray(3);
		
		glDrawElements(GL_TRIANGLES, indexCount, GL_UNSIGNED_INT, (void*)0);
		
		glDisableVertexAttribArray(0);
		glDisableVertexAttribArray(1);
		glDisableVertexAttribArray(2);
		glDisableVertexAttribArray(3);

		glBindVertexArray(0);
	}
}