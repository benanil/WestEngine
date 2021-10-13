#pragma once

#include "glad.h"
#include <iostream>
#include <string>
#include <iostream>
#include <unordered_map>
#include <filesystem>
#include "glm/glm.hpp"

namespace WestEngine
{
	class Shader
	{
	private:
		std::unordered_map<std::string, int> map;
	public:
		volatile unsigned int shaderProgram;
		
		Shader(const std::string& vertexPath, const std::string& fragmentPath);

		void Bind() const { glUseProgram(shaderProgram); }

		// utility uniform functions
		void setBool(const std::string& name, bool value)          { glUniform1i(map[name], (int)value); }
		void setInt(const std::string& name, const int& value)     { glUniform1i(map[name], value); }
		void setFloat(const std::string& name, const float& value) { glUniform1f(map[name], value); }
		void setVec2(const std::string& name, glm::vec2& value)    { glUniform2fv(map[name], 1, &value[0]); }
		void setVec2(const std::string& name, const float& x, const float& y) { glUniform2f(map[name], x, y); }
		void setVec3(const std::string& name, const glm::vec3& value        ) { glUniform3fv(map[name], 1, &value[0]); }
		void setVec3(const std::string& name, const float& x, const float& y, const float& z) { glUniform3f(map[name], x, y, z); }
		void setVec4(const std::string& name, const float& x, const float& y, const float& z, const float& w) { glUniform4f(map[name], x, y, z, w); }
		void setVec4(const std::string& name, const glm::vec4& value) { glUniform4fv(map[name], 1, &value[0]); }
		void setMat2(const std::string& name, const glm::mat2& mat)   { glUniformMatrix2fv(map[name], 1, GL_FALSE, &mat[0][0]); }
		void setMat3(const std::string& name, const glm::mat3& mat)   { glUniformMatrix3fv(map[name], 1, GL_FALSE, &mat[0][0]); }
		void setMat4(const std::string& name, const glm::mat4& mat)   { glUniformMatrix4fv(map[name], 1, GL_FALSE, &mat[0][0]); }

		static const char* ReadAllText(const std::string& filePath) ;
	};
}
