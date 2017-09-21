#include "Model.h"
#include "assimp/Importer.hpp"
#include "assimp/scene.h"
#include "assimp/postprocess.h"
#include <iostream>
#include <map>

namespace SurgeNight
{

Model::Model(const std::string &filename)
{
    load(filename);
}

Model::~Model()
{

}

void Model::paint(ShaderProgram &shader)
{
    for (auto &mesh : m_meshes) {
        mesh.registerTexture(shader);
        mesh.paint();
    }
}

void Model::load(const std::string &filename)
{
    Assimp::Importer importer;
    const aiScene *scene = importer.ReadFile(filename, aiProcess_Triangulate | aiProcess_FlipUVs | aiProcess_CalcTangentSpace);

    if (NULL == scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || NULL == scene->mRootNode) {
        std::cerr << "Test, error!" << std::endl;
        return;
    }

    std::string path = filename.substr(0, filename.find_last_of('/'));
    loadNode(scene->mRootNode, scene, path);
}

void Model::loadNode(const aiNode *node, const aiScene *scene, const std::string &path)
{
    for (auto i = 0u; i < node->mNumMeshes; ++i) {
        auto &omesh = *m_meshes.insert(m_meshes.end(), Mesh());
        aiMesh *mesh = scene->mMeshes[node->mMeshes[i]];

        for (auto j = 0u; j < mesh->mNumVertices; ++j) {
            omesh.getVertexs().push_back(
                Vertex(
                    glm::vec3(mesh->mVertices[j].x, mesh->mVertices[j].y, mesh->mVertices[j].z),
                    glm::vec3(mesh->mNormals[j].x, mesh->mNormals[j].y, mesh->mNormals[j].z),
                    glm::vec2(NULL == mesh->mTextureCoords[0] ? 0.0f : mesh->mTextureCoords[0][j].x,
                              NULL == mesh->mTextureCoords[0] ? 0.0f : mesh->mTextureCoords[0][j].y),
                    glm::vec3(mesh->mTangents[j].x, mesh->mTangents[j].y, mesh->mTangents[j].z),
                    glm::vec3(mesh->mBitangents[j].x, mesh->mBitangents[j].y, mesh->mBitangents[j].z)
                )
            );
        }

        for (auto k = 0u; k < mesh->mNumFaces; ++k) {
            aiFace face = mesh->mFaces[k];
            for (auto j = 0u; j < face.mNumIndices; ++j) {
                omesh.getIndexes().push_back(face.mIndices[j]);
            }
        }

        std::string filename;
        aiMaterial *mat = scene->mMaterials[mesh->mMaterialIndex];
        std::map<aiTextureType, int> types{
            { aiTextureType_DIFFUSE, Texture2D::TEXTURE_DIFFUSE },
            { aiTextureType_SPECULAR, Texture2D::TEXTURE_SPECULAR },
            { aiTextureType_AMBIENT, Texture2D::TEXTURE_AMBIENT },
            { aiTextureType_HEIGHT, Texture2D::TEXTURE_HEIGHT },
            { aiTextureType_NORMALS, Texture2D::TEXTURE_NORMAL }
        };
        for (auto &type : types) {
            for (auto j = 0u; j < mat->GetTextureCount(type.first); ++j) {
                aiString str;
                mat->GetTexture(type.first, j, &str);

                filename = path;
                filename += "/";
                filename += str.C_Str();

                bool alreadyHave = false;
                for (auto &tex : m_textures) {
                    if (tex->getFilename() == filename) {
                        omesh.getTextures().push_back(tex);
                        alreadyHave = true;
                        break;
                    }
                }

                if (!alreadyHave) {
                    auto texture = std::make_shared<Texture2D>(filename, m_textures.size(), type.second);
                    m_textures.push_back(texture);
                    omesh.getTextures().push_back(texture);
                }
            }
        }

        omesh.load();
    }

    for (auto i = 0u; i < node->mNumChildren; ++i)
        loadNode(node->mChildren[i], scene, path);
}

}
