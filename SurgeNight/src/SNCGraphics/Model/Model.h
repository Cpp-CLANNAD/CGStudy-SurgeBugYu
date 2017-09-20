#ifndef SN_MODEL_H
#define SN_MODEL_H

#include "Texture2D.h"
#include "Mesh.h"
#include "../ShaderProgram.h"
#include <memory>
#include <vector>
#include "assimp/scene.h"

namespace SurgeNight
{

class Model
{
public:
    Model(const std::string &filename);
    ~Model();

    void paint(ShaderProgram &shader);

private:
    void load(const std::string &filename);
    void loadNode(const aiNode *node, const aiScene *scene, const std::string &path);

    std::vector<Mesh> m_meshes;
    std::vector<std::shared_ptr<Texture2D>> m_textures;
};

}

#endif // SN_MODEL_H
