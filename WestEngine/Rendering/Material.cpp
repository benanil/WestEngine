#include "Renderer.h"
#include "imgui/imgui.h"

namespace WestEngine
{
	Material::Material(Shader* _shader, Texture* _textures) : shader(shader), textures(_textures)
	{
		properties = (MaterialProperty*)malloc(sizeof(Material) * shader->map.size());
		propertyCount = shader->map.size();
		
		unsigned short i = 0;

		for (auto iter = shader->map.begin();
			iter != shader->map.end(); iter++) 
		{
			properties[i].name   = iter->first.c_str();
			properties[i].id     = iter->second.id;
			properties[i++].type = iter->second.type;
		}
	}
	
	void Material::ShowProperties()  {
		using namespace glm;

		for (unsigned short i = 0; i < propertyCount; i++)
		{
			const MaterialProperty& prop = properties[i];
			if      (prop.type == GL_FLOAT)      ImGui::DragFloat (prop.name, (float*)prop.value, 0.1f);
			else if (prop.type == GL_FLOAT_VEC2) ImGui::DragFloat2(prop.name, (float*)prop.value, 0.1f);
			else if (prop.type == GL_FLOAT_VEC3) ImGui::DragFloat3(prop.name, (float*)prop.value, 0.1f);
			else if (prop.type == GL_FLOAT_VEC4) ImGui::ColorEdit4(prop.name, (float*)prop.value, 0.1f);
			else if (prop.type == GL_SAMPLER_2D) GUI::TextureField(prop.name, &textures);
		}
	}

	// upload changed value to shader
	void Material::UploadAllProperties() const
	{
		for (unsigned short i = 0; i < propertyCount; i++)
		{
			const MaterialProperty& prop = properties[i];
			
			if (prop.type == GL_FLOAT)		 shader->setFloat(prop.name, (float*)prop.value);
			else if (prop.type == GL_FLOAT_VEC2) shader->setVec2(prop.name, (float*)prop.value);
			else if (prop.type == GL_FLOAT_VEC3) shader->setVec3(prop.name, (float*)prop.value);
			else if (prop.type == GL_FLOAT_VEC4) shader->setVec4(prop.name, (float*)prop.value);
			else if (prop.type == GL_SAMPLER_2D) shader->setInt (prop.name, textures[0].texID);
		}
	}
}