#pragma once
#include <iostream>
#include <filesystem>

namespace WestEngine
{
	class Helper
	{	
	public:
		static std::filesystem::path AssetsPath();
	};
}