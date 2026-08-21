#include "GridMesh.h"

#include <glm/glm.hpp>
#include <algorithm>

/* GridMesh
 */
GridMesh::GridMesh(size_t resolution) : m_resolution(resolution),
                                        m_heights(resolution * resolution, 0.0f)
{
  this->build_vertices();
  this->create_mesh();
}

/* GridMesh
 */
GridMesh::GridMesh(size_t resolution, const std::vector<float> &heights) : m_resolution(resolution),
                                                                           m_heights(resolution * resolution, 0.0f)
{
  size_t count = std::min(heights.size(), m_heights.size());
  std::copy(heights.begin(), heights.begin() + count, m_heights.begin());

  this->build_vertices();
  this->create_mesh();
}

/* set_heights
 */
void GridMesh::set_heights(const std::vector<float> &heights)
{
  size_t count = std::min(heights.size(), m_heights.size());
  std::copy(heights.begin(), heights.begin() + count, m_heights.begin());

  this->build_vertices();
  this->create_mesh();
}

/* build_vertices
 */
void GridMesh::build_vertices()
{
  m_vertices.clear();

  if (m_resolution < 2)
  {
    m_num_vertices = 0;
    return;
  }

  float spacing = 1.0f / (float)(m_resolution - 1);

  for (size_t y = 0; y < m_resolution - 1; y++)
  {
    for (size_t x = 0; x < m_resolution - 1; x++)
    {
      vec3 p00 = this->get_position(x, y);
      vec3 p10 = this->get_position(x + 1, y);
      vec3 p01 = this->get_position(x, y + 1);
      vec3 p11 = this->get_position(x + 1, y + 1);

      vec3 n00 = this->get_normal(x, y);
      vec3 n10 = this->get_normal(x + 1, y);
      vec3 n01 = this->get_normal(x, y + 1);
      vec3 n11 = this->get_normal(x + 1, y + 1);

      vec2 uv00((float)x * spacing, (float)y * spacing);
      vec2 uv10((float)(x + 1) * spacing, (float)y * spacing);
      vec2 uv01((float)x * spacing, (float)(y + 1) * spacing);
      vec2 uv11((float)(x + 1) * spacing, (float)(y + 1) * spacing);

      Vertex v00 = {p00, n00, uv00};
      Vertex v10 = {p10, n10, uv10};
      Vertex v01 = {p01, n01, uv01};
      Vertex v11 = {p11, n11, uv11};

      // Triangle 1
      m_vertices.push_back(v00);
      m_vertices.push_back(v01);
      m_vertices.push_back(v10);

      // Triangle 2
      m_vertices.push_back(v10);
      m_vertices.push_back(v01);
      m_vertices.push_back(v11);
    }
  }

  m_num_vertices = (unsigned int)m_vertices.size();
}

/* get_height
 */
float GridMesh::get_height(size_t x, size_t y) const
{
  return m_heights[y * m_resolution + x];
}

/* get_position
 */
vec3 GridMesh::get_position(size_t x, size_t y) const
{
  float spacing = 1.0f / (float)(m_resolution - 1);

  float px = (float)x * spacing - 0.5f;
  float pz = (float)y * spacing - 0.5f;
  float py = this->get_height(x, y);

  return vec3(px, py, pz);
}

/* get_normal
 */
vec3 GridMesh::get_normal(size_t x, size_t y) const
{
  int res = (int)m_resolution;
  int xi = (int)x;
  int yi = (int)y;

  int x0 = std::max(xi - 1, 0);
  int x1 = std::min(xi + 1, res - 1);
  int y0 = std::max(yi - 1, 0);
  int y1 = std::min(yi + 1, res - 1);

  float h_x0 = this->get_height((size_t)x0, y);
  float h_x1 = this->get_height((size_t)x1, y);
  float h_y0 = this->get_height(x, (size_t)y0);
  float h_y1 = this->get_height(x, (size_t)y1);

  float spacing = 1.0f / (float)(m_resolution - 1);

  vec3 tangent_x((float)(x1 - x0) * spacing, (h_x1 - h_x0), 0.0f);
  vec3 tangent_z(0.0f, (h_y1 - h_y0), (float)(y1 - y0) * spacing);

  vec3 normal = glm::cross(tangent_z, tangent_x);
  if (glm::length(normal) < 1e-8f)
    return vec3(0, 1, 0);

  return glm::normalize(normal);
}
