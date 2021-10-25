#include "Texture.h"
#include "Common.h"
#include "External/stb_image.h"
#include "External/stb_image_resize.h"
#include <iostream>
#include <filesystem>
#include "spdlog/spdlog.h"

namespace WestEngine
{
	Texture::Texture(const bool generateMipMaps, const char* path) {
		path = Helper::AssetsPath().append(path).u8string().c_str();
		
		if (!std::filesystem::exists(Helper::AssetsPath().append(path)))
		{
			spdlog::error("texture is not exist! {0}", path);
		}
		
		int channels;
		data = stbi_load(path, &width, &height, &channels, 0);
		if (data == nullptr) spdlog::error("Texture Creation Failed!");
		// if we are generating texture for low performance devides we can downsample our image here

		GLint ChannelType = GL_GREEN + channels; // channel 3 = GL_RGB, channel 4 = GL_RGBA
		// create opengl texture for icon
		iconID = CreateIconInternal(data, width, height, channels);
		
		// create opengl texture
		texID = 0;
		glGenTextures(1, &texID);
		glBindTexture(GL_TEXTURE_2D, texID);
		glTexImage2D(GL_TEXTURE_2D, 0, ChannelType, width, height, 0, ChannelType, GL_UNSIGNED_BYTE, data);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		
		if (generateMipMaps) {
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
			glGenerateMipmap(GL_TEXTURE_2D);
		}
		else {
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		}

		glBindTexture(GL_TEXTURE_2D, 0);
		// if we want we couldnt use later but for now I want to delete them so we cannot use Create MiniTexture for now
		stbi_image_free(data);
	}

	void Texture::Bind() const
	{
		glBindTexture(GL_TEXTURE_2D, texID);
	}

	void Texture::FreeData() const { stbi_image_free(data); };

	// creates opengl texture for icons
	unsigned int Texture::CreateIcon(const char* path)
	{
		path = Helper::AssetsPath().append("Textures").append("Icons").append(path).u8string().c_str();
		int channels = 0, width = 0, height = 0;

		if (!std::filesystem::exists(path))
		{
			spdlog::error("icon Creation Failed! file is not exist!");
		}

		unsigned char* data = stbi_load(path, &width, &height, &channels, 0);
		
		if (data == nullptr) spdlog::error("icon Creation Failed!");
	
		unsigned int iconID = CreateIconInternal(data, width, height, channels);
		
		stbi_image_free(data);
		return iconID;
	}

	/// <summary> downsamles the image </summary>
	unsigned int Texture::CreateIconInternal(unsigned char* data, const int& width, 
											 const int& height, const int& channelCount)
	{
		unsigned char* iconData = (unsigned char*)malloc(64 * 64 * channelCount);
		GLint ChannelType = GL_GREEN + channelCount; // channel 3 = GL_RGB, channel 4 = GL_RGBA

		// downsampling for icon
		stbir_resize_uint8(data, width, height, width * channelCount,
		iconData, 64, 64, 64 * channelCount, channelCount); 

		if (ChannelType == GL_RGBA) spdlog::warn("channel type true!");
		if (iconData == nullptr) spdlog::error("icon loading failed Internal!");

		// create opengl texture for icon
		unsigned int iconID = 0;
		glGenTextures(1, &iconID);
		glBindTexture(GL_TEXTURE_2D, iconID);
		glTexImage2D(GL_TEXTURE_2D, 0, ChannelType, 64, 64, 0, ChannelType, GL_UNSIGNED_BYTE, iconData);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glBindTexture(GL_TEXTURE_2D, 0);
		stbi_image_free(iconData);
		return iconID;
	}

	/// <summary> this can be usefull for UI textures. </summary>
	/// <param name="size">use power of two. x and y both same size for now we can add owerload method in future</param>
	/// <param name="disposeTextureAfter"> deletes source texture data after creation of mini texture</param>
	/// <returns> opengl texture id</returns>
	/// channel count must be added if we want to use this
	unsigned int Texture::GetMiniTexture(const Texture* texture, const int& miniSize, const bool& disposeTextureAfter)
	{
		unsigned char* resizedPixels = (unsigned char*)malloc(texture->GetWidth() * texture->GetHeight() * 3);
		
		// downsampling
		stbir_resize_uint8(texture->GetData(), texture->GetWidth(), texture->GetHeight(),
						   texture->GetWidth() * 3, resizedPixels, miniSize, miniSize, miniSize * 3, 3);

		unsigned int texID = 0;
		glGenTextures(1, &texID);
		glBindTexture(GL_TEXTURE_2D, texID);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, miniSize, miniSize, 0, GL_RGB, GL_UNSIGNED_BYTE, resizedPixels);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		
		glBindTexture(GL_TEXTURE_2D, 0);

		if (disposeTextureAfter) stbi_image_free(texture->GetData());
		stbi_image_free(resizedPixels);
		
		return texID;
	}
}
