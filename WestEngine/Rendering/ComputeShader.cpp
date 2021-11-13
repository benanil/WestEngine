#include "ComputeShader.h"
#include "spdlog/spdlog.h"
#include <filesystem>

namespace WestEngine
{
	ComputeShader::ComputeShader(const std::string& path)
	{
		this->path = path;//std::copy(path);

		std::cout << Helper::AssetsPath().append(path) << std::endl;

		// Read shaders
		std::string sourceStr = Helper::ReadAllText(Helper::AssetsPath().append(path).generic_string<char>());

		spdlog::warn("Compute Shader\n {0}", sourceStr);

		const char* source = sourceStr.c_str();

		unsigned int computeShader = glCreateShader(GL_COMPUTE_SHADER);
		glShaderSource(computeShader, 1, &source, NULL);
		glCompileShader(computeShader);

		int success = 0;
		char infoLog[512];
		glGetShaderiv(computeShader, GL_COMPILE_STATUS, &success);
		if (!success) {
			glGetShaderInfoLog(computeShader, 512, NULL, infoLog);
			std::cout << "ERROR::SHADER::Compute::COMPILATION_FAILED\n" << infoLog << std::endl;
		}

		programID = glCreateProgram();
		glAttachShader(programID, computeShader);
		glLinkProgram(programID);
		glDeleteShader(computeShader);
		glDetachShader(programID, computeShader);
		int x = 1440, y = 900;
		Invalidate(&x, &y);
	}

	void ComputeShader::Invalidate(const int* width, const int* height)
	{
		this->width  = (unsigned int)*width;
		this->height = (unsigned int)*height;
		
		glDeleteTextures(1, &texture);
		
		glGenTextures(1, &texture);
		glBindTexture(GL_TEXTURE_2D, texture);
		glTexParameteri(texture, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA16F, this->width, this->height, 0, GL_RGBA, GL_FLOAT, 0);
	}
	
	void ComputeShader::Dispatch() const
	{
		glBindImageTexture(0, texture, 0, GL_FALSE, 0, GL_WRITE_ONLY, GL_RGBA16F);
		glDispatchCompute(width / 8, height / 8, 1);
		glMemoryBarrier(GL_SHADER_IMAGE_ACCESS_BARRIER_BIT);
	}
}