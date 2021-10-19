#pragma once
namespace WestEngine
{
	class Texture
	{
	public:
		Texture(const bool generateMipMaps, const char* path);
		void Bind() const;
		unsigned int texID;
	};
}

