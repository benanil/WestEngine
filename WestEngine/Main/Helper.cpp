#include "Helper.h"

namespace Helper
{
	using namespace std::filesystem;
	std::filesystem::path AssetsPath()
	{
		static std::filesystem::path path = std::filesystem::current_path().parent_path().append("Assets");
		return path;
	}
}