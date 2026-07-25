#pragma once

// Includes
#include "Object3D.h"
#include "CircleMesh.h"


/* Circle
 */
class Circle : public Object3D {
    public:
        Circle(Transform transform, vec3 color, int shininess = 1);
        Circle(Transform transform, Texture texture);
        Circle(vec2 position, float radius, vec3 color);
};
