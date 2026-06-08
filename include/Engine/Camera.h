#pragma once

// Includes
#include <glm/gtc/matrix_transform.hpp>

#include "ECS.h"
#include "Types.h"


class Renderer;


/* Camera
 */
class Camera : public Component {
    friend class Renderer;

    public:
        Camera();
        Camera(vec3 position);

        void set_position(vec3 position);
        vec3 get_position() const;

        void set_mouse_offset(double offset_x, double offset_y);

        void translate_x(float speed);
        void translate_y(float speed);
        void translate_z(float speed);

        vec3 front() const;
        vec3 up() const;
        vec3 right() const;

    private:
        vec3 m_position;
        vec3 m_front;
        vec3 m_up;

        double m_yaw;
        double m_pitch;
};