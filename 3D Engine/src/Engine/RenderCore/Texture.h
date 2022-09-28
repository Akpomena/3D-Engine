#pragma once

#include <string>

class Texture
{
public:
	std::string m_Type, m_Path;
public:
	Texture(std::string texturePath, unsigned int textureSlot, std::string type = "");
	void Bind();
	unsigned int GetID() { return m_TextureID; }
private:
	unsigned int m_TextureID, m_Slot;
	int m_Width, m_Height, m_Channels;
};

