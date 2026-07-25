#pragma once

// Includes
#include "Types.h"
#include "Mesh.h"

#include <vector>

/* MeshInstances
 */
class MeshInstances : public Mesh {
    public:
        MeshInstances(Mesh *instance);
        MeshInstances(Mesh *instance, std::vector<Transform> transforms);
        virtual ~MeshInstances();

        void render();

        void add_transform(Transform transform);
        void set_transforms(std::vector<Transform> transforms);

    private:
        static mat4 build_model_matrix(Transform transform);

        Mesh *m_instance;
        std::vector<mat4> m_models;
        int m_num_vertices;
};