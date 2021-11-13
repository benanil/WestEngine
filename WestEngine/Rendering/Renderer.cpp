#include "Common.h"
#include "Renderer.h"
#include "spdlog/spdlog.h"
#include "ComputeShader.h"
#include "FrameBuffer.h"

namespace WestEngine
{
	ComputeShader* Renderer::PostCompute = NULL; 
	FrameBuffer* Renderer::PostFrameBuffer = NULL; 

	void Renderer::Initialize()
	{
		PostCompute = new ComputeShader("PostProcessing.glsl");
		PostFrameBuffer = new FrameBuffer(1440, 900);
	}

	void Renderer::Render(const Camera& camera)
	{
		const static Shader* screen = new Shader("Screen.vert", "Screen.frag");

		glClearColor(0.48f, 0.78f, 0.88f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT); 

		glEnable(GL_DEPTH_TEST);
		// PostFrameBuffer->Bind();

		for (char i = 0; i < materialCount; i++)
		{
			auto pair = materialPair[i];
			pair.material->shader->Bind();
			pair.material->UploadAllProperties();
			
			pair.material->shader->setMat4("projection", camera.GetProjectionMatrix());
			pair.material->shader->setMat4("view"      , camera.GetViewMatrix());
			pair.material->shader->setVec3("viewPos"   , camera.Position);

			for (unsigned short j = 0; j < pair.indexCount; j++)
			{
				renderers[pair.indexes[j]]->OnRender(false);
			}
		}

		// FrameBuffer::UnBind();
		// 
		// glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
		// 
		// PostCompute->Bind();
		// 
		// glBindImageTexture(1, PostFrameBuffer->GetTexture(), 0, false, 0, GL_READ_ONLY, GL_RGBA16F);
		// PostCompute->Dispatch();
		// 
		// glDisable(GL_DEPTH_TEST);
		// screen->Bind();
		// 
		// glActiveTexture(GL_TEXTURE0);
		// glBindTexture(GL_TEXTURE_2D, PostCompute->GetTexture());
		// glDrawArrays(GL_TRIANGLES, 0, 3);
		// glBindTexture(GL_TEXTURE_2D, 0);
		Shader::Unbind();
	}

	void Renderer::Invalidate(const int* width, const int* height)
	{
		PostCompute->Invalidate(width, height);
		PostFrameBuffer->Invalidate(width, height);
	}

	void Renderer::AddMeshRenderer(MeshRenderer* renderer, Material* material)
	{
		short rendererindex = GetRendererIndex(renderer);
	
		if (rendererindex == -1)
		{
			materialPair[materialCount].AddIndex(rendererCount);
			materialPair[materialCount++].material = material;
			renderers[rendererCount++] = renderer;
		}
		else
		{
			materialPair[material->index].AddIndex(rendererindex);
		}
	}

	void Renderer::ClearRenderers()
	{
		memset(renderers, 0, sizeof(MeshRenderer*) * rendererCount);
		rendererCount = 0;

		// remove/detach indexes
		for (char i = 0; i < materialCount; i++)
		{
			memset(materialPair[i].indexes, 0, sizeof(unsigned short) * materialPair[i].indexCount);
			materialPair[i].indexCount = 0;
		}
	}

	/// <summary> removes and destroys the mesh renderer
	/// this will be used for editor only most of the time </summary>
	void Renderer::RemoveMeshRenderer(const MeshRenderer* renderer)
	{
		short removedIndex = GetRendererIndex(renderer);
		
		if (removedIndex == -1)
		{
			spdlog::error("tryin remove meshrenderer but it is not exist!");
			return;
		}

		rendererCount--;
		
		renderers[removedIndex]->~MeshRenderer();
		
		delete renderers[removedIndex]; // delete the mesh renderer

		renderers[rendererCount] = nullptr; // dangling pointer thing
		renderers[removedIndex] = renderers[rendererCount]; // move last member to removed position
	
		// unregister meshrenderer from material
		for (char i = 0; i < materialCount; i++)
		{
			for (short j = 0; j < materialPair[i].indexCount; j++)
			{
				if (materialPair[i].indexes[j] == removedIndex)
				{
					materialPair[i].RemoveAt(j);
					break;
				}
			}
		}

		// register moved renderer again
		for (char i = 0; i < materialCount; i++)
		{
			for (short j = 0; j < materialPair[i].indexCount; j++)
			{
				if (materialPair[i].indexes[j] == rendererCount)
				{
					materialPair[i].AddIndex(removedIndex);
					break;
				}
			}
		}
	}

	short Renderer::GetRendererIndex(const MeshRenderer* renderer)
	{
		short rendererindex = -1;

		for (short i = 0; i < rendererCount; i++)
		{
			if (renderer == renderers[i])
			{
				return rendererindex = i;
			}
		}

		return rendererindex;
	}
}