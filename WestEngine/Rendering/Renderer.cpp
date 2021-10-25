#include "Common.h"
#include "Renderer.h"
#include "spdlog/spdlog.h"

namespace WestEngine
{

	void Renderer::Render(const Camera& camera)
	{
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT); 

		for (char i = 0; i < materialCount; i++)
		{
			auto pair = materialPair[i];
			pair.material->shader->Bind();
			pair.material->UploadAllProperties();
			
			pair.material->shader->setMat4("projection", camera.GetProjectionMatrix());
			pair.material->shader->setMat4("view", camera.GetViewMatrix());
			pair.material->shader->setVec3("viewPos", camera.Position);

			for (unsigned short j = 0; j < pair.indexCount; j++)
			{
				renderers[pair.indexes[j]]->OnRender(false);
			}
		}

		Shader::Unbind();
	}


	void Renderer::AddMeshRenderer(MeshRenderer* renderer, Material* material)
	{
		short rendererindex = GetRendererIndex(renderer);
	
		if (rendererindex == -1)
		{
			materialPair[materialCount].AddIndex(rendererCount);
			materialPair[materialCount++].material = material;
			renderers[rendererCount++] = renderer;
			spdlog::error("material added");
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