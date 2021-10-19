#include "Mesh.h"
#include <iostream>
#include <filesystem>
#include <spdlog/spdlog.h>
#include <vector>

namespace WestEngine
{
	Mesh* MeshLoader::Load(const std::string& path, int& meshCount)
	{
		Assimp::Importer importer;

		const aiScene* scene = importer.ReadFile(path, aiProcessPreset_TargetRealtime_MaxQuality | aiProcess_FlipUVs);

		// If the import failed, report it
		if (scene == nullptr) {
			printf(importer.GetErrorString());
			assert(1);
		}

		meshCount = scene->mNumMeshes;
		Mesh* result = (Mesh*)malloc(sizeof(Mesh) * scene->mNumMeshes);

		for (uint i = 0; i < scene->mNumMeshes; i++) result[i] = Mesh(*scene->mMeshes[i]);
		
		importer.FreeScene();

		return result;
	}

	Mesh::Mesh(const aiMesh& aimesh)
	{
		indexCount = aimesh.mNumFaces * 3;
		vertexCount = aimesh.mNumVertices;

		// copy indices from aimesh's faces
		indices = (uint*)malloc(sizeof(uint) * aimesh.mNumFaces * 3);
		for (uint i = 0; i < aimesh.mNumFaces; i++) {
		
			indices[i * 3 + 0] = aimesh.mFaces[i].mIndices[0];
			indices[i * 3 + 1] = aimesh.mFaces[i].mIndices[1];
			indices[i * 3 + 2] = aimesh.mFaces[i].mIndices[2];
		}

		vertices = (Vertex*)malloc(sizeof(Vertex) * vertexCount);

		for (unsigned int i = 0; i < vertexCount; i++) {
			vertices[i].position = aimesh.mVertices[i];
			vertices[i].normal   = aimesh.mNormals[i];
			vertices[i].texCoord.x = aimesh.mTextureCoords[0][i].x;
			vertices[i].texCoord.y = aimesh.mTextureCoords[0][i].y;
			vertices[i].tangent = aimesh.mTangents[i];
		}

		Invalidate();
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
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(uint) * indexCount, indices, GL_STATIC_DRAW);
	
		glBindVertexArray(0);
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