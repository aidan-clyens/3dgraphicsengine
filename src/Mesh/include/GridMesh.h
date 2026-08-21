#pragma once

// Includes
#include "Mesh.h"

#include <vector>

/* GridMesh
 */
class GridMesh : public Mesh
{
public:
    GridMesh(size_t resolution = 64);
    GridMesh(size_t resolution, const std::vector<float> &heights);
    ~GridMesh() = default;

    void set_heights(const std::vector<float> &heights);

    size_t get_resolution() const { return m_resolution; }

private:
    void build_vertices();
    float get_height(size_t x, size_t y) const;
    vec3 get_position(size_t x, size_t y) const;
    vec3 get_normal(size_t x, size_t y) const;

    size_t m_resolution;
    std::vector<float> m_heights;
};
