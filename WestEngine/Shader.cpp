#include "Shader.h"

namespace WestEngine
{
	Shader::Shader(const std::string& vertexPath, const std::string& fragmentPath)
	{
		std::cout << std::filesystem::current_path().parent_path().append(vertexPath) << std::endl;
		std::cout << std::filesystem::current_path().parent_path().append(fragmentPath) << std::endl;
	
		// Read shaders
		const char* vertexShaderSource = ReadAllText(std::filesystem::current_path().parent_path().append(vertexPath).u8string());
		const char* fragmentShaderSource = ReadAllText(std::filesystem::current_path().parent_path().append(fragmentPath).u8string());
	
		std::cout << "vertex shader\n" << vertexShaderSource << std::endl;
		std::cout << "fragment shader\n" << fragmentShaderSource << std::endl;
	
		unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
		glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
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
		glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
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
		int uniformSize = 0;
		glGetProgramiv(shaderProgram, GL_UNIFORM_SIZE, &uniformSize);
		
		map = std::unordered_map<std::string, int>();
		map.reserve(uniformSize);
		for (int i = 0; i < uniformSize; i++) {
			char buffer[32];

			GLsizei uniform_length = 0;
			GLint	uniform_size = 0;
			GLenum	uniform_type = 0;
			glGetActiveUniform(shaderProgram, (GLuint)i, (GLsizei)sizeof(buffer), &uniform_length, &uniform_size, &uniform_type, buffer);
			std::string name(buffer, uniformSize);
			std::cout << "uniform" << name << buffer << std::endl;
			map.insert({ name, glGetUniformLocation(shaderProgram, name.c_str()) });
		}
	}

    const char* Shader::ReadAllText(const std::string& filePath)  {
		char* fcontent = NULL;
		int fsize = 0;
		FILE* fp;

		fp = fopen(filePath.c_str(), "r");
		if (fp) {
			fseek(fp, 0, SEEK_END);
			fsize = ftell(fp);
			rewind(fp);

			fcontent = (char*)malloc(sizeof(char) * fsize);
			fread(fcontent, 1, fsize, fp);

			fclose(fp);
		}
		return fcontent;
	}
}