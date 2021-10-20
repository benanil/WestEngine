#pragma once

#include "glad.h"
#include <iostream>
#include <string>
#include <iostream>
#include <unordered_map>
#include <filesystem>
#include "glm/glm.hpp"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>"

namespace WestEngine
{
	struct UniformData
	{	
		unsigned int id;
		GLenum type;
		UniformData() : id(0), type(0) {}
	};

	class Shader
	{
	private:
		std::string ReadAllText(std::string filePath) const;
	public:
		volatile unsigned int shaderProgram;
		std::unordered_map<std::string, UniformData> map;
		std::string vertexPath, fragmentPath;
	public:
		Shader(const std::string& vertexPath, const std::string& fragmentPath);
		void Bind() const { glUseProgram(shaderProgram); }
		// utility uniform functions
		void setBool(const std::string& name, bool value) ;
		void setInt (const std::string& name, const int& value) ;
		void setVec2(const std::string& name, const glm::vec2& value) ;
		void setVec3(const std::string& name, const glm::vec3& value);
		void setVec2(const std::string& name, const float& x, const float& y) ;
		void setVec3(const std::string& name, const float& x, const float& y, const float& z) ;
		void setVec4(const std::string& name, const float& x, const float& y, const float& z, const float& w) ;
		void setVec4(const std::string& name, const glm::vec4& value) ;
		void setMat2(const std::string& name, const glm::mat2& mat);
		void setMat3(const std::string& name, const glm::mat3& mat);
		void setMat4(const std::string& name, const glm::mat4& mat);

		void setFloat(const std::string& name, const float* value);
		void setVec2 (const std::string& name, const float* value);
		void setVec3 (const std::string& name, const float* value);
		void setVec4 (const std::string& name, const float* value);
		void setMat4 (const std::string& name, const float* value);
	};
}
