#pragma once

// Includes
#include "Types.h"
#include "ECS.h"

#include <string>
#include <vector>

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

// Forward Declarations
class Mesh;

/* Model
 */
class Model : public Component {
    public:
        Model();
        virtual ~Model();

        void set_transform(Transform transform);

        void load_model(const std::string &file_path);

        void get_meshes(std::vector<Mesh *> &meshes);

    private:
        void process_node(const aiNode *node, const aiScene *scene);
        Mesh *process_mesh(const aiMesh *mesh, const aiScene *scene);

        std::vector<Mesh *> m_meshes;
};
