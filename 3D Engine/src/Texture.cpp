#include "Texture.h"

#include <glad/glad.h>
#include "../vendor/stb_image/stb_image.h"

Texture::Texture(const char* texturePath, unsigned int textureSlot)
{
	stbi_set_flip_vertically_on_load(true);

	glGenTextures(1, &m_TextureID);
	glActiveTexture(GL_TEXTURE0 + textureSlot);
	glBindTexture(GL_TEXTURE_2D, m_TextureID);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	unsigned char* data = stbi_load(texturePath, &m_Width, &m_Height, &m_Channels, 0);

	int channelEnum = 0;
	if (m_Channels == 3)
		channelEnum = GL_RGB;
	else
		channelEnum = GL_RGBA;

	glTexImage2D(GL_TEXTURE_2D, 0, channelEnum, m_Width, m_Height, 0, channelEnum, GL_UNSIGNED_BYTE, data);
	glGenerateMipmap(GL_TEXTURE_2D);

	stbi_image_free(data);
}
