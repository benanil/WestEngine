
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
	class Mesh
	{
	public:
		aiVector3D* positions;
		aiVector3D* normals;
		aiVector2D* texCoords;
		uint* indices;
		
		uint indexCount;
		uint vertexCount;
		
		uint vao, vbo, ebo;
		uint texID, normalID;
		
		Mesh(const aiMesh& aimesh)
		{
			indexCount = aimesh.mNumFaces * 3;
			vertexCount = aimesh.mNumVertices;
			
			// copy indices from aimesh's faces
			uint* indices = (uint*)malloc(sizeof(uint) * aimesh.mNumFaces * 3);
			for (uint i = 0; i < aimesh.mNumFaces; i ++) {
				const aiFace& face = aimesh.mFaces[i];
				memcpy(&indices[i * 3], face.mIndices, sizeof(uint) * 3);
			}

			// allocate vertices 
			positions = (aiVector3D*)malloc(sizeof(aiVector3D) * aimesh.mNumVertices);
			normals   = (aiVector3D*)malloc(sizeof(aiVector3D) * aimesh.mNumVertices);
			texCoords = (aiVector2D*)malloc(sizeof(aiVector2D) * aimesh.mNumVertices);

			// copy vertices from aimesh
			memcpy(positions, aimesh.mVertices, sizeof(aiVector3D) * aimesh.mNumVertices);
			memcpy(normals  , aimesh.mNormals , sizeof(aiVector3D) * aimesh.mNumVertices);
			
			for (uint i = 0; i < aimesh.mNumVertices; i++) {
				memcpy(&texCoords[i], &aimesh.mTextureCoords[0][i], sizeof(aiVector2D));
			}

			Invalidate();
		}

		void Invalidate() {
			glGenVertexArrays(1, &vao);
			glBindVertexArray(vao);
		
			glGenBuffers(1, &vbo);
			glBindBuffer(GL_ARRAY_BUFFER, vbo);
			glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec3) * vertexCount, positions, GL_STATIC_DRAW);
			glVertexAttribPointer(0, 3, GL_FLOAT, GL_TRUE, sizeof(glm::vec3), 0);
			glEnableVertexAttribArray(0);

			glGenBuffers(1, &texID);
			glBindBuffer(GL_ARRAY_BUFFER, texID);
			glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec2) * vertexCount, texCoords, GL_STATIC_DRAW);
			glVertexAttribPointer(1, 2, GL_FLOAT, GL_TRUE, sizeof(glm::vec2), 0);
			glEnableVertexAttribArray(1);

			glGenBuffers(1, &normalID);
			glBindBuffer(GL_ARRAY_BUFFER, normalID);
			glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec3) * vertexCount, normals, GL_STATIC_DRAW);
			glVertexAttribPointer(1, 3, GL_FLOAT, GL_TRUE, sizeof(glm::vec3), 0);
			glEnableVertexAttribArray(2);

			glGenBuffers(1, &ebo);
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
			glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(uint) * indexCount, indices, GL_STATIC_DRAW);
			
			glBindVertexArray(0);
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
			glBindBuffer(GL_ARRAY_BUFFER, 0);
			glBindVertexArray(0);
		}

		void Draw()	{
			glBindVertexArray(vao);
			glEnableVertexAttribArray(0);
			glEnableVertexAttribArray(1);
			glEnableVertexAttribArray(2);
			glDrawElements(GL_TRIANGLES, indexCount, GL_UNSIGNED_INT, indices);
			glDisableVertexAttribArray(0);
			glDisableVertexAttribArray(1);
			glDisableVertexAttribArray(2);
			glBindVertexArray(0);
			glUseProgram(0);
		}
	};
}




