#include "Cube.h"

void Cube::set_color(vec3 colour)
{
  CubeMesh *mesh = this->get_cube_mesh();
  Material material = mesh->get_material();

  material.specular = vec3(1, 1, 1);
  material.ambient = colour;
  material.diffuse = colour;
  material.shininess = 1;

  mesh->set_material(material);
}

/* Cube
 */
Cube::Cube()
{
  Transform transform;
  transform.position = vec3(0, 0, 0);
  transform.rotation = vec3(0, 0, 0);
  transform.size = vec3(1, 1, 1);

  Material material;
  material.specular = vec3(1, 1, 1);
  material.ambient = vec3(1, 1, 1);
  material.diffuse = vec3(1, 1, 1);
  material.shininess = 1;

  CubeMesh *mesh = this->add_cube_mesh();
  mesh->set_material(material);
  mesh->set_transform(transform);
}

/* Cube
 */
Cube::Cube(Transform transform, vec3 color, int shininess) : Object3D(transform.position, transform.rotation, transform.size)
{
  Material material;
  material.specular = vec3(1, 1, 1);
  material.ambient = color;
  material.diffuse = color;
  material.shininess = shininess;

  CubeMesh *mesh = this->add_cube_mesh();
  mesh->set_material(material);
  mesh->set_transform(transform);
}

/* Cube
 */
Cube::Cube(Transform transform, Texture texture) : Object3D(transform.position, transform.rotation, transform.size)
{
  CubeMesh *mesh = this->add_cube_mesh();
  mesh->set_texture(texture);
  mesh->set_transform(transform);
}

CubeMesh *Cube::add_cube_mesh()
{
  this->add_component(COMP_MESH, new CubeMesh());
  return (CubeMesh *)this->get_component(COMP_MESH);
}

CubeMesh *Cube::get_cube_mesh()
{
  return (CubeMesh *)this->get_component(COMP_MESH);
}
