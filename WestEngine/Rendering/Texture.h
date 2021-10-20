#pragma once
#include "Common.h"

namespace WestEngine
{
	class Texture
	{
	public:
		const char* path;
		Texture(const bool generateMipMaps, const char* path);
		void Bind() const;
		unsigned int texID;
	};
}

