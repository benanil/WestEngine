#pragma once
#include "Common.h"

namespace WestEngine
{
	class Texture
	{
	private:
		int width, height;
		unsigned char* data;
		unsigned int iconID;
		static unsigned int CreateIconInternal(unsigned char* data, const int& width, const int& height, const int& channelCount);
	public:
		const char* path;
		unsigned int texID;

		Texture(const bool generateMipMaps, const char* path);
		~Texture() { FreeData(); }
		
		void Bind() const;
		void FreeData() const ;
		// getters
		unsigned char* GetData() const { return data;   };
		const int& GetWidth()    const { return width;  };
		const int& GetHeight()   const { return height; };
		const unsigned int& GetTextureID() const { return texID; };
		const unsigned int& GetIconID() const { return iconID; }
		static unsigned int CreateIcon(const char* path);
		static unsigned int GetMiniTexture(const Texture* texture, const int& size = 64, const bool& disposeTextureAfter = true);
	};
}

