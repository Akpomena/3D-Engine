#include "Texture.h"

#include <glad/glad.h>
#include <stb_image.h>
#include <iostream>

Texture::Texture(std::string texturePath, unsigned int textureSlot, std::string type):
	m_Path(texturePath), m_Slot(textureSlot), m_Type(type)
{
	stbi_set_flip_vertically_on_load(true);

	glGenTextures(1, &m_TextureID);
	//glActiveTexture(GL_TEXTURE0 + textureSlot);
	glBindTexture(GL_TEXTURE_2D, m_TextureID);

	unsigned char* data = stbi_load(texturePath.c_str(), &m_Width, &m_Height, &m_Channels, 0);

	if (data)
	{
		GLenum format = 0;
		if (m_Channels == 1)
			format = GL_RED;
		else if (m_Channels == 3)
			format = GL_RGB;
		else if (m_Channels == 4)
			format = GL_RGBA;

		glTexImage2D(GL_TEXTURE_2D, 0, format, m_Width, m_Height, 0, format, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		stbi_image_free(data);
	}
	else
	{
		std::cout << "Texture failed to load at path: " << m_Path << std::endl;
		stbi_image_free(data);
	}
}

void Texture::Bind()
{
	glBindTexture(GL_TEXTURE_2D, m_TextureID);
}
