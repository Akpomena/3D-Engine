#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "./Shader.h"
#include "./Texture.h"
#include "./VertexArray.h"
#include "./VertexBuffer.h"
#include "./IndexBuffer.h"

#include <string>
#include <vector>
#include <memory>


#define MAX_BONE_INFLUENCE 4

    struct Vertex {
        // position
        glm::vec3 Position;
        // normal
        glm::vec3 Normal;
        // texCoords
        glm::vec2 TexCoords;
        // tangent
        glm::vec3 Tangent;
        // bitangent
        glm::vec3 Bitangent;
        //bone indexes which will influence this vertex
        int m_BoneIDs[MAX_BONE_INFLUENCE];
        //weights from each bone
        float m_Weights[MAX_BONE_INFLUENCE];
    };

    class Mesh {
    public:

        // constructor
        Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices, std::vector<Texture> textures);

        // Temp
        Mesh(std::vector<Vertex> vertices, std::vector<Texture> textures);

        // render the mesh
        void Draw(Shader& shader);

        // Update position
        void SetPosition(glm::vec3&& pos) { m_Position = pos; }

    private:
        // Transform
        glm::vec3 m_Position = { 0.0f, 0.0f, 0.0f };
        glm::vec3 m_Scale = { 1.0f, 1.0f, 1.0f }; 
        glm::vec3 m_Rotation = { 0.0f, 0.0f, 0.0f };

        // mesh Data
        std::vector<Vertex>       vertices;
        std::vector<unsigned int> indices;
        std::vector<Texture>      textures;

        // render data 

        std::unique_ptr<VertexBuffer> m_VertexBuffer;
        std::unique_ptr<IndexBuffer> m_IndexBuffer;
        std::unique_ptr<VertexArray> m_VertexArray;

    private:
        // initializes all the buffer objects/arrays
        void setupMesh();
    };
   
