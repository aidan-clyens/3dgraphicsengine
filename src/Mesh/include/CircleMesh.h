#pragma once

// Includes
#include "Mesh.h"

// Defines
#define CIRCLE_DEFAULT_SEGMENTS    32


/* CircleMesh
 */
class CircleMesh : public Mesh {
    public:
        CircleMesh(unsigned int segments = CIRCLE_DEFAULT_SEGMENTS);
        virtual ~CircleMesh();
};
