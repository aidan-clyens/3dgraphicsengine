#pragma once

// Includes
#include "Types.h"
#include "ECS.h"
#include "Mesh.h"
#include "Light.h"

#include <string>

/* Object3D
 */
class Object3D : public Entity {
    public:
        Object3D();
        Object3D(vec3 pos, vec3 rotation, vec3 size);
        virtual ~Object3D();

        vec3 get_position() const;
        vec3 get_rotation() const;
        vec3 get_size() const;

        void set_position(vec3 position);
        void set_rotation(vec3 rotation);
        void set_size(vec3 size);

        std::string get_name() const;
        void set_name(const std::string &name);

    protected:
        std::string m_name; 
};