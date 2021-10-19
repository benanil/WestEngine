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
	class Shader
	{
	private:
		std::unordered_map<std::string, int> map;
		std::string ReadAllText(std::string filePath) const;
	public:
		volatile unsigned int shaderProgram;
		
		Shader(const std::string& vertexPath, const std::string& fragmentPath);

		void Bind() const { glUseProgram(shaderProgram); }

		// utility uniform functions
		void setBool(const std::string& name, bool value) const;
		void setInt(const std::string& name, const int& value) const;
		void setFloat(const std::string& name, const float& value) const;
		void setVec2(const std::string& name, glm::vec2& value) const;
		void setVec2(const std::string& name, const float& x, const float& y) const;
		void setVec3(const std::string& name, const glm::vec3& value) const;
		void setVec3(const std::string& name, const float& x, const float& y, const float& z) const;
		void setVec4(const std::string& name, const float& x, const float& y, const float& z, const float& w) const;
		void setVec4(const std::string& name, const glm::vec4& value) const;
		void setMat2(const std::string& name, const glm::mat2& mat) const;
		void setMat3(const std::string& name, const glm::mat3& mat) const;
		void setMat4(const std::string& name, const glm::mat4& mat) const;
	};
}
