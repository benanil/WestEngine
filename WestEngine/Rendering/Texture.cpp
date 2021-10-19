#include "Texture.h"
#include "glad.h"
#include "SOIL/SOIL.h"
#include <iostream>
#include <filesystem>

namespace WestEngine
{
	Texture::Texture(const bool generateMipMaps, const char* path) {
		const char* imgPath = std::filesystem::current_path().parent_path().append("Assets").append(path).u8string().c_str();
		int width, height;
		int channels;
		unsigned char* data = SOIL_load_image(imgPath, &width, &height, &channels, 0);

		std::cout << "channels" << channels << std::endl;
		std::cout << "image path: " << imgPath << std::endl;
		std::cout << "texture message: " << SOIL_last_result() << std::endl;

		texID = 0;
		glGenTextures(1, &texID);
		glBindTexture(GL_TEXTURE_2D, texID);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
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

		SOIL_free_image_data(data);
	}

	void Texture::Bind() const
	{
		glBindTexture(GL_TEXTURE_2D, texID);
	}
}
