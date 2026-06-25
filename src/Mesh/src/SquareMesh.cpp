#include "SquareMesh.h"

#include <cstring>


float square_vertices[] = {
   -1.0f, -1.0f, 0.0f,  // Bottom-left
    1.0f, -1.0f, 0.0f,  // Bottom-right
   -1.0f,  1.0f, 0.0f,  // Top-left
    1.0f, -1.0f, 0.0f,  // Bottom-right
    1.0f,  1.0f, 0.0f,  // Top-right
   -1.0f,  1.0f, 0.0f   // Top-left
};

float square_normals[] = {
    // front face
    0.0f, 0.0f, 1.0f,
    0.0f, 0.0f, 1.0f,
    0.0f, 0.0f, 1.0f,
    0.0f, 0.0f, 1.0f,
    0.0f, 0.0f, 1.0f,
    0.0f, 0.0f, 1.0f
};

float square_uvs[] = {
    0.0f, 0.0f,  // Bottom-left
    1.0f, 0.0f,  // Bottom-right
    0.0f, 1.0f,  // Top-left
    1.0f, 0.0f,  // Bottom-right
    1.0f, 1.0f,  // Top-right
    0.0f, 1.0f   // Top-left
};

/* SquareMesh
 */
SquareMesh::SquareMesh() {
    m_num_vertices = SQUARE_NUM_VERTICES;

    m_vertex_buffer.stride = 3;
    m_vertex_buffer.size = sizeof(float) * m_vertex_buffer.stride * m_num_vertices;
    m_vertex_buffer.data = new float[m_vertex_buffer.size];

    m_normal_buffer.stride = 3;
    m_normal_buffer.size = sizeof(float) * m_normal_buffer.stride * m_num_vertices;
    m_normal_buffer.data = new float[m_normal_buffer.size];

    m_uv_buffer.stride = 2;
    m_uv_buffer.size = sizeof(float) * m_uv_buffer.stride * m_num_vertices;
    m_uv_buffer.data = new float[m_uv_buffer.size];

    memcpy(m_vertex_buffer.data, square_vertices, m_vertex_buffer.size);
    memcpy(m_normal_buffer.data, square_normals, m_normal_buffer.size);
    memcpy(m_uv_buffer.data, square_uvs, m_uv_buffer.size);
}

/* ~SquareMesh
 */
SquareMesh::~SquareMesh() {
    delete m_vertex_buffer.data;
    delete m_normal_buffer.data;
    delete m_uv_buffer.data;
}