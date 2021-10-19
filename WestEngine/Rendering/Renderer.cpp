#include "glad.h"
#include "Common.h"
#include "Renderer.h"
#include "Camera.h"

namespace WestEngine
{
	void Renderer::Render(const Camera& camera)
	{
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT); // also clear the depth buffer now!

        // activate shader
        shader.Bind();
        // bind textures on corresponding texture units
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, texture.texID);

        shader.setMat4("projection", camera.GetProjectionMatrix()); // note: currently we set the projection matrix each frame, but since the projection matrix rarely changes it's often best practice to set it outside the main loop only once.
        shader.setMat4("view", camera.GetViewMatrix());
        shader.setFloat("sunAngle", glm::radians(sunAngle));
        shader.setVec3("viewPos", camera.Position);
        
        shader.setFloat("metallic", Engine::properties.metalic);
        shader.setFloat("roughness", Engine::properties.roughness);
        shader.setFloat("specValue", Engine::properties.specValue);
        shader.setVec3("sunColor", Engine::properties.sunColor);
        shader.setVec3("ambientColor", Engine::properties.ambientColor);
        shader.setFloat("ambientStrength", Engine::properties.ambientStrength);

        for (uint i = 0; i < meshCount; i++) mesh[i].Draw();

        glUseProgram(0);
	}
}