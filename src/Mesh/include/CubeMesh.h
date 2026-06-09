#pragma once 

// Includes
#include "Mesh.h"

// Defines
#define CUBE_NUM_FACES          6
#define CUBE_FACE_NUM_VERTICES  6
#define CUBE_NUM_VERTICES       CUBE_NUM_FACES * CUBE_FACE_NUM_VERTICES

// Enums
typedef enum {
    CUBE_BACK,
    CUBE_FRONT,
    CUBE_LEFT,
    CUBE_RIGHT,
    CUBE_BOTTOM,
    CUBE_TOP
} eCubeFace;

/* CubeMesh
 */
class CubeMesh : public Mesh {
    public:
        CubeMesh();
        virtual ~CubeMesh();

        void set_face_enabled(eCubeFace face, bool enabled);

    private:
        bool m_faces_enabled[CUBE_NUM_FACES];
};