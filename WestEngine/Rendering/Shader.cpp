#include "Shader.h"
#include <fstream>
#include "spdlog/spdlog.h"
#include <stdio.h>
#include <sys/stat.h>
#include <GLFW/glfw3.h>
#include <sys/stat.h>
#include "Helper.h"

namespace WestEngine
{
	namespace fs = std::filesystem;

	Shader::Shader(const std::string& vertexPath, const std::string& fragmentPath)
	{
		std::cout << Helper::AssetsPath().append(vertexPath) << std::endl;
		std::cout << Helper::AssetsPath().append(fragmentPath) << std::endl;
	
		// Read shaders
		std::string vertexShaderSource   = ReadAllText(Helper::AssetsPath().append(vertexPath).u8string());
		std::string fragmentShaderSource = ReadAllText(Helper::AssetsPath().append(fragmentPath).u8string());
	
		spdlog::warn("vertex shader\n {0}"  , vertexShaderSource  );
		spdlog::warn("fragment shader\n {0}", fragmentShaderSource);
	
		const char* anan = vertexShaderSource.c_str();
		const char* anan1 = fragmentShaderSource.c_str();

		unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
		glShaderSource(vertexShader, 1, &anan, NULL);
		glCompileShader(vertexShader);
	
		int success;
		char infoLog[512];
		glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
		if (!success)
		{
			glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
			std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
		}
		// fragment shader
		unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
		glShaderSource(fragmentShader, 1, &anan1, NULL);
		glCompileShader(fragmentShader);
		// check for shader compile errors
		glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
		if (!success)
		{
			glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
			std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
		}
		// link shaders
		shaderProgram = glCreateProgram();
		glAttachShader(shaderProgram, vertexShader);
		glAttachShader(shaderProgram, fragmentShader);
		glLinkProgram(shaderProgram);
		// check for linking errors
		glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
		if (!success) {
			glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
			std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
		}
		glDeleteShader(vertexShader);
		glDeleteShader(fragmentShader);
		int activeUniforms = 0;
		glGetProgramiv(shaderProgram, GL_ACTIVE_UNIFORMS, &activeUniforms);
		
		map = std::unordered_map<std::string, int>();
		map.reserve(activeUniforms);
		for (int i = 0; i < activeUniforms; i++) {
			char buffer[64];

			GLsizei uniform_length = 0;
			GLint	uniform_size = 0;
			GLenum	uniform_type = 0;
			glGetActiveUniform(shaderProgram, (GLuint)i, (GLsizei)sizeof(buffer), &uniform_length, &uniform_size, &uniform_type, buffer);
			std::string name(buffer, uniform_length);
			std::cout << "uniform " << name << std::endl;
			map.insert({ name, glGetUniformLocation(shaderProgram, name.c_str()) });
		}
	}

	// utility uniform functions
	void Shader::setBool(const std::string& name, bool value) const { glUniform1i(map[name], (int)value); }
	void Shader::setInt(const std::string& name, const int& value) const { glUniform1i(map[name], value); }
	void Shader::setFloat(const std::string& name, const float& value) const { glUniform1f(map[name], value); }
	void Shader::setVec2(const std::string& name, glm::vec2& value) const { glUniform2fv(map[name], 1, &value[0]); }
	void Shader::setVec2(const std::string& name, const float& x, const float& y) const { glUniform2f(map[name], x, y); }
	void Shader::setVec3(const std::string& name, const glm::vec3& value) const  { glUniform3fv(map[name], 1, &value[0]); }
	void Shader::setVec3(const std::string& name, const float& x, const float& y, const float& z) const { glUniform3f(map[name], x, y, z); }
	void Shader::setVec4(const std::string& name, const float& x, const float& y, const float& z, const float& w) const { glUniform4f(map[name], x, y, z, w); }
	void Shader::setVec4(const std::string& name, const glm::vec4& value) const { glUniform4fv(map[name], 1, &value[0]); }
	void Shader::setMat2(const std::string& name, const glm::mat2& mat) const { glUniformMatrix2fv(map[name], 1, GL_FALSE, &mat[0][0]); }
	void Shader::setMat3(const std::string& name, const glm::mat3& mat) const { glUniformMatrix3fv(map[name], 1, GL_FALSE, &mat[0][0]); }
	void Shader::setMat4(const std::string& name, const glm::mat4& mat) const { glUniformMatrix4fv(map[name], 1, GL_FALSE, &mat[0][0]);  }

    std::string Shader::ReadAllText(std::string filePath) const {
		
		if (!fs::exists(filePath)) {
			spdlog::warn("file is not exist! {0} ", filePath);
		}

		std::ifstream f(filePath, std::ios::in | std::ios::binary | std::ios::failbit);
		const auto sz = fs::file_size(filePath);
		std::string result(sz, '\0');
		f.read(result.data(), sz);

		return result.c_str();
	}
}