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

        bool has_instance_colors() const override { return !m_colors.empty(); }

        void add_transform(Transform transform);
        void set_transforms(std::vector<Transform> transforms);
        void set_colors(std::vector<vec3> colors);

    private:
        static mat4 build_model_matrix(Transform transform);

        Mesh *m_instance;
        std::vector<mat4> m_models;
        std::vector<vec3> m_colors;
        unsigned int m_color_buffer_object;
        int m_num_vertices;
};