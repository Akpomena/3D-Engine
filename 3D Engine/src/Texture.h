#pragma once

class Texture
{
public:
	Texture(const char* texturePath, unsigned int textureSlot);
private:
	unsigned int m_TextureID;
	int m_Width, m_Height, m_Channels;
};

