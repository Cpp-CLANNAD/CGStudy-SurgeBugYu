#ifndef SN_MODEL_H
#define SN_MODEL_H

#include "SNCGraphics/Model/Mesh.h"
#include "SNCGraphics/Model/Texture2D.h"
#include "SNCGraphics/ShaderProgram.h"
#include "assimp/scene.h"
#include <memory>
#include <vector>

namespace SurgeNight
{

class Model
{
public:
    explicit Model(const std::string &filename);
    ~Model();

    void paint(ShaderProgram &shader);

    std::vector<Mesh> m_meshes;
private:
    void load(const std::string &filename);
    void loadNode(const aiNode *node, const aiScene *scene, const std::string &path);

    std::vector<std::shared_ptr<Texture2D>> m_textures;
};

}

#endif // SN_MODEL_H
