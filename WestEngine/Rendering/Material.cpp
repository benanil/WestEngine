#include "Renderer.h"
#include "imgui/imgui.h"
#include "spdlog/spdlog.h"
#include "Editor.h"

namespace WestEngine
{
	Material::Material(Shader* _shader, Texture* _textures) : shader(_shader), textures(_textures)
	{
		properties = (MaterialProperty*)malloc(sizeof(Material) * _shader->map.size());
		propertyCount = _shader->map.size();
		
		unsigned short i = 0;

		for (auto iter = _shader->map.begin();
			iter != _shader->map.end(); iter++)
		{
			spdlog::warn(iter->first.c_str());
			properties[i].name     = iter->first.c_str();
			properties[i].location = iter->second.id;
			properties[i].value = (float*)malloc(sizeof(float) * 16);
			glGetUniformfv(_shader->shaderProgram, properties[i].location, properties[i].value);
			properties[i++].type   = iter->second.type;
		}
	}
	
	void Material::ShowProperties()  {
		using namespace glm;

		for (unsigned short i = 0; i < propertyCount; i++)
		{
			const MaterialProperty& prop = properties[i];
			if      (prop.type == GL_FLOAT)      ImGui::DragFloat (prop.name, prop.value, 0.1f);
			else if (prop.type == GL_FLOAT_VEC2) ImGui::DragFloat2(prop.name, prop.value, 0.1f);
			else if (prop.type == GL_FLOAT_VEC3) ImGui::DragFloat3(prop.name, prop.value, 0.1f);
			else if (prop.type == GL_FLOAT_VEC4) ImGui::ColorEdit4(prop.name, prop.value, 0.1f);
			else if (prop.type == GL_SAMPLER_2D) GUI::TextureField(prop.name, &textures);
		}
	}

	// upload changed value to shader
	void Material::UploadAllProperties() const
	{
		for (unsigned short i = 0; i < propertyCount; i++)
		{
			const MaterialProperty& prop = properties[i];
		
			if (prop.type == GL_FLOAT)		     glUniform1fv(prop.location, 1, prop.value);
			else if (prop.type == GL_FLOAT_VEC2) glUniform2fv(prop.location, 1, prop.value);
			else if (prop.type == GL_FLOAT_VEC3) glUniform3fv(prop.location, 1, prop.value);
			else if (prop.type == GL_FLOAT_VEC4) glUniform4fv(prop.location, 1, prop.value);
			else if (prop.type == GL_SAMPLER_2D)
			{
				glUniform1i(prop.location, 0);
				glActiveTexture(GL_TEXTURE0);
				glBindTexture(GL_TEXTURE_2D, textures[0].texID);
			}
		}
	}

	/// <param name="name"> uniform's name</param>
	/// <param name="size"> size in bytes </param>
	void Material::SetProperty(const char* name, void* value, const char& size) {
		SetProperty(GetPropertyIndex(name), value, size);
	}

	void Material::SetProperty(const unsigned short& index, const void* value, const char& size) {
		memcpy(properties[index].value, value, size);
	}
	
	unsigned short Material::GetPropertyIndex(const char* name) const 
	{
		for (unsigned short i = 0; i < propertyCount; i++)
			if (name == properties[i].name) return i;

		spdlog::error("material property index is not exist! {0}", name);
		return -1;
	}
}

