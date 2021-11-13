#pragma once
#include "Common.h"

namespace WestEngine
{
	class ComputeShader
	{
		unsigned int width, height;
		unsigned int programID;
		unsigned int texture;
		std::string path;
	public:
		ComputeShader(const std::string& path);
		void Invalidate(const int* width, const int* height);
		void Dispatch() const;
		void Bind() const { glUseProgram(programID); };
		const unsigned int& GetTexture() const { return texture;   };
		const unsigned int& GetProgram() const { return programID; };
	};
}

