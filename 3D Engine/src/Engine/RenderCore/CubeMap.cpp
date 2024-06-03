#include "CubeMap.h"
#include <glad/glad.h>
#include <stb_image.h>
#include <iostream>

Engine::CubeMap::CubeMap(std::string path)
{

    glGenTextures(1, &m_CubeMapID);
    glBindTexture(GL_TEXTURE_CUBE_MAP, m_CubeMapID);

    int width, height, nrChannels;
    stbi_set_flip_vertically_on_load(true);
    for (unsigned int i = 0; i < m_Faces.size(); i++)
    {
        unsigned char* data = stbi_load((path + m_Faces[i]).c_str(), &width, &height, &nrChannels, 0);

        if (data)
        {
            glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i,
                0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data
            );
            stbi_image_free(data);
        }
        else
        {
            std::cout << "Cubemap tex failed to load at path: " << (path + m_Faces[i]) << std::endl;
            stbi_image_free(data);
        }
    }
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

}

void Engine::CubeMap::Draw()
{
    
}

void Engine::CubeMap::Bind()
{
    glBindTexture(GL_TEXTURE_CUBE_MAP, m_CubeMapID);
}
