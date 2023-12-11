#include "./Mesh.h"
#include "./VertexBufferLayout.h"


Engine::Mesh::Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices, std::vector<Texture> textures)
{
    this->vertices = vertices;
    this->indices = indices;
    this->textures = textures;

    // now that we have all the required data, set the vertex buffers and its attribute pointers.
    setupMesh();
}

Engine::Mesh::Mesh(std::vector<Vertex> vertices, std::vector<Texture> textures)
{
    this->vertices = vertices;
    this->textures = textures;

    setupMesh();
}

void Engine::Mesh::Draw(Shader& shader)
{
    shader.Bind();
    // bind appropriate texturesstd::vector
    unsigned int diffuseNr = 1;
    unsigned int specularNr = 1;
    unsigned int normalNr = 1;
    unsigned int heightNr = 1;

    for (unsigned int i = 0; i < textures.size(); i++)
    {
        glActiveTexture(GL_TEXTURE0 + i); // active proper texture unit before binding
        // retrieve texture number (the N in diffuse_textureN)
        std::string number;
        std::string name = textures[i].m_Type;
        if (name == "texture_diffuse")
            number = std::to_string(diffuseNr++);
        else if (name == "texture_specular")
            number = std::to_string(specularNr++); // transfer unsigned int to string
        else if (name == "texture_normal")
            number = std::to_string(normalNr++); // transfer unsigned int to string
        else if (name == "texture_height")
            number = std::to_string(heightNr++); // transfer unsigned int to string

        // now set the sampler to the correct texture unit
        shader.SetUniformInt((name + number), i);
        // and finally bind the texture
        textures[i].Bind();
    }

    // Setting Transform
    glm::mat4 transform = glm::mat4(1.0f);
    transform = glm::translate(transform, m_Position);
   // transform = glm::rotate()
    transform = glm::scale(transform, m_Scale);

    shader.SetUniformMat4("u_Model", transform);

    // draw mesh
    m_VertexArray->bind();
    //glDrawElements(GL_TRIANGLES, m_IndexBuffer->GetCount(), GL_UNSIGNED_INT, 0);
    glDrawArrays(GL_TRIANGLES, 0, vertices.size() * 88);
    //glBindVertexArray(0);

    // always good practice to set everything back to defaults once configured.
    glActiveTexture(GL_TEXTURE0);
}

void Engine::Mesh::setupMesh()
{
    m_VertexArray = std::make_unique<VertexArray>();

    m_VertexBuffer = std::make_unique<VertexBuffer>(&vertices[0], vertices.size() * sizeof(Vertex));
    VertexBufferLayout layout;
    layout.push<float>(3);
    layout.push<float>(3);
    layout.push<float>(2);
    layout.push<float>(3);
    layout.push<float>(3);
    layout.push<int>(4);
    layout.push<float>(4);

   
    m_VertexArray->AddBuffer(*m_VertexBuffer, layout);

   // m_IndexBuffer = std::make_unique<IndexBuffer>(&indices[0], indices.size());

    glBindVertexArray(0);
}