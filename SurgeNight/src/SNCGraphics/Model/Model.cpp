#include "Model.h"
#include "assimp/Importer.hpp"
#include "assimp/scene.h"
#include "assimp/postprocess.h"

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
        return;
    }

    std::string path = filename.substr(0, filename.find_last_of('/'));
    loadNode(scene->mRootNode, scene, path);
}

void Model::loadNode(const aiNode *node, const aiScene *scene, const std::string &path)
{
    for (auto i = 0u; i < node->mNumMeshes; ++i) {
        m_meshes.push_back(Mesh());
        auto &omesh = m_meshes[m_meshes.size() - 1];
        aiMesh *mesh = scene->mMeshes[node->mMeshes[i]];

        for (auto i = 0u; i < mesh->mNumVertices; ++i) {
            omesh.getVertexs().push_back(
                Vertex(
                    glm::vec3(mesh->mVertices[i].x, mesh->mVertices[i].y, mesh->mVertices[i].z),
                    glm::vec3(mesh->mNormals[i].x, mesh->mNormals[i].y, mesh->mNormals[i].z),
                    glm::vec2(NULL == mesh->mTextureCoords[0] ? 0.0f : mesh->mTextureCoords[0][i].x,
                              NULL == mesh->mTextureCoords[0] ? 0.0f : mesh->mTextureCoords[0][i].y),
                    glm::vec3(mesh->mTangents[i].x, mesh->mTangents[i].y, mesh->mTangents[i].z),
                    glm::vec3(mesh->mBitangents[i].x, mesh->mBitangents[i].y, mesh->mBitangents[i].z)
                )
            );
        }

        for (auto i = 0u; i < mesh->mNumFaces; ++i) {
            auto &face = mesh->mFaces[i];
            for (auto j = 0u; j < face.mNumIndices; ++j) {
                omesh.getIndexes().push_back(face.mIndices[j]);
            }
        }

        aiMaterial *mat = scene->mMaterials[mesh->mMaterialIndex];
        for (auto &type : {aiTextureType_DIFFUSE, aiTextureType_SPECULAR, aiTextureType_HEIGHT, aiTextureType_AMBIENT}) {
            for (auto i = 0u; i < mat->GetTextureCount(type); ++i) {
                aiString str;
                mat->GetTexture(type, i, &str);

            }
        }

        omesh.load();
    }

    for (auto i = 0u; i < node->mNumChildren; ++i)
        loadNode(node->mChildren[i], scene, path);
}

}
