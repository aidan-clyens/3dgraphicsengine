#pragma once

// Includes
#include "Object3D.h"
#include "SquareMesh.h"


/* Square
 */
class Square : public Object3D {
    public:
        Square(Transform transform, vec3 color, int shininess = 1);
        Square(Transform transform, Texture texture);
};
