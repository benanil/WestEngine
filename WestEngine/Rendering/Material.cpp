#include "Renderer.h"
#include "imgui/imgui.h"

namespace WestEngine
{
	Material::Material(Shader* shader)
	{
		properties = (MaterialProperty*)malloc(sizeof(Material) * shader->map.size());
		propertyCount = shader->map.size();
		unsigned short i = 0;

		for (auto iter = shader->map.begin();
			iter != shader->map.end(); iter++) 
		{
			properties[i].name   = iter->first;
			properties[i].id     = iter->second.id;
			properties[i++].type = iter->second.type;
		}
	}
	
	template<typename T>
	void Material::SetProperty(const string& name, const T& value)
	{
		using namespace glm;
		for (unsigned short i = 0; i < )
		{
			if (properties[i].name == name)
			{
				if (float val = dynamic_cast<float>(value))    glUniform1f(properties[i].id, val);
				else if (vec2 val = dynamic_cast<vec2>(value)) glUniform2f(properties[i].id, val.x, val.y);
				else if (vec3 val = dynamic_cast<vec3>(value)) glUniform3f(properties[i].id, val.x, val.y, val.z);
				else if (vec4 val = dynamic_cast<vec4>(value)) glUniform4f(properties[i].id, val.x, val.y, val.z, val.w);
				else if (mat4 val = dynamic_cast<mat4>(value)) glUniformMatrix4fv(properties[i].id, 1, GL_FALSE, &val[0][0]);
			}
		}
	}

	void Material::ShowProperties() const {
		using namespace glm;

		for (unsigned short i = 0; i < propertyCount; i++)
		{
			const MaterialProperty& prop = properties[i];

			if (prop.type == GL_FLOAT && ImGui::DragFloat(prop.name.c_str(), (float*)prop.value)) UploadValue(i);
			else if (prop.type == GL_FLOAT_VEC2) ImGui::DragFloat2(prop.name.c_str(), (float*)prop.value);
			else if (prop.type == GL_FLOAT_VEC3) ImGui::DragFloat3(prop.name.c_str(), (float*)prop.value);
			else if (prop.type == GL_FLOAT_VEC4) ImGui::ColorEdit4(prop.name.c_str(), (float*)prop.value);
		}
	}

	// upload changed value to shader
	void Material::UploadValue(int index) const 
	{
		// if (prop.type == GL_FLOAT) shader->setFloat(properties[index].name, );
		// else if (prop.type == GL_FLOAT_VEC2);
		// else if (prop.type == GL_FLOAT_VEC3);
		// else if (prop.type == GL_FLOAT_VEC4);
	}
}