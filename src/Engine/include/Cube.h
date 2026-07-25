#pragma once

// Includes
#include "Object3D.h"
#include "CubeMesh.h"


/* Cube
 */
class Cube : public Object3D {
    public:
        Cube(Transform transform, vec3 color, int shininess = 1);
        Cube(Transform transform, Texture texture);
};
