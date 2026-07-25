#include "Square.h"

/* Square
 */
Square::Square(Transform transform, vec3 color, int shininess):
Object3D(transform.position, transform.rotation, transform.size)
{
    Material material;
    material.specular = vec3(1, 1, 1);
    material.ambient = color;
    material.diffuse = color;
    material.shininess = shininess;

    this->add_component(COMP_MESH, new SquareMesh());

    SquareMesh *mesh = (SquareMesh *)this->get_component(COMP_MESH);
    mesh->set_material(material);
    mesh->set_transform(transform);
}

/* Square
 */
Square::Square(Transform transform, Texture texture):
Object3D(transform.position, transform.rotation, transform.size)
{
    this->add_component(COMP_MESH, new SquareMesh());

    SquareMesh *mesh = (SquareMesh *)this->get_component(COMP_MESH);
    mesh->set_texture(texture);
    mesh->set_transform(transform);
}
