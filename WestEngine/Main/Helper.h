#pragma once
#include <iostream>
#include <filesystem>

namespace WestEngine
{
	class Helper
	{	
	public:
		static std::filesystem::path AssetsPath();
		static bool Contains(const char* compValue, const char** strings, const unsigned char& count);
		static bool Contains(const std::string& compValue, const std::string* strings, const unsigned char& count);
		static std::string ReadAllText(const std::string& filePath);
		static void SkipBOM(std::ifstream& in);
	};
}