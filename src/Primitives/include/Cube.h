#pragma once

// Includes
#include "Object3D.h"
#include "CubeMesh.h"

/* Cube
 */
class Cube : public Object3D
{
  friend class Object3DFactory;

public:
  void set_color(vec3 colour);

private:
  Cube();
  Cube(Transform transform, vec3 color, int shininess = 1);
  Cube(Transform transform, Texture texture);

  CubeMesh *add_cube_mesh();
  CubeMesh *get_cube_mesh();
};
