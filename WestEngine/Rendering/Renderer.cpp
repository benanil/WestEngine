#include "glad.h"
#include "Common.h"
#include "Renderer.h"


namespace WestEngine
{
	void Renderer::Render(const Camera* camera)
	{
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT); // also clear the depth buffer now!

		for (auto iter = materialPair.begin(); iter != materialPair.end(); iter++)
		{
			iter->first->shader->Bind();
			iter->first->UploadAllProperties();

			for (auto iter1 = iter->second.begin(); iter1 != iter->second.end(); iter1++)
			{
				(*iter1)->OnRender(true);
			}
		}

		glUseProgram(0);
	}

	void Renderer::AddMeshRenderer(MeshRenderer* renderer, Material* material)
	{
		renderers.push_back(renderer);

		if (materialPair.find(material) == materialPair.end()) // not finded
		{
			auto list = std::list<MeshRenderer*>();
			list.push_back(renderer);
			materialPair.insert({ material , list});
		}
		else
		{
			materialPair[material].push_back(renderer);
		}
	}

}