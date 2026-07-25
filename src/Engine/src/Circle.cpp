#include "Circle.h"

/* Circle
 */
Circle::Circle(Transform transform, vec3 color, int shininess):
Object3D(transform.position, transform.rotation, transform.size)
{
    Material material;
    material.specular = vec3(1, 1, 1);
    material.ambient = color;
    material.diffuse = color;
    material.shininess = shininess;

    this->add_component(COMP_MESH, new CircleMesh());

    CircleMesh *mesh = (CircleMesh *)this->get_component(COMP_MESH);
    mesh->set_material(material);
    mesh->set_transform(transform);
}

/* Circle
 */
Circle::Circle(Transform transform, Texture texture):
Object3D(transform.position, transform.rotation, transform.size)
{
    this->add_component(COMP_MESH, new CircleMesh());

    CircleMesh *mesh = (CircleMesh *)this->get_component(COMP_MESH);
    mesh->set_texture(texture);
    mesh->set_transform(transform);
}

/* Circle
 */
Circle::Circle(vec2 position, float radius, vec3 color):
Circle(
    Transform{ vec3(position.x, position.y, 0.0f), vec3(0.0f, 0.0f, 0.0f), vec3(radius, radius, radius) },
    color
)
{
}
