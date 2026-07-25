#include "CircleMesh.h"

#include <cmath>

namespace {
    constexpr float PI = 3.14159265358979323846f;
}

/* CircleMesh
 * Approximates a unit circle as a flat triangle list (center + two adjacent
 * perimeter points per segment), since Mesh always draws with GL_TRIANGLES.
 */
CircleMesh::CircleMesh(unsigned int segments) {
    m_num_vertices = segments * 3;

    m_vertex_buffer.stride = 3;
    m_vertex_buffer.size = sizeof(float) * m_vertex_buffer.stride * m_num_vertices;
    m_vertex_buffer.data = new float[m_vertex_buffer.size];

    m_normal_buffer.stride = 3;
    m_normal_buffer.size = sizeof(float) * m_normal_buffer.stride * m_num_vertices;
    m_normal_buffer.data = new float[m_normal_buffer.size];

    m_uv_buffer.stride = 2;
    m_uv_buffer.size = sizeof(float) * m_uv_buffer.stride * m_num_vertices;
    m_uv_buffer.data = new float[m_uv_buffer.size];

    unsigned int v_index = 0;
    unsigned int n_index = 0;
    unsigned int uv_index = 0;

    for (unsigned int i = 0; i < segments; i++) {
        float angle0 = (float)i / segments * 2.0f * PI;
        float angle1 = (float)(i + 1) / segments * 2.0f * PI;

        // Center
        m_vertex_buffer.data[v_index++] = 0.0f;
        m_vertex_buffer.data[v_index++] = 0.0f;
        m_vertex_buffer.data[v_index++] = 0.0f;

        // Perimeter point 0
        m_vertex_buffer.data[v_index++] = cosf(angle0);
        m_vertex_buffer.data[v_index++] = sinf(angle0);
        m_vertex_buffer.data[v_index++] = 0.0f;

        // Perimeter point 1
        m_vertex_buffer.data[v_index++] = cosf(angle1);
        m_vertex_buffer.data[v_index++] = sinf(angle1);
        m_vertex_buffer.data[v_index++] = 0.0f;

        for (int j = 0; j < 3; j++) {
            m_normal_buffer.data[n_index++] = 0.0f;
            m_normal_buffer.data[n_index++] = 0.0f;
            m_normal_buffer.data[n_index++] = 1.0f;
        }

        m_uv_buffer.data[uv_index++] = 0.5f;
        m_uv_buffer.data[uv_index++] = 0.5f;

        m_uv_buffer.data[uv_index++] = 0.5f + 0.5f * cosf(angle0);
        m_uv_buffer.data[uv_index++] = 0.5f + 0.5f * sinf(angle0);

        m_uv_buffer.data[uv_index++] = 0.5f + 0.5f * cosf(angle1);
        m_uv_buffer.data[uv_index++] = 0.5f + 0.5f * sinf(angle1);
    }
}

/* ~CircleMesh
 */
CircleMesh::~CircleMesh() {
    delete m_vertex_buffer.data;
    delete m_normal_buffer.data;
    delete m_uv_buffer.data;
}
