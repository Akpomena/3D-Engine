#include "CubeMap.h"
#include <glad/glad.h>
#include <stb_image.h>
#include <iostream>

#include "VertexBufferLayout.h"
#include "./Camera.h"

Engine::SkyBox::SkyBox(std::string path): m_SkyboxShader("assets/shaders/SkyboxShader.vert", "assets/shaders/SkyboxShader.frag")
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

    //SkyBox

    float skyboxVertices[] = {
        // positions          
        -1.0f,  1.0f, -1.0f,
        -1.0f, -1.0f, -1.0f,
         1.0f, -1.0f, -1.0f,
         1.0f, -1.0f, -1.0f,
         1.0f,  1.0f, -1.0f,
        -1.0f,  1.0f, -1.0f,

        -1.0f, -1.0f,  1.0f,
        -1.0f, -1.0f, -1.0f,
        -1.0f,  1.0f, -1.0f,
        -1.0f,  1.0f, -1.0f,
        -1.0f,  1.0f,  1.0f,
        -1.0f, -1.0f,  1.0f,

         1.0f, -1.0f, -1.0f,
         1.0f, -1.0f,  1.0f,
         1.0f,  1.0f,  1.0f,
         1.0f,  1.0f,  1.0f,
         1.0f,  1.0f, -1.0f,
         1.0f, -1.0f, -1.0f,

        -1.0f, -1.0f,  1.0f,
        -1.0f,  1.0f,  1.0f,
         1.0f,  1.0f,  1.0f,
         1.0f,  1.0f,  1.0f,
         1.0f, -1.0f,  1.0f,
        -1.0f, -1.0f,  1.0f,

        -1.0f,  1.0f, -1.0f,
         1.0f,  1.0f, -1.0f,
         1.0f,  1.0f,  1.0f,
         1.0f,  1.0f,  1.0f,
        -1.0f,  1.0f,  1.0f,
        -1.0f,  1.0f, -1.0f,

        -1.0f, -1.0f, -1.0f,
        -1.0f, -1.0f,  1.0f,
         1.0f, -1.0f, -1.0f,
         1.0f, -1.0f, -1.0f,
        -1.0f, -1.0f,  1.0f,
         1.0f, -1.0f,  1.0f
    };

    VertexBuffer skybuf(&skyboxVertices, sizeof(skyboxVertices));
    VertexBufferLayout skyboxLayout;
    skyboxLayout.push<float>(3);

    m_SkyboxVAO.AddBuffer(skybuf, skyboxLayout);
    glBindVertexArray(0);

}

void Engine::SkyBox::Draw(Camera& camera)
{
    //Skybox

    glDepthFunc(GL_LEQUAL);
    m_SkyboxShader.Bind();

    glm::mat4 view = glm::mat4(glm::mat3(camera.GetViewMatrix())); // remove translation from the view matrix
    m_SkyboxShader.SetUniformMat4("view", std::move(view));
    m_SkyboxShader.SetUniformMat4("projection", camera.GetProjMatrix());

    m_SkyboxVAO.bind();
    glBindTexture(GL_TEXTURE_CUBE_MAP, m_CubeMapID);
    glDrawArrays(GL_TRIANGLES, 0, 36);
    glDepthFunc(GL_LESS);
}

void Engine::SkyBox::Bind()
{
    glBindTexture(GL_TEXTURE_CUBE_MAP, m_CubeMapID);
}
