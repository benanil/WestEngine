#include "Helper.h"

namespace WestEngine
{
	std::filesystem::path Helper::AssetsPath()
	{
		static std::filesystem::path path = std::filesystem::current_path().parent_path().append("Assets");
		return path;
	}
}