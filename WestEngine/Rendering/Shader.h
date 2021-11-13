#pragma once

#include "Common.h"
#include <iostream>
#include <string>
#include <iostream>
#include <unordered_map>
#include <filesystem>

namespace WestEngine
{
	struct UniformData
	{	
		/// <summary> uniform location </summary>
		unsigned int id;
		GLenum type; // GL_FLOAT etc.
		UniformData() : id(0), type(0) {}
	};

	class Shader
	{
	public:
		volatile unsigned int shaderProgram;
		std::unordered_map<std::string, UniformData> map;
		std::string vertexPath, fragmentPath;
	public:
		Shader(const std::string& vertexPath, const std::string& fragmentPath);
		void Bind() const  { glUseProgram(shaderProgram); }
		inline static void Unbind() { glUseProgram(0); };
		// utility uniform functions
		void setBool(const std::string& name, bool value) ;
		void setInt (const std::string& name, const int& value) ;
		void setVec2(const std::string& name, const 
			
			
		void setVec3(const std::string& name, const Math::vec3& value);
		void setVec2(const std::string& name, const float& x, const float& y) ;
		void setVec3(const std::string& name, const float& x, const float& y, const float& z) ;
		void setVec4(const std::string& name, const float& x, const float& y, const float& z, const float& w) ;
		void setVec4(const std::string& name, const Math::vec4& value) ;
		void setMat2(const std::string& name, const Math::mat2& mat);
		void setMat3(const std::string& name, const Math::mat3& mat);
		void setMat4(const std::string& name, const Math::mat4& mat);

		void setFloat(const std::string& name, const float* value);
		void setVec2 (const std::string& name, const float* value);
		void setVec3 (const std::string& name, const float* value);
		void setVec4 (const std::string& name, const float* value);
		void setMat4 (const std::string& name, const float* value);
	};
}
