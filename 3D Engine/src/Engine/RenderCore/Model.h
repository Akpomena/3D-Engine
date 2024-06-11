#pragma once

#include "./Mesh.h"
#include "./Shader.h"

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <map>
#include <vector>

extern struct aiNode;
extern struct aiScene;
extern struct aiMesh;
extern struct aiMaterial;
extern enum aiTextureType;

namespace Engine {

    class Model
    {
    public:
        // model data 
        std::vector<Texture> textures_loaded;	// stores all the textures loaded so far, optimization to make sure textures aren't loaded more than once.
        std::vector<Mesh>    meshes;
        std::string directory;
        bool gammaCorrection;

        // constructor, expects a filepath to a 3D model.
        Model(std::string const& path, bool gamma = false);

        // Default Constructor
        Model();
        std::vector<Mesh>& GetMeshes() { return meshes; }

        // draws the model, and thus all its meshes
        void Draw(Shader& shader);

        // loads a model with supported ASSIMP extensions from file and stores the resulting meshes in the meshes vector.
        void loadModel(std::string const& path);

        std::string m_ModelName = "No Model Loaded";
    private:

        // processes a node in a recursive fashion. Processes each individual mesh located at the node and repeats this process on its children nodes (if any).
        void processNode(aiNode* node, const aiScene* scene);


        Mesh processMesh(aiMesh* mesh, const aiScene* scene);

        // checks all material textures of a given type and loads the textures if they're not loaded yet.
        // the required info is returned as a Texture struct.
        std::vector<Texture> loadMaterialTextures(aiMaterial* mat, aiTextureType type, std::string typeName);
    };

}